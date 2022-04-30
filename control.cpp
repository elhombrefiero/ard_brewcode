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

bool is_auto_control()
{
	return auto_control;
}

void set_auto_control(bool new_auto_control) {
	// TODO: When going from auto to manual control, disable all controllers
	// Similarly, when going from manual to auto, enable all controllers
	auto_control = new_auto_control;
}
