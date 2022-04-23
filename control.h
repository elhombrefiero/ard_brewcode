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
#else
	#include "WProgram.h"
#endif

void process_state(DallasTemperature& sensors, std::vector<uint8_t*>& tsensors);


#endif

