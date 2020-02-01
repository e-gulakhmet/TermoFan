#include <Arduino.h>

#include "fan.h"

Fan fan(6);


void setup() {
  
}

void loop() {
  fan.update(40,10);
}