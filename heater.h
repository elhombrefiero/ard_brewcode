// heater.h

#ifndef _HEATER_h
#define _HEATER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <ArduinoSTL.h>
	#include "ArduinoJson.h"
	#include "DallasTemperature.h"
	#include "tsensor.h"
#else
	#include "WProgram.h"
#endif

class Heater {
	std::vector<int> tsensor_indices;
	char name[50] = "Heater";
	int hindex;
	float setpoint_high = 32.0;
	float setpoint_low = 31.0;
	float setpoint_max = 212.0;
	bool status = false;
	bool has_sensor = false;
	int data_pin = LED_BUILTIN;

public:
		const char* get_name();
		void set_index(int heater_index);
		void check_setpoints(DallasTemperature& sensors);
		float get_setpoint_high();
		float get_setpoint_low();
		float get_setpoint_max();
		void set_setpoint_high(float setpoint_high);
		void set_setpoint_low(float setpoint_low);
		void set_setpoint_max(float setpoint_max);
		float get_current_temp(DallasTemperature& sensors);
		int get_data_pin();
		bool get_status();
		void set_data_pin(int new_pin);
		void remove_tsensors();
		void update_heater_name(const char* new_name);
		void add_tsensor(DallasTemperature& sensors, int tsensor_index);
		void print_info(DallasTemperature& sensors);
};



void add_heater();

void print_heater_info(DallasTemperature& sensors);

int identify_heater_by_name(const char* name);

void update_heater_setpoint_high(int hindex, float setpoint_high);

void update_heater_setpoint_low(int hindex, float setpoint_low);

void update_heater_setpoint_max(int hindex, float setpoint_max);

void update_heater_name_by_index(int hindex, const char* new_name);

void update_heater_index(int hindex, int new_index);

void update_heater_pin(int hindex, int pin);

void update_heater_tsensor_by_tsensor_name(int hindex, DallasTemperature& sensors, const char* tsensor_address);

void update_heater_tsensor(int hindex, DallasTemperature& sensors, int tsensor_index);

void remove_heater_tsensors(int hindex);

void check_heater_setpoints(DallasTemperature& sensors);

int get_num_of_heaters();

#endif

