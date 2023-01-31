#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <wifi_passwords.h>

const char* ssid = STASSID;
const char* password = STAPSK;

// PINS 
// using D3 or D4 caused me problems
const int mom_close_pin = D1;
const int mom_open_pin = D2;
const int endstop_pin = D6;
const int motor_close_pin = D5;
const int motor_open_pin = D0;

// Variables
const float piston_speed = 0.01;          //in m/s (coincidentally also mm/ms)
const float time_to_energize_coils = 1;   //in ms
bool position_known = false;              //true if position is known
float current_position = -1;              //in mm
const int minimum_allowable_position = 0;
const int maximum_allowable_position = 350;

void setup() {
  //pin modes
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(mom_close_pin, INPUT_PULLUP);
  pinMode(mom_open_pin, INPUT_PULLUP);
  pinMode(endstop_pin, INPUT_PULLUP);
  pinMode(motor_close_pin, OUTPUT);
  pinMode(motor_open_pin, OUTPUT);

  //start by stopping all motor movement
  digitalWrite(motor_close_pin, LOW);
  digitalWrite(motor_open_pin, LOW);

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  home();
}

void loop() {  
  //to do:
  //measure piston speed precisely
  //measure charge time
  //check if endstop opened without piston being moved
  //panic if endstop pin still triggered after opening
  //panic if endstop doesn't trigger after full movement
  //sanity check movement commands to not go out of range of motion
  //wirelessly send debug messages
  //program alarm bell  
  //control via home assistant
  ArduinoOTA.handle();

  if(position_known){
    Serial.print("position is known and is: ");
    Serial.println(current_position);
  }
  else{
    Serial.println("position is not known");
  }
  check_manual_switches();
  delay(500);
}

// I kept getting the polarity of the endstop check wrong
// Endstop switch is normally closed and connected to ground
// when endstop gets triggered the pin is pulled high by internal resistor
bool query_endstop(){
  return(digitalRead(endstop_pin));
}

void home(){
  if(query_endstop()){
    Serial.println("already homed");
    position_known = true;
    current_position = 0;
    return;
  }
  else{
    Serial.println("homing");
    digitalWrite(motor_close_pin, HIGH);
    while(!query_endstop()){
      delay(5);
    }
    digitalWrite(motor_close_pin,LOW);
    position_known = true;
    current_position = 0;
    Serial.println("homed");
    return;
  } 
}

void check_manual_switches(){
  //check open switch
  if(!digitalRead(mom_open_pin)){  //toggle switch triggered
    Serial.println("opening");
    digitalWrite(motor_open_pin, HIGH);
    delay(time_to_energize_coils + 50);       //wait for debounce
    current_position += 50*piston_speed;
    while(!digitalRead(mom_open_pin)){      
      delay(100);
      current_position += 100*piston_speed;
    }
    digitalWrite(motor_open_pin, LOW);    
    Serial.println("stopped");
  }
  //check close switch
  if(!digitalRead(mom_close_pin)){  //toggle switch triggered
    Serial.println("closing");
    digitalWrite(motor_close_pin, HIGH);
    delay(time_to_energize_coils + 50);       //wait for debounce
    current_position -= 50*piston_speed;
    while(!digitalRead(mom_close_pin)){      
      delay(100);
      current_position -= 100*piston_speed;
    }
    digitalWrite(motor_close_pin, LOW);    
    Serial.println("stopped");
  }
  return;
}

void go_to_x(int desired_position){
  if(desired_position < minimum_allowable_position || desired_position > maximum_allowable_position){
    Serial.println("DESIRED POSITION OUT OF BOUNDS");
  }
  int rounded_current_position = (int)roundf(current_position);
  if(rounded_current_position == desired_position){
    Serial.println("close enough.jpg");
    return;
  }
  else{
    Serial.print("moving to ");
    Serial.println(desired_position);
    int distance_in_mm_to_move = desired_position - rounded_current_position;
    int time_in_ms_to_move = ((int) ((float)abs(distance_in_mm_to_move))/piston_speed*1000);
    if(distance_in_mm_to_move > 0){
      digitalWrite(motor_open_pin, HIGH);
      delay(time_in_ms_to_move);
      digitalWrite(motor_open_pin, LOW);
      return;
    }
    else{
      digitalWrite(motor_close_pin, HIGH);
      delay(time_in_ms_to_move);
      digitalWrite(motor_close_pin, LOW);
      return;
    }
  }
}