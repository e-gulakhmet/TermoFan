#include <fan.h>



Fan::Fan(uint8_t fan_pin)
    : fan_pin_(fan_pin)
    , speed_(0)
    , spiral_temp_(0)
    , manual_temp_(0)
    {
        pinMode(fan_pin_, OUTPUT);
    }



void Fan::update(uint8_t spiral_temp, uint8_t manual_temp) {
    spiral_temp_ = spiral_temp;
    manual_temp_ = manual_temp;

    switch (fan_mode_) {
        case fmOff:
            analogWrite(fan_pin_, 0);
            break;
        
        case fmOn:
            
    }

}
