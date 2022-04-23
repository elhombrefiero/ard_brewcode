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
}

void update_heater_setpoint_low(int hindex, float setpoint_low)
{
}

void update_heater_setpoint_max(int hindex, float setpoint_max)
{
}

void update_heater_pin(int hindex, int pin) 
{
	heaters[hindex].set_data_pin(pin);
}

const char* Heater::get_name() {
	return name;
}

void Heater::set_index(int index)
{
	hindex = index;
}

void Heater::check_setpoints(DallasTemperature& sensors)
{

}

void Heater::remove_tsensors()
{
}

float Heater::get_setpoint_high()
{
	return setpoint_high;
}

float Heater::get_setpoint_low()
{
	return setpoint_low;
}

float Heater::get_setpoint_max()
{
	return setpoint_max;
}


int Heater::get_data_pin()
{
	return data_pin;
}

bool Heater::get_status()
{
	return status;
}

float Heater::get_current_temp(DallasTemperature &sensors)
{
	float current_temp = 0.0;
	for (int i = 0; i < tsensor_indices.size(); i++) {
		float tsensor_temp = sensors.getTempFByIndex(tsensor_indices[i]);
		Serial.print("Heater tsensor_temp: "); //DELETE
		Serial.println(tsensor_temp); //DELETE
		if (tsensor_temp > current_temp) {
			current_temp = tsensor_temp;
		}
	}
	return current_temp;
}

void Heater::set_data_pin(int new_pin)
{
	data_pin = new_pin;
}

void Heater::add_tsensor(DallasTemperature& sensors, int tsensor_index)
{
	DeviceAddress tsensor_address;
	bool valid_address;

	valid_address = sensors.getAddress(tsensor_address, tsensor_index);
	if (valid_address) {
		tsensor_indices.push_back(tsensor_index);
	}
}

//void update_heater_tsensor(int hindex, DallasTemperature& sensors, std::vector<uint8_t*>& tsensors, const char* tsensor_address) 
//{
//	return;
//}


void update_heater_tsensor(int hindex, DallasTemperature& sensors, int tsensor_index)
{
	heaters[hindex].add_tsensor(sensors, tsensor_index);
}
