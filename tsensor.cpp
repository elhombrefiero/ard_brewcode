// 
// 
// 

#include "tsensor.h"
StaticJsonDocument<192> tsensor_info;
static int num_of_sensors = 0;

void init_temp_sensors(DallasTemperature &sensors)
{
	sensors.begin();
	num_of_sensors = sensors.getDeviceCount();
}

void print_temp_sensors(DallasTemperature& sensors)
{
	char address[16];
	DeviceAddress daddress;
	bool valid_address;
	float tempF;
	for (int i = 0; i < num_of_sensors; i++) {
		valid_address = sensors.getAddress(daddress, i);
		tempF = sensors.getTempFByIndex(i);		
		daddress_to_char(daddress, address);
		tsensor_info["type"] = "tsensor";
		tsensor_info["address"] = address;
		tsensor_info["index"] = i;
		tsensor_info["cur_temp"] = tempF;
		serializeJson(tsensor_info, Serial);
		Serial.println();
		tsensor_info.clear();
		address[0] = '\0';
	}
}

void daddress_to_char(DeviceAddress deviceAddress, char* return_char_array)
{
	uint8_t i, j;
	static char hex[17] = "0123456789ABCDEF";
	for (i = 0, j = 0; i < 8; i++) {
		return_char_array[j++] = hex[deviceAddress[i] / 16];
		return_char_array[j++] = hex[deviceAddress[i] & 15];
	}
	return_char_array[j] = '\0';
}

int find_tsensor_by_name(DallasTemperature& sensors, const char* lookup_serial)
{
	char address[17];
	DeviceAddress daddress;
	bool valid_address;

	for (int i = 0; i < num_of_sensors; i++) {
		valid_address = sensors.getAddress(daddress, i);
		daddress_to_char(daddress, address);
		if (strcmp(address, lookup_serial) == 0) {
			return i;
		}

	}

	return -1;
}
