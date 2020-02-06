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

MenuMode menu_mode;

bool is_cursor;



MenuMode switchMenuMode(MenuMode curr, bool clockwice) { // Переключение режимов
  int n = static_cast<int>(curr);

  n += clockwice ? 1 : -1; // Если по часовой стрелке, то ставим следующий

  if ( n > 1) {
    n = 1;
  }
  if ( n < 0 ) {
    n = 0;
  }
  return static_cast<MenuMode>(n);
}



void showDisp(){
  // Показываем данные о температуре
  // Показываем работает ли система
  // Показываем данные о вентиляторе
  // Показываем работает включен ли сейчас нагрев

  if (is_cursor) {
    if (encoder.isHolded()) {
      is_cursor = false;
    }
  }
  else {
    if (encoder.isPress()) {
      is_cursor = true;
    }
    if (encoder.isRight()) {
      // Меняем режим на следущий
      switchMenuMode(menu_mode, 1);
    }
    if (encoder.isLeft()) {
      // Меняем режим на предыдущий
      switchMenuMode(menu_mode, -1);
    }
  }
  


  switch (menu_mode) {
    case mmHeater: // Режим настройки нагревателя
      if (is_cursor) {
        // Показать курсор
        // Упрвление темперартурой
      }
      else {
        // Мигаем курсором
      }
      break;
    

    case mmFan: // Режим настройки вентилятора
      if (is_cursor) {
        // Показать курсор
        // Упрвление скоростью
      }
      else {
        // Мигаем курсором
      }
      break;
  }
}





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
}