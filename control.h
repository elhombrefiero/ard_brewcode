// control.h

#ifndef _CONTROL_h
#define _CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "DallasTemperature.h"
	#include "ArduinoSTL.h"
	#include "ArduinoJson.h"
	#include "tsensor.h"
	#include "heater.h"
	#include "user_io.h"
#else
	#include "WProgram.h"
#endif

void process_state(DallasTemperature& sensors);

bool is_auto_control();

void set_auto_control(bool new_auto_control);


#endif

