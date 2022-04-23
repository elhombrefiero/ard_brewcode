// user_io.h

#ifndef _USER_IO_h
#define _USER_IO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "tsensor.h"
	#include "heater.h"
#else
	#include "WProgram.h"
#endif

#define MAX_SERIAL_INPUT 256 // Maximum size of character array to send info through serial

void return_all_info();

void clean_serial();

//void process_heater_info();

void determine_action(DallasTemperature& sensors, std::vector<uint8_t*>& tsensors);

void process_incoming_byte(const byte inByte, DallasTemperature& sensors, std::vector<uint8_t*>& tsensors);

void process_heater_info(DallasTemperature& sensors, std::vector<uint8_t*>& tsensors);


#endif

