#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "test-playground-b36c0.firebaseio.com"
#define FIREBASE_AUTH "D4FdhdrYkSrlsxpUbwRm5wPLwZTLnwm8BDJdVFCU"
#define WIFI_SSID "projectmusic"
#define WIFI_PASSWORD "projectmusic"

int PIN_VCA = 16;
int PIN_VCF = 5;
int PIN_VCO = 4;
int PIN_LFO = 0;
int PIN_GATE = 2;

int end_time = 0;
int start_time = 0;
bool playing = false;
int duration = 0;
float VCA = 0;
float VCO = 0;
float VCF = 0;
float LFO = 0;

void setup() {
  Serial.begin(115200);
  pinMode(duration, OUTPUT);
  pinMode(PIN_VCA, OUTPUT);
  pinMode(PIN_VCF, OUTPUT);
  pinMode(PIN_VCO, OUTPUT);
  pinMode(PIN_LFO, OUTPUT);
  pinMode(PIN_GATE, OUTPUT);

  // connect to wifi.
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
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
  Firebase.set("VCA", 0);
  Firebase.set("VCO", 0);
  Firebase.set("VCF", 0);
  Firebase.set("LFO", 0);
  Firebase.set("duration", 0);
  int end_time = 0;
  int start_time = 0;
  bool playing = false;
  int duration = 0;
  Firebase.stream("/"); 
}


void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("connecting");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    }
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.set("VCA", 0);
    Firebase.set("VCO", 0);
    Firebase.set("VCF", 0);
    Firebase.set("LFO", 0);
    Firebase.set("duration", 0);
    int end_time = 0;
    int start_time = 0;
    bool playing = false;
    int duration = 0;
    Firebase.stream("/"); 
  }
  
  if (Firebase.available()) {
      FirebaseObject event = Firebase.readEvent();
      String path = event.getString("path");
      Serial.println(path);
      if (path == "/duration") {
        duration = event.getFloat("data/value");
        Serial.print("DUR: ");
        Serial.println(duration);
        VCO = convertVoltage(event.getFloat("data/note"));
        Serial.print("VCO2: ");
        Serial.println(VCO);
      }
      else if (path == "/VCA") {
        VCA = convertVoltage(event.getFloat("data/value"));
        Serial.print("VCA: ");
        Serial.println(VCA);
        analogWrite(PIN_VCA, VCA);
      }
      else if (path == "/VCF") {
        VCF = convertVoltage(event.getFloat("data/value"));
        Serial.print("VCF: ");
        Serial.println(VCF);
        analogWrite(PIN_VCF, VCF);
      }
//      else if (path == "/VCO") {
//        VCO = convertVoltage(event.getFloat("data/value"));
//        Serial.print("VCO: ");
//        Serial.println(VCO);
//      }
      else if (path == "/LFO") {
        LFO = convertVoltage(event.getFloat("data/value"));
        Serial.print("LFO: ");
        Serial.println(LFO);
        analogWrite(PIN_LFO, LFO);
      }
  }   
    
  if (!playing && duration > 0) {
    Serial.println("start note");
    playing = true;
    end_time = millis() + duration;
    analogWrite(PIN_VCO, VCO);
    analogWrite(PIN_GATE, 0);
    delay(50);
    analogWrite(PIN_GATE, 1023);
    duration = 0;
  }
  if (playing && millis() >= end_time) {
    Serial.println("stop note");
    playing = false;
    analogWrite(PIN_GATE, 0);
    Firebase.setInt("/duration/value", 0);
  }
}

int convertVoltage(float voltage) {
  return voltage * (1023/3.28)*1.087;
}
