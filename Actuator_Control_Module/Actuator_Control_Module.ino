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
const int endstop_pin_num = D6;
const int motor_close_pin = D0;
const int motor_open_pin = D5;

void setup() {
  //pin modes
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(mom_close_pin, INPUT_PULLUP);
  pinMode(mom_open_pin, INPUT_PULLUP);
  pinMode(endstop_pin_num, INPUT_PULLUP);
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

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  // Serial.print(digitalRead(mom_close_pin));
  // Serial.print(" ");
  // Serial.print(digitalRead(mom_open_pin));
  // Serial.print(" ");
  // Serial.print(digitalRead(endstop_pin_num));
  // Serial.print('\n');

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
}

void home(){
  return;
}