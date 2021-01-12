// 
// 
// 

//#include "SerialInput.h"
//#include "SerialOutput.h"
//#include "Heater.h"
//
//void parse_serial(String& SerialInput, TempSensorClass tempsensors[], uint8_t number_of_tsensors, HeaterClass heaterarray[], DallasTemperature& sensors) {
//	// Read the input from Python, which are
//	  // in the following format:
//	  // Switching pin statuses
//	  //   X=OFF or X=ON
//	  // where X is the pin number
//	  // Returning all information
//	  //   !
//	char character = Serial.read();
//	SerialInput.concat(character);
//
//	if (SerialInput.endsWith("!"))
//	{
//		// Requested all information (temperatures, and heaters)
//		returnAllInfo(tempsensors, number_of_tsensors, heaterarray, sensors);
//		SerialInput = "";
//		return;
//	}
//
//	if (SerialInput.endsWith("#"))
//		// The character # is the end of an input from serial
//	{
//		Serial.print("User inputted '#'. Here is the full string input: ");
//		Serial.println(SerialInput);
//		if (SerialInput.startsWith("updateHeaterSetpoint")) {
//			update_heater_setpoint(SerialInput);
//		}
//
//
//		// Assign temperature sensor to heater (Need device address and heater name)
//
//
//
//
//		// Requested software override of the heaters
//
//		// Requested automatic heater control
//
//		// Update heater pin
//
//		// Clear the input
//		SerialInput = "";
//	}
//}
//
//void update_heater_setpoint(String& serial_input) {
//	// String is in the format:
//	// updateHeaterSetpoint;<Heater name>;<lower value>;<upper value>;<max value>#
//	Serial.println("We are in the update_heater_setpoint routine. Here's the full string:");
//	Serial.println(serial_input);
//
//	// First capture is discarded
//	String discard = "";
//	return_captured_and_cut_string(serial_input, discard, ";");
//	String heater_name = "";
//	return_captured_and_cut_string(serial_input, heater_name, ";");
//
//	String string_lower = "";
//	return_captured_and_cut_string(serial_input, string_lower, ";");
//	float lower = string_lower.toFloat();
//
//	String string_upper = "";
//	return_captured_and_cut_string(serial_input, string_upper, ";");
//	float upper = string_upper.toFloat();
//
//	String string_max = "";
//	return_captured_and_cut_string(serial_input, string_max, "#");
//	float max = string_max.toFloat();
//
//	//// Now go through each heater element and update the one that matches the name
//	Serial.println("End of update_heater_setpoint routine. Here are the heater info.");
//	Serial.print("Heater name: ");
//	Serial.println(heater_name);
//	Serial.print("Lower: ");
//	Serial.println(lower);
//	Serial.print("Upper: ");
//	Serial.println(upper);
//	Serial.print("Max: ");
//	Serial.println(max);
//};
//
//void return_captured_and_cut_string(String& string_input, String& string_output, String delimeter) {
//
//	//DEBUG
//	Serial.print("Entering return_captured_and_cut_string. String_input:");
//	Serial.println(string_input);
//
//	// Find first instance of the delimiter
//	int end_pos = string_input.indexOf(delimeter);
//	string_output = string_input.substring(0, end_pos);
//
//	// cut the original referenced string (including delimiter)
//	string_input.remove(0, end_pos + 1);
//
//	//DEBUG
//	Serial.print("Finished return_captured_and_cut_string.");
//	Serial.print("String_input:");
//	Serial.println(string_input);
//	Serial.print("String_output:");
//	Serial.println(string_output);
//
//}
