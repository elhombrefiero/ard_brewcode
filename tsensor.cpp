// 
// 
// 

#include "tsensor.h"

void init_temp_sensors(DallasTemperature &sensors, std::vector<uint8_t*> &tsensors)
{
	sensors.begin();
	int num_of_sensors = sensors.getDeviceCount();
	Serial.print("num_of_sensors: ");
	Serial.println(num_of_sensors);

	for (int i = 0; i < num_of_sensors; i++) {
		uint8_t* address = nullptr;
		bool valid = sensors.getAddress(address, i);
		if (valid) {
			tsensors.push_back(address);
		}		
	}
	Serial.print("Found ");
	Serial.print(tsensors.size());
	Serial.println(" temperature sensors.");
}

void print_temp_sensors(DallasTemperature& sensors, std::vector<uint8_t*> &tsensors)
{
	DynamicJsonDocument tsensor_info(192);
	char address[16];
	DeviceAddress daddress;
	bool valid_address;
	float tempF;
	for (int i = 0; i < tsensors.size(); i++) {
		valid_address = sensors.getAddress(daddress, i);
		tempF = sensors.getTempFByIndex(i);		
		dadress_to_char(daddress, address);
		tsensor_info["type"] = "tsensor";
		tsensor_info["address"] = address;
		tsensor_info["index"] = i;
		tsensor_info["cur_temp"] = tempF;
		serializeJson(tsensor_info, Serial);
		Serial.println();
		tsensor_info.clear();
	}
}

void dadress_to_char(DeviceAddress deviceAddress, char* return_char_array)
{
	uint8_t i, j;
	static char hex[17] = "0123456789ABCDEF";
	for (i = 0, j = 0; i < 8; i++) {
		return_char_array[j++] = hex[deviceAddress[i] / 16];
		return_char_array[j++] = hex[deviceAddress[i] & 15];
	}
	return_char_array[j] = '\0';
}
