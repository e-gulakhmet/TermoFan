#include <Arduino.h>
#include <GyverEncoder.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "main.h"
#include "fan.h"
#include "heater.h"

Fan fan(FAN_PIN);
Heater heater(HEATER_PIN, TEMP_PIN);
Encoder encoder(ENC_CLK, ENC_DT, ENC_BUTT, TYPE2);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_AO, TFT_RST);



void setup() {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST7735_CYAN);
  tft.setTextColor(ST77XX_RED);
}



void loop() {
  fan.update(heater.getHeaterTemp(), heater.getManualTemp());
  heater.update();
  encoder.tick();

  heater.setTemp(100);
  
  tft.setCursor(0,0);
  tft.print("FUCK IT");
}