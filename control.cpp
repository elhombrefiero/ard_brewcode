// 
// 
// 

#include "control.h"

bool static auto_control = true;

void process_state(DallasTemperature &sensors) {
	if (auto_control) {
		// Update sensor values
		sensors.requestTemperatures();

		// Process controller setpoints
		check_heater_setpoints(sensors);
		//check_pump_setpoints();

		if (Serial.available()) {
			process_user_input(sensors);
		}
	}
	else {  // manual control
		// Update sensor values
		sensors.requestTemperatures();

		if (Serial.available()) {
			process_user_input(sensors);
		}
	}
}
