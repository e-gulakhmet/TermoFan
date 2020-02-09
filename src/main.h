#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>

const uint8_t FAN_PIN = 6; // Пин вентилятора
const uint8_t HEATER_PIN = 5; // Пин нагревателя
const uint8_t TEMP_PIN = A0; // Пин датчика температуры

const uint8_t ENC_CLK = 2;
const uint8_t ENC_DT = 3;
const uint8_t ENC_BUTT = 4;

const uint8_t TFT_CS = 7;
const uint8_t TFT_RST = 8;
const uint8_t TFT_AO = 9;

typedef enum {
    mmHeater,
    mmFan
} MenuMode;

#endif // _MAIN_H_
