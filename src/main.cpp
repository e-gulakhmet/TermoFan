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

MenuMode menu_mode = mmHeater;

bool is_cursor;
unsigned long cursor_timer;
bool cursor;


// TODO: Нарисовать символ градус



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



void drawCursor(uint8_t x, uint8_t y, bool is_blink) {
  if (is_blink) {
    if (millis() - cursor_timer > 500) {
      cursor_timer = millis();
      cursor = !cursor;
    }
    if (cursor) {
      tft.drawRect(x, y, 160, 40, ST7735_GREEN);
    }
    else {
      tft.drawRect(x, y, 160, 40, ST7735_BLACK);
    }
  }
  else {
    tft.drawRect(x, y, 160, 40, ST7735_GREEN);
  }
  
}



void showDisp() {
  // Показываем данные о температуре
  // Название окна нагревателя
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(40, 0);
  tft.print("HEATER");
  // Названия маленьких окон
  tft.setTextSize(1);
  tft.setCursor(10, 20);
  tft.print("CURRENT");
  tft.setCursor(100, 20);
  tft.print("MANUAL");

  // Данные по температурам
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.setCursor(5, 30);
  tft.print(heater.getHeaterTemp());
  tft.print("'");
  tft.setCursor(90, 30);
  tft.print(heater.getManualTemp());
  tft.print("'");
  // Показываем данные о вентиляторе

  // Показываем работает ли система

  
  // Показываем работает включен ли сейчас нагрев

  switch (menu_mode) {
    case mmHeater: // Режим настройки нагревателя
      if (is_cursor) {
        // Показать курсор
        drawCursor(0, 15, false);
        // Упрвление темперартурой
      }
      else {
        // Мигаем курсором
        drawCursor(0, 15, true);        
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
  


}





void setup() {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
}



void loop() {
  fan.update(heater.getHeaterTemp(), heater.getManualTemp());
  heater.update();
  encoder.tick();

  showDisp();
}