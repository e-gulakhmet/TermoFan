#ifndef _HEATER_H_
#define _HEATER_H_

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>



class Heater {
    public:
        Heater(uint8_t heater_pin, uint8_t sensor_pin);

        typedef enum {
            mOff,
            mOn
        } Mode;

        void update();
        void setTemp(uint8_t manual_temp);
        void addTemp();
        void minTemp();
        void on();
        void off();
        void setMaxTemp(uint8_t max_temp);
    
    private:
        uint8_t getTemp();

        uint8_t heater_pin_;
        uint8_t sensor_pin_;
        uint8_t heater_temp_;
        uint8_t manual_temp_;
        uint8_t max_temp_;

        Mode mode_;
        OneWire wireSensor;
        DallasTemperature sensor;
        DeviceAddress sensorAddress;
};


#endif // _HEATER_H_