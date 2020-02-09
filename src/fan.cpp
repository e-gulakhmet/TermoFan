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
            // Если температура спирали больше 40
            // включаем вентилятор.
            if (spiral_temp_ >= 40) {
                speed_ = 100;
            }
            else { // Если температура не больше 40, то выключаем вентилятор
                speed_ = 0;
            }

            analogWrite(fan_pin_, 0);
            break;

        case fmOn:
            // Вентилятор включен

            // Устанавливаем скрость 100, если температура больше 40
            if (spiral_temp_ >= 40 && speed_ <= 99) {
                speed_ = 100;
            }

            else {
                
            }

            analogWrite(fan_pin_, speed_);         
            break;
    }

}

void Fan::setSpeed(uint8_t speed) {
    speed_ = speed;
}

void Fan::off() {
    fan_mode_ = fmOff;
}

void Fan::on() {
    fan_mode_ = fmOn;
}

void Fan::addTemp() {
    if (speed_ >= 100) {
        speed_ = 100;
    }
    else {
        speed_ += 10;
    }
}

void Fan::minTemp() {
    if (speed_ <= 0) {
        speed_ = 0;
    }
    else {
        speed_ -= 10;
    }
}

uint8_t Fan::getSpeed() {
    return uint8_t(speed_);
}

String Fan::getModeName() {
    return mode_name_[fan_mode_];
}