#include <Arduino.h>

#include "main.h"
#include "fan.h"
#include "heater.h"

Fan fan(FAN_PIN);
Heater heater(HEATER_PIN, TEMP_PIN);


void setup() {
  Serial.begin(9600);
}

void loop() {
  fan.update(40,10);
  heater.update();
  heater.setTemp(100);
}