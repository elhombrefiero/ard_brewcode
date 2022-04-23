// 
// 
// 

#include "control.h"

bool static auto_control = true;

void process_state(DallasTemperature &sensors, std::vector<uint8_t*> &tsensors) {
	if (auto_control) {
		// Update sensor values
		sensors.requestTemperatures();

		// Process controller setpoints

		// Process user input

		print_temp_sensors(sensors, tsensors);

		print_heater_info(sensors);
	}
	else {  // manual control
		// Update sensor values
		sensors.requestTemperatures();

		// Process user input
	}
}
