#ifndef _HEATER_H_
#define _HEATER_H_

#include <Arduino.h>



class Heater {
    public:
        Heater(uint8_t heater_pin, uint8_t temp_pin);

        typedef enum {
            mOff,
            mOn
        } Mode;

        void update();
        void setTemp(uint8_t manual_temp);
        void addTemp();
        void minTemp();
    
    private:
        uint8_t getTemp();

        uint8_t heater_pin_;
        uint8_t heater_temp_;
        uint8_t manual_temp_;

        Mode mode_;
};


#endif // _HEATER_H_