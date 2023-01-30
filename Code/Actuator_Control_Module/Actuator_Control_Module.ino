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

void setup() {
  //pin modes
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(mom_close_pin, INPUT_PULLUP);
  pinMode(mom_open_pin, INPUT_PULLUP);
  pinMode(endstop_pin, INPUT_PULLUP);
  pinMode(motor_close_pin, OUTPUT);
  pinMode(motor_open_pin, OUTPUT);

  //start by stopping all motor movement
  digitalWrite(motor_close_pin, LOW);
  digitalWrite(motor_open_pin, LOW);

  //initialize home boolean 
  bool homed = false;


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
}

void loop() {  
  ArduinoOTA.handle();

  if(!digitalRead(mom_close_pin)){  //toggle switch triggered
    Serial.print("closing\n");
    digitalWrite(motor_close_pin, HIGH);
    delay(100);         //wait for debounce
    while(!digitalRead(mom_close_pin)){      
      delay(100);
    }    
    Serial.print("stopping\n");
    digitalWrite(motor_close_pin, LOW);
  }

  if(!digitalRead(mom_open_pin)){  //toggle switch triggered
    Serial.print("opening\n");
    digitalWrite(motor_open_pin, HIGH);
    delay(100);       //wait for debounce
    while(!digitalRead(mom_open_pin)){      
      delay(100);
    }    
    Serial.print("stopping\n");
    digitalWrite(motor_open_pin, LOW);
  }
  query_endstop();
  delay(500);
}

// I kept getting the polarity of the endstop check wrong
// Endstop switch is normally closed and connected to ground
// when endstop gets triggered the pin is pulled high by internal resistor
bool query_endstop(){
  return(digitalRead(endstop_pin));
}

bool home(){
  if(query_endstop()){
    Serial.print("already homed\n");
    return 0;
  }  
  Serial.print("homing\n");
  digitalWrite(motor_close_pin, HIGH);
  while(query_endstop()){
    delay(50);
  }
  digitalWrite(motor_close_pin,LOW);
  Serial.print("homed\n");
  return 0;
}