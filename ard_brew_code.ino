/*
 Name:		    ard_brew_code.ino
 Description:	Controls a series of heaters and pumps based on
				temperature sensor readings.
 Author:	    Rene Valdez
*/

// the setup function runs once when you press reset or power the board
#include "valve.h"
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

void setup() {
	Serial.begin(9600);
	while (!Serial);
	delay(10);
	Serial.println("Beginning brew process...");
	init_temp_sensors(sensors);
	// Uncomment the following lines for debugging
	/*
	add_heater(); 
	add_heater(); 
	update_heater_tsensor(0,  sensors, 0);
	update_heater_setpoint_low(0, 77.0);
	update_heater_setpoint_high(0, 79.0);
	update_heater_setpoint_low(1, 77.0);
	update_heater_setpoint_high(1, 79.0);
	update_heater_tsensor(1, sensors, 1);
	update_heater_pin(0, 6);
	update_heater_pin(1, 4);*/
}

// the loop function runs over and over again until power down or reset
void loop() {
	process_state(sensors);
	delay(5);
}
