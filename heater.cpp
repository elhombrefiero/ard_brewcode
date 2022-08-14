// 
// 
// 

#include "heater.h"

static std::vector<Heater> heaters;
static int num_of_heaters = 0;

void add_heater()
{
	Heater myheater;
	myheater.set_index(num_of_heaters);
	heaters.push_back(myheater);
	num_of_heaters++;
}

void print_heater_info(DallasTemperature& sensors) {
	DynamicJsonDocument hinfo(256);
	
	for (int i = 0; i < heaters.size(); i++) {
		hinfo["type"] = "heater";
		hinfo["name"] = heaters[i].get_name();
		hinfo["index"] = i;
		hinfo["pin"] = heaters[i].get_data_pin();
		hinfo["setpoint_high"] = heaters[i].get_setpoint_high();
		hinfo["setpoint_low"] = heaters[i].get_setpoint_low();
		hinfo["setpoint_max"] = heaters[i].get_setpoint_max();
		hinfo["current_temp"] = heaters[i].get_current_temp(sensors);
		hinfo["status"] = heaters[i].get_status();
		if (heaters[i].tsensor_indices.size() > 0) {
			JsonArray tsensor_indices = hinfo.createNestedArray("tsensor_indices");
			for (int j = 0; j < heaters[i].tsensor_indices.size(); j++) {
				tsensor_indices.add(heaters[i].tsensor_indices[j]);
			}
		}
		serializeJson(hinfo, Serial);
		Serial.println();
		hinfo.clear();
	}
}

int identify_heater_by_name(const char* check_name)
{
	// Looks up the heater info based on name

	// A -1 means the heater was not found
	int heater_index = -1;
	bool name_matched = false;	

	if (check_name[0] != '\0') {
		for (int i = 0; i < heaters.size(); i++) {
			name_matched = strcmp(heaters[i].get_name(), check_name) == 0;
			if (name_matched) {
				return i;
			}
		}
	}
	return heater_index;
}

void update_heater_setpoint_high(int hindex, float setpoint_high)
{
	heaters[hindex].set_setpoint_high(setpoint_high);
}

void update_heater_setpoint_low(int hindex, float setpoint_low)
{
	heaters[hindex].set_setpoint_low(setpoint_low);
}

void update_heater_setpoint_max(int hindex, float setpoint_max)
{
	heaters[hindex].set_setpoint_max(setpoint_max);
}

void update_heater_pin(int hindex, int pin) 
{
	heaters[hindex].set_data_pin(pin);
}

const char* Heater::get_name() {
	return name;
}

void update_heater_index(int hindex, int new_index)
{
	heaters[hindex].set_index(new_index);
}

void Heater::set_index(int index)
{
	hindex = index;
}

void Heater::check_setpoints(DallasTemperature& sensors)
{
	int val = digitalRead(data_pin);
	float maxtempF = 999.0; // Peg it high so it won't turn the heater on
	float tempF; // Temperature from sensor array
	if (!has_sensor) return;

	for (int i = 0; i < tsensor_indices.size(); i++) {
		// Get the latest temperature for the heater
		float tempF = sensors.getTempFByIndex(tsensor_indices[i]);
		if (tempF > 32.0) { // Use case will never use freezing temperatures
			if (val == HIGH) {
				status = true;
				if (tempF > setpoint_high || tempF > setpoint_max) {
					digitalWrite(data_pin, LOW);
					status = false;
				}
			}
			if (val == LOW) {
				status = false;
				if (tempF < setpoint_low) {
					digitalWrite(data_pin, HIGH);
					status = true;
				}
			}
		}
	}	
}

float Heater::get_setpoint_high()
{
	return setpoint_high;
}

void Heater::set_setpoint_high(float new_setpoint_high)
{
	setpoint_high = new_setpoint_high;
}

float Heater::get_setpoint_low()
{
	return setpoint_low;
}

void Heater::set_setpoint_low(float new_setpoint_low)
{
	setpoint_low = new_setpoint_low;
}

float Heater::get_setpoint_max()
{
	return setpoint_max;
}

void Heater::set_setpoint_max(float new_setpoint_max)
{
	setpoint_max = new_setpoint_max;
}

int Heater::get_data_pin()
{
	return data_pin;
}

void Heater::set_data_pin(int new_pin)
{
	// Turn off previous pin and set it to INPUT
	digitalWrite(data_pin, LOW);
	pinMode(data_pin, INPUT);

	// Set the new heater pin
	pinMode(new_pin, OUTPUT);
	data_pin = new_pin;
}

bool Heater::get_status()
{
	return status;
}

void Heater::update_heater_name(const char* new_name)
{
	strcpy(name, new_name);
}

void Heater::remove_tsensors()
{
	digitalWrite(data_pin, LOW);
	status = false;
	data_pin = LED_BUILTIN;
	tsensor_indices.clear();
	has_sensor = false;
}

float Heater::get_current_temp(DallasTemperature &sensors)
{
	float current_temp = 0.0;
	if (has_sensor) {
		for (int i = 0; i <= tsensor_indices.size(); i++) {
			float tsensor_temp = sensors.getTempFByIndex(tsensor_indices[i]);
			if (tsensor_temp > current_temp) {
				current_temp = tsensor_temp;
			}
		}
	}
	return current_temp;
}

void Heater::add_tsensor(DallasTemperature& sensors, int tsensor_index)
{
	DeviceAddress tsensor_address;
	bool valid_address;

	valid_address = sensors.getAddress(tsensor_address, tsensor_index);
	if (valid_address) {
		tsensor_indices.push_back(tsensor_index);
		has_sensor = true;
	}
}

void update_heater_tsensor_by_tsensor_name(int hindex, DallasTemperature& sensors, const char* tsensor_address)
{
	int tsensor_index;
	tsensor_index = find_tsensor_by_name(sensors, tsensor_address);
	if (tsensor_index != -1) {
		heaters[hindex].add_tsensor(sensors, tsensor_index);
	}
	
	return;
}

void update_heater_tsensor(int hindex, DallasTemperature& sensors, int tsensor_index)
{
	heaters[hindex].add_tsensor(sensors, tsensor_index);
}

void remove_heater_tsensors(int hindex)
{
	heaters[hindex].remove_tsensors();
}

void check_heater_setpoints(DallasTemperature& sensors)
{
	for (int i = 0; i < heaters.size(); i++) {
		heaters[i].check_setpoints(sensors);
	}
}

void update_heater_name_by_index(int hindex, const char* new_name) 
{
	heaters[hindex].update_heater_name(new_name);
}