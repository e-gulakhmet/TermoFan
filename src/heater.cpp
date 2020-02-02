#include <heater.h>



Heater::Heater(uint8_t heater_pin, uint8_t temp_pin)
    : heater_pin_(heater_pin)
    , heater_temp_(0)
    , manual_temp_(0)
    , mode_(mOn)
    {
        pinMode(temp_pin, INPUT);
        pinMode(heater_pin_, OUTPUT);
    }



void Heater::update() {
    heater_temp_ = getTemp();
}



uint8_t Heater::getTemp(){
    uint8_t temp = 40;
    return temp;
}