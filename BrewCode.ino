/*
 Name:		    BrewCode.ino
 Description:	Controls a series of heaters and pumps based on
				temperature sensor readings.
 Author:	    Rene Valdez
*/

#include "OneWire.h"
#include "DallasTemperature.h"
/*
#include "SerialOutput.h"
#include "SerialInput.h"
#include "Heater.h"
#include "TempSensorUtil.h"
*/

// Define some constants
#define ONE_WIRE_PIN 10     // Data pin for the temperature sensors
#define MAX_TEMP_SENSORS 10 // TODO: Figure out way to define temp sensors in runtime
#define NUMBER_OF_HEATERS 3 // TODO: Figure out way to create heaters in runtime

// Setup a OneWire instance to communicate with oneWire devices
OneWire oneWire(ONE_WIRE_PIN);

// Create a DallasTemperature instance which takes in
// a reference to the oneWire object.
DallasTemperature sensors(&oneWire);

// Array of Device Addresses
DeviceAddress myDAddresses[MAX_TEMP_SENSORS];

// Array to hold pointers to the device addresses
uint8_t* myTSensors[MAX_TEMP_SENSORS];

// Create an array of pointers to heaters
//HeaterClass* myHeaters[NUMBER_OF_HEATERS];

// Create an integer that stores the number of tsensors
uint8_t number_of_sensors = 0;

// String that will keep incoming serial info.
String SerialInput = "";

// Logical used for software override
bool controller_override = FALSE;

// Debug variables
uint8_t MAX_COUNTER = 10;
uint8_t counter = 0;
bool turnOn = FALSE;
bool DEBUG = TRUE;

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	Serial.print("Beginning brew process...");
	Serial.println();

	// Put the pointers to the device addresses in the myTempSensor array
	for (int i = 0; i < MAX_TEMP_SENSORS; i++)
	{
		myTSensors[i] = myDAddresses[i];
	}

	// Print all serial information
	//getDeviceAddress(oneWire);

	// Setup the sensors and get the number on the bus
	sensors.begin();
	number_of_sensors = sensors.getDeviceCount();
	if (DEBUG) {
		Serial.print("Found ");
		Serial.print(number_of_sensors);
		Serial.println(" Temperature Sensors");
	}

	// Initialize the temp sensors
	for (int i = 0; i < number_of_sensors; i++) {
		if (DEBUG) {
			Serial.print("Creating temperature sensor ");
			Serial.println(i);
		}
		if (!sensors.getAddress(myTSensors[i], i))
		{
			Serial.print("Failed to create temp sensor ");
			Serial.println(i);
		}
		delay(10);
	}

	// Initialize the heaters
	/*for (int i = 0; i < NUMBER_OF_HEATERS; i++) {
		if (DEBUG) {
			Serial.print("Creating Heater ");
			Serial.println(i);
		}
		myHeaters[i] = new HeaterClass(i);
	}*/


}

void loop()
{
	// Run checks on heaters
	/*
	*     for (int i = 0; i < sizeof(myHeaters) / sizeof(myHeaters[0]); i++) {
		myHeaters[i].getMaxTemp(myTempSensors);
		myHeaters[i].check_setpoints();
	};
	*/
	//Serial.print("Start of loop");
	// Update the temperatures from every device
	sensors.requestTemperatures();

	// Check if a new OneWire has been added
	// Check number of sensors
	// new_number_sensors = check_sensors()
	// if (new_number_sensors != num_sensors) {
	// redo the sensor arrays
	//}

	// serial read section
	//Serial.print("Start of serial read");
	//while (Serial.available()) {
	//	if (Serial.available() > 0) {
	//		parse_serial(SerialInput, *myTempSensors, number_of_sensors, *myHeaters, sensors);
	//	}
	//}

	// Debug printing statements
	if (DEBUG) {
		printTempSensors();
		if (turnOn) {
			Serial.println("Turning on LEDs");
			digitalWrite(4, HIGH);
			digitalWrite(6, HIGH);
			turnOn = FALSE;
		}
		else {
			Serial.println("Turning off LEDs");
			digitalWrite(4, LOW);
			digitalWrite(6, LOW);
			turnOn = TRUE;
		}
	}

	counter = counter + 1;
	if (counter >= MAX_COUNTER) {
		Serial.print("There have been ");
		Serial.print(MAX_COUNTER);
		Serial.println(" cycles. Resetting counter...");
		counter = 0;
	}


	// Put a little delay here to avoid overloading the Arduino
	if (DEBUG) {
		delay(1000);
	}

}

void printTempSensors() {
	// Temp Sensor info
	Serial.println("Printing Temp Sensor info.");
	for (uint8_t i = 0; i < number_of_sensors; i++) {
		Serial.print("Temp sensor ");
		Serial.print(i);
		Serial.print(" : ");
		printAddress(myTSensors[i]);
		Serial.print("Temperature: ");
		Serial.print(sensors.getTempFByIndex(i));
		Serial.println(" F");
		Serial.println();
	}
	delay(10);
}

void displayAllTSensorSerials() {
	return;
}

void switchPin(int pin_num) {
	int current_status = digitalRead(pin_num);
	Serial.print("Pin number ");
	Serial.print(pin_num);
	Serial.print(" is ");
	Serial.println(current_status);

	if (current_status == LOW) {
		digitalWrite(pin_num, HIGH);
	}
	else {
		digitalWrite(pin_num, LOW);
	}
	delay(1);

}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (deviceAddress[i] < 16) Serial.print("0");
		Serial.print(deviceAddress[i], HEX);
	}
}
