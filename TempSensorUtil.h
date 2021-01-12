// TempSensorUtil.h

#ifndef _TEMPSENSORUTIL_h
#define _TEMPSENSORUTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "DallasTemperature.h"
#else
#include "WProgram.h"
#endif

void printAddress(DeviceAddress deviceAddress);
void getDeviceAddress(OneWire& instance);

#endif