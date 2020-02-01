#ifndef _FAN_H_
#define _FAN_H_

#include <Arduino.h>

class Fan {
    public:
        Fan(uint8_t fan_pin);

        typedef enum {
            fmOff,
            fmOn
        } FanMode;

        void update(uint8_t spiral_temp, uint8_t manual_temp);
        void setSpeed(uint8_t speed);
        void on();
        void off();
        uint8_t getSpeed() {return speed_;}

    private:
        uint8_t fan_pin_;
        uint8_t speed_;
        uint8_t spiral_temp_;
        uint8_t manual_temp_;

        String main_mode_name_[3] = {"Off", "On"};

        FanMode fan_mode_;

};

#endif // _FAN_H_
