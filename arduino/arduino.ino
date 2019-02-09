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
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  // set value
  float VCA = convertVoltage(Firebase.getFloat("/VCA/value"));
  if (Firebase.failed()) {
      Serial.print("getting VCA failed:");
      Serial.println(Firebase.error());  
      return;
  }
  float VCF = convertVoltage(Firebase.getFloat("/VCF/value"));
  // handle error
  if (Firebase.failed()) {
      Serial.print("getting VCF failed:");
      Serial.println(Firebase.error());  
      return;
  };
  float VCO = convertVoltage(Firebase.getFloat("/VCO/value"));
  // handle error
  if (Firebase.failed()) {
      Serial.print("getting VCO failed:");
      Serial.println(Firebase.error());  
      return;
  }
  float LFO = convertVoltage(Firebase.getFloat("/LFO/value"));
  // handle error
  if (Firebase.failed()) {
      Serial.print("getting LFO failed:");
      Serial.println(Firebase.error());  
      return;
  }
  analogWrite(PIN_VCA, VCA);
  analogWrite(PIN_VCF, VCF);
  analogWrite(PIN_VCO, VCO);
  analogWrite(PIN_LFO, LFO);
}

int convertVoltage(float voltage) {
  return voltage * (1024/3.26);
}