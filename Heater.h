//// Heater.h
//
#ifndef _HEATER_h
#define _HEATER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "DallasTemperature.h"
#else
#include "WProgram.h"
#endif
//
//#define MAX_TEMP_SENSOR_PER_HEATER 3
//

class Heater {
public:
	Heater(int i) {
		heater_num = i;
		pin = 999;
	}
	void change_pin_num(int p) {
		pin = p;
		Serial.print("Heater " + heater_num);
		Serial.print(" pin is now " + pin);
	}
private:
	int heater_num;
	int pin;
};

//class HeaterClass
//{
//protected:
//
//
//public:
//	HeaterClass(int i);
//	float current_temp;
//	float upper_limit;
//	float lower_limit;
//	float max_limit;
//	bool status;
//	DeviceAddress tsensoraddresses[MAX_TEMP_SENSOR_PER_HEATER] = {};
//
//	void set_lower(float lower);
//	void set_upper(float upper);
//	void set_max(float max);
//	void return_heater_info();
//	void add_temp_sensor(String tsensorname);
//	void clear_temp_sensors();
//	void turn_on_pin();
//	void getMaxTemp(DallasTemperature &sensors);
//	void setName(String new_name);
//	void setPin(int new_pin);
//	void check_setpoints();
//
//private:
//	int pin = -999;
//	String name = "";
//};
//
//extern HeaterClass Heater;
//
//float getTempByDevice(DeviceAddress deviceAddress, DallasTemperature& sensors);
#endif
//
