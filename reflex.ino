#include "tm1637.h"

uint32_t k;
volatile uint32_t cur;
volatile uint8_t stop = 1, ponow = 0;

void handleInterrupt ()
{
  if (digitalRead (15) == LOW) 
  {
    stop = 0;
    ponow = 1;
  } else {
    digitalWrite (2, LOW);
    stop = 1;
  }
}
void setup() {
  TM1637_init(1/*enable*/, 5/*brightness*/);
  pinMode(15, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(15), handleInterrupt, CHANGE);
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
  if (ponow && digitalRead(15) == LOW){
    delay(1000 + (cur % 2000UL));
    digitalWrite (2, HIGH);
    cur = millis();
    ponow = 0;
  }
  if (!stop) k = millis() - cur;
  pokaz (k);
  delay(1);
}
