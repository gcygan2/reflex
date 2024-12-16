/*
  Układ do pomiaru refleksu na dzień otwarty CEZ 13 grudnia 2024 r.
  Copyright (c) 2024, Grzegorz Cygan
  All rights reserved.
*/
#include <WiFi.h>
#include <WebServer.h>
#include "tm1637.h"
#define GRZYBEK 15
#define LED 2
volatile uint32_t start_ts, cur_ts;
volatile uint8_t stop;
const char* ssid = "TP-LINK_EAD700";
const char* password = "Skowronek";
WebServer server(80);
void handleRoot() {
  String html= "<!DOCTYPE html>\n<html><head><meta http-equiv=\"refresh\" content=\"1\"></head><body><h1>" + String(cur_ts - start_ts) + "</h1></body></html>";
  server.send(200, "text/html", html);
}



void handleInterrupt ()
{
  stop = 1;
  cur_ts = millis();
  digitalWrite (LED, LOW);
}

void setup() {
  TM1637_init(1/*enable*/, 5 /*brightness*/);
  pinMode(GRZYBEK, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(GRZYBEK), handleInterrupt, FALLING);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Łączenie z WiFi..."); 
  }
  Serial.println("Połączono z WiFi");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Serwer uruchomiony");
}

void pokaz (uint32_t k2)
{
  uint8_t n;
  for (n = 0; n < 6; ++n) {
    TM1637_display_digit(n, k2 % 10UL);
    k2 /= 10UL;
  }
}

void loop() {
  if (digitalRead(GRZYBEK) && stop){
    delay(1000 + (start_ts % 2000UL));
    digitalWrite (LED, HIGH);
    start_ts = millis();
    stop = 0;
  }
  if (!stop) cur_ts = millis();
  pokaz (cur_ts - start_ts);
  //delay(10); // this speeds up the simulation
  server.handleClient();
}
