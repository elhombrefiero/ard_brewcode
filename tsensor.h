// tsensor.h

#ifndef _TSENSOR_h
#define _TSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "DallasTemperature.h"
	#include "OneWire.h"
	#include "ArduinoSTL.h"
	#include "ArduinoJson.h"
#else
	#include "WProgram.h"
#endif

void init_temp_sensors(DallasTemperature &sensors, std::vector<uint8_t*> &tsensors);

void print_temp_sensors(DallasTemperature& sensors, std::vector<uint8_t*> &tsensors);

void dadress_to_char(DeviceAddress deviceAddress, char* return_char_array);

#endif
