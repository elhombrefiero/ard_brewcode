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

void init_temp_sensors(DallasTemperature &sensors);

void print_temp_sensors(DallasTemperature& sensors);

void daddress_to_char(DeviceAddress deviceAddress, char* return_char_array);

int find_tsensor_by_name(DallasTemperature& sensors, const char* lookup_serial);

#endif
