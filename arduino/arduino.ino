//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "test-playground-b36c0.firebaseio.com"
#define FIREBASE_AUTH "D4FdhdrYkSrlsxpUbwRm5wPLwZTLnwm8BDJdVFCU"
#define WIFI_SSID "projectmusic"
#define WIFI_PASSWORD "projectmusic"

int PIN_VCA = 5;
int PIN_VCF = 4;
int PIN_VCO = 0;
int PIN_LFO = 2;
int PIN_GATE = 14;

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  pinMode(PIN_GATE, OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/");  
}

int end_time = 0;
int start_time = 0;
bool playing = false;
int duration = 0;
float VCA = 0;
float VCO = 0;
float VCF = 0;
float LFO = 0;

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
      FirebaseObject event = Firebase.readEvent();
      String path = event.getString("path");
      if (path == "/duration/value") {
        duration = event.getInt("data");
        Serial.print("DUR: ");
        Serial.println(duration);
      }
      else if (path == "/VCA/value") {
        VCA = convertVoltage(event.getFloat("data"));
        Serial.print("VCA: ");
        Serial.println(VCA);
      }
      else if (path == "/VCF/value") {
        VCF = convertVoltage(event.getFloat("data"));
        Serial.print("VCF: ");
        Serial.println(VCF);
      }
      else if (path == "/VCO/value") {
        VCO = convertVoltage(event.getFloat("data"));
        Serial.print("VCO: ");
        Serial.println(VCO);
      }
      else if (path == "/LFO/value") {
        LFO = convertVoltage(event.getFloat("data"));
        Serial.print("LFO: ");
        Serial.println(LFO);
      }
      analogWrite(PIN_VCO, VCO);
      analogWrite(PIN_VCA, VCA);
      analogWrite(PIN_VCF, VCF);
      analogWrite(PIN_LFO, LFO);
  }   
    
  if (!playing && duration > 0) {
    playing = true;
    end_time = millis() + duration;
    digitalWrite(PIN_GATE, HIGH);
  }
  if (playing && millis() >= end_time) {
    playing = false;
    end_time = 0;
    digitalWrite(PIN_GATE, LOW);
    Firebase.setInt("/duration/value", 0);
  }
}

int convertVoltage(float voltage) {
  return voltage * (1024/3.26);
}
