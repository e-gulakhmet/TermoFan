#include <fan.h>



Fan::Fan(uint8_t fan_pin)
    : fan_pin_(fan_pin)
    , speed_(0)
    , spiral_temp_(0)
    , manual_temp_(0)
    , fan_mode_(fmOn)
    {
        pinMode(fan_pin_, OUTPUT);
    }



void Fan::update(uint8_t spiral_temp, uint8_t manual_temp) {
    spiral_temp_ = spiral_temp;
    manual_temp_ = manual_temp;

    switch(fan_mode_) {
        case fmOff:
            // Вентилятор выключен
            analogWrite(fan_pin_, 0);
            break;

        case fmOn:
            // Вентилятор включен

            // Устанавливаем скрость 100, если температура больше 40
            if (spiral_temp_ >= 40 && speed_ <= 99) {
                analogWrite(fan_pin_, 100);
            }

            else {
                analogWrite(fan_pin_, speed_);
            }            
            break;
    }

}



void Fan::setSpeed(uint8_t speed) {
    speed_ = speed;
}



void Fan::off(){
    // Если температура спирали меньше 40, тогда можем выключить вентилятор
    if (spiral_temp_ <= 40) {
        fan_mode_ = fmOff;
    }
}