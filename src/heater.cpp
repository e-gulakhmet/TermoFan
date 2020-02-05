#include <heater.h>



Heater::Heater(uint8_t heater_pin, uint8_t sensor_pin)
    : heater_pin_(heater_pin)
    , sensor_pin_(sensor_pin)
    , heater_temp_(0)
    , manual_temp_(0)
    , max_temp_(120)
    , mode_(mOn)
    , wireSensor(sensor_pin_)
    , sensor(&wireSensor)
    {
        pinMode(heater_pin_, OUTPUT);
        sensor.begin();
    }



void Heater::update() {

    switch (mode_) {
        // Если нагреватель включен
        case mOn:
            heater_temp_ = getTemp();

            // Если температура больше максимальной, то выключаем нагреваетель
            if (heater_temp_ > max_temp_) {
                digitalWrite(heater_pin_, LOW);
            }
            
            else {
                // Если темепература спирали меньше указанной температуры,
                // Включаем нагреватель
                if (heater_temp_ < manual_temp_) {
                    digitalWrite(heater_pin_, HIGH);
                }
                // Если температура спирали больше указанной,
                // то выключаем нагреватель
                else if (heater_temp_ >= manual_temp_) {
                    digitalWrite(heater_temp_, LOW);
                }
            }

            break;

        
        case mOff:
            digitalWrite(heater_temp_, LOW);
    }
}



uint8_t Heater::getTemp(){
    sensor.requestTemperatures();
    uint8_t temp = sensor.getTempCByIndex(0);
    Serial.println(temp);
    return temp;
}



void Heater::setTemp(uint8_t manual_temp) {
    if (manual_temp > max_temp_) {
        manual_temp_ = max_temp_;
    }
    else if (manual_temp < 0) {
        manual_temp_ = 0;
    }
    else {
        manual_temp_ = manual_temp;
    }
}



void Heater::addTemp() {
    if (manual_temp_ >= max_temp_) {
        manual_temp_ = max_temp_;
    }
    else {
        manual_temp_ += 10;
    }
}



void Heater::minTemp() {
    if (manual_temp_ <= 0) {
        manual_temp_ = 0;
    }
    else {
        manual_temp_ -= 10;
    }
}



void Heater::on() {
    mode_ = mOn;
}



void Heater::off() {
    mode_ = mOff;
}



void Heater::setMaxTemp(uint8_t max_temp) {
    max_temp_ = max_temp;    
}