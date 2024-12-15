/*
  Układ do pomiaru refleksu na dzień otwarty CEZ 13 grudnia 2024 r.
  Copyright (c) 2024, Grzegorz Cygan
  All rights reserved.
*/

#include "tm1637.h"
#define GRZYBEK 15
#define LED 2

volatile uint32_t start_ts, cur_ts;
volatile uint8_t stop;

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
  delay(10); // this speeds up the simulation
}
