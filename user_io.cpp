// 
// 
// 

#include "user_io.h"

// String that will keep incoming serial info.
char static SerialInput[MAX_SERIAL_INPUT];
static StaticJsonDocument<256> json_input;
static StaticJsonDocument<96> tsensor_info;

void return_all_info(DallasTemperature& sensors)
{
	//Print the information for sensors and controllers
	print_temp_sensors(sensors);
	print_heater_info(sensors);
}

void clean_serial()
{
	for (int i = 0; i < MAX_SERIAL_INPUT - 1; i++) {
		SerialInput[i] = '\0';
	}
	json_input.clear();
}

void process_heater_info(DallasTemperature &sensors)
{
	/*
	For heater/pump components, one the following is required:
	index=<num>
	name=<hname>

	the rest are valid entries for that heater:
	setpoint_upper:<num>
	setpoint_lower:<num>
	setpoint_max:<num>
	tsensor_address:<address>*/
	int hindex = -1;

	const char* name = json_input["name"]; // "Heater 1"
	const char* new_name = json_input["new_name"]; // "Heater 2"
	int index = json_input["index"]; // Assume heater indices start at 1
	float setpoint_high = json_input["setpoint_high"]; // 95.5
	float setpoint_low = json_input["setpoint_low"]; // 90.5
	float setpoint_max = json_input["setpoint_max"]; // 212.5
	int pin = json_input["pin"]; // 5
	const char* tsensor_address = json_input["tsensor_address"]; // "28FFAC378217045A"
	int tsensor_index = json_input["tsensor_index"];
	bool remove_tsensors = json_input["remove_tsensors"]; // "remove_tsensors"
	
	// Add new heater
	if (json_input.containsKey("add_heater")) {
		add_heater();
		return;
	}

	// Get index of heater
	if (json_input.containsKey("name")) {
		hindex = identify_heater_by_name(name);
	}
	else if (json_input.containsKey("index")) {
		hindex = index;
	}
	else {
		return;
	}

	// Update setpoint high if found
	if (setpoint_high > 0.0) {
		update_heater_setpoint_high(hindex, setpoint_high);
	}

	// Update setpoint low if found
	if (setpoint_low > 0.0) {
		update_heater_setpoint_low(hindex, setpoint_low);
	}

	// Update setpoint max if found
	if (setpoint_max > 0.0) {
		update_heater_setpoint_max(hindex, setpoint_max);
	}

	// Update heater name if found
	if (json_input.containsKey("new_name")) {
		update_heater_name_by_index(hindex, new_name);
	}

	// Update heater pin if found
	if (json_input.containsKey("pin")) {
		update_heater_pin(hindex, pin);
	}

	// Update tsensor if found
	if (json_input.containsKey("tsensor_address")) {
		update_heater_tsensor_by_tsensor_name(hindex, sensors, tsensor_address);
	}
	if (json_input.containsKey("tsensor_index")) {
		update_heater_tsensor(hindex, sensors, tsensor_index);
	}

	// Remove tsensors from heater
	if (json_input.containsKey("remove_tsensors")) {
		remove_heater_tsensors(hindex);
	}
}

void process_user_input(DallasTemperature& sensors)
{
	while (Serial.available()) {
		process_incoming_byte(Serial.read(), sensors);
	}
}

void determine_action(DallasTemperature& sensors)
{
	/*
 * Deserialize the JSON information in the SERIAL_BUFFER
 * Process JSON command(s).
 * {type:heater,name:"Heater 1",index=1,...}
*/

	DynamicJsonDocument output_text(MAX_SERIAL_INPUT);

	DeserializationError error = deserializeJson(json_input, SerialInput);

	if (error) {
		output_text["type"] = "error";
		output_text["msg"] = "determine_action, deserializeJson() failed.";
		output_text["msg2"] = error.f_str();
		serializeJson(output_text, Serial);
		Serial.println();
		clean_serial();
		return;
	}

	const char* type = json_input["type"];

	if (strcmp(type, "heater") == 0) {
		process_heater_info(sensors);
		return;
	}
}

void process_incoming_byte(const byte inByte, DallasTemperature& sensors)
{
	static unsigned int input_pos = 0;

	switch (inByte) {
	case '!': // display all information
		return_all_info(sensors);
		clean_serial();
		input_pos = 0;
		break;
	case '}':
		SerialInput[input_pos++] = inByte;
		determine_action(sensors);
		clean_serial();
		input_pos = 0;
		break;
	default:
		if (input_pos < (MAX_SERIAL_INPUT - 1)) {
			SerialInput[input_pos++] = inByte;
		}
		break;
	}
}
