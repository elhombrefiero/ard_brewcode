/*
 Name:		    ard_brew_code.ino
 Description:	Controls a series of heaters and pumps based on
				temperature sensor readings.
 Author:	    Rene Valdez
*/

// the setup function runs once when you press reset or power the board
//#include "valve.h"
#include "heater.h"
#include "user_io.h"
#include "arduino.h"
#include "control.h"
#include <ArduinoJson.h>
#include "tsensor.h"
#include "pump.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ArduinoSTL.h>
// Data pin for the temperature sensors
#define ONE_WIRE_PIN 10
// Setup a OneWire instance to communicate with oneWire devices
OneWire oneWire(ONE_WIRE_PIN);
/* Create a DallasTemperature instance which takes in
a reference to the oneWire object. */
DallasTemperature sensors(&oneWire);
std::vector<uint8_t*> tsensors;

void setup() {
	Serial.begin(9600);
	while (!Serial);
	delay(10);
	Serial.println("Beginning brew process...");
	init_temp_sensors(sensors, tsensors);
	add_heater(); // DELETE
	int hindex_to_use = 0;  // DELETE
	int tsensor_ind_to_use = 0;  // DELETE
	update_heater_tsensor(hindex_to_use,  sensors, tsensor_ind_to_use); // DELETE
	update_heater_pin(0, 6);
}

// the loop function runs over and over again until power down or reset
void loop() {
	process_state(sensors, tsensors);
	delay(1000);
}
