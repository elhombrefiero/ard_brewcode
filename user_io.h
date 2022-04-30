// user_io.h

#ifndef _USER_IO_h
#define _USER_IO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "tsensor.h"
	#include "heater.h"
	#include "control.h"
#else
	#include "WProgram.h"
#endif

#define MAX_SERIAL_INPUT 256 // Maximum size of character array to send info through serial

void return_all_info(DallasTemperature& sensors);

void clean_serial();

void determine_action(DallasTemperature& sensors);

void process_incoming_byte(const byte inByte, DallasTemperature& sensors);

void process_heater_info(DallasTemperature& sensors);

void process_user_input(DallasTemperature& sensors);

void print_general_status();

void process_general_info();


#endif

