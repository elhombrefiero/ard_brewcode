//// 
//// 
//// 
//
//#include "Heater.h"
//
//
//
//HeaterClass::HeaterClass(int i)
//{
//	name = "Heater " + String(i);
//	//Serial.print("Creating " + name + "\n");
//	tsensoraddresses[MAX_TEMP_SENSOR_PER_HEATER] = {};
//	pin = -999;
//	current_temp = 32.0;
//	upper_limit = 33.0;
//	lower_limit = 32.0;
//	max_limit = 212.0;
//	status = false;
//	//Serial.print("Finished making " + name + "\n");
//}
//
//void HeaterClass::set_lower(float lower)
//{
//	lower_limit = lower;
//}
//
//void HeaterClass::set_upper(float upper)
//{
//	upper_limit = upper;
//}
//
//void HeaterClass::set_max(float max)
//{
//	max_limit = max;
//}
//
//void HeaterClass::return_heater_info() {
//	Serial.print("Heater name: ");
//	Serial.print(name);
//	Serial.print("\tHeater pin: ");
//	Serial.print(pin);
//	Serial.print("\tStatus: ");
//	Serial.print(status);
//	Serial.print("\tHeater upper: ");
//	Serial.print(upper_limit);
//	Serial.print("\tHeater lower: ");
//	Serial.print(lower_limit);
//	Serial.print("\tHeater current temp: ");
//	Serial.print(current_temp);
//	Serial.print("\tCurrent temp sensor name(s): ");
//	for (int i = 0; i < sizeof(tsensornames) / sizeof(tsensornames[0]); i++) {
//		Serial.print(tsensornames[i]);
//		Serial.print(":");
//	}
//	Serial.println();
//}
//
//void HeaterClass::add_temp_sensor(String tsensorname)
//{
//	Serial.print("Adding sensorname: ");
//	Serial.println(tsensorname);
//	Serial.print("to Heater: ");
//	Serial.println(name);
//	for (int i = 0; sizeof(tsensornames) / sizeof(tsensornames[0]); i++) {
//		if (tsensornames[i] == "") {
//			tsensornames[i] = tsensorname;
//			return;
//		}
//	}
//}
//
//void HeaterClass::clear_temp_sensors()
//{
//	DeviceAddress tsensoraddresses[MAX_TEMP_SENSOR_PER_HEATER] = {};
//}
//
//void HeaterClass::turn_on_pin()
//{
//	digitalWrite(pin, HIGH);
//}
//
//void HeaterClass::getMaxTemp(DallasTemperature& sensors)
//{
//	float new_temp = 0.0;
//	byte addr[8];
//
//	// Go through the sensor temperatures and grab the highest temperature
//	for (uint8_t i = 0; i < MAX_TEMP_SENSOR_PER_HEATER; i++) {
//		float tsensor_tempF = getTempByDevice(tsensoraddresses[i], sensors);
//		new_temp = max(new_temp, tsensor_tempF);
//	}
//
//	if (new_temp != 0.0) {
//		current_temp = new_temp;
//	}
//}
//
//void HeaterClass::setName(String new_name)
//{
//	name = new_name;
//	Serial.println("Set Heater name to: " + name);
//}
//
//void HeaterClass::setPin(int new_pin)
//{
//	Serial.println("Setting " + name + " pin to: " + new_pin);
//	pin = new_pin;
//	pinMode(pin, OUTPUT);
//	digitalWrite(pin, LOW);
//}
//
//void HeaterClass::check_setpoints()
//{
//	int val = digitalRead(pin);
//	// If the pin is on, then run checks to see if pin should be off.
//	if (val == HIGH) {
//		// Check if the current temperature is above the max limits
//		if (current_temp > upper_limit || current_temp > max_limit) {
//			digitalWrite(pin, LOW);
//		};
//	};
//	if (val == LOW) {
//		// Check if the current temperature is below the lower setpoint
//		if (current_temp < lower_limit) {
//			digitalWrite(pin, HIGH);
//		};
//	};
//}
//
//float getTempByDevice(DeviceAddress deviceAddress, DallasTemperature& sensors) {
//	if (!sensors.validAddress(deviceAddress)) {
//		return 0.0;
//	}
//	byte addr[8];
//	for (uint8_t j = 0; j < 8; j++) {
//		addr[j] = deviceAddress[j];
//		Serial.print(addr[j], HEX);
//	}
//
//	float tempF = sensors.getTempF(addr);
//	return tempF;
//}