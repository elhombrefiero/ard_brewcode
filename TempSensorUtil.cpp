
#include "DallasTemperature.h"



//// Print device addresses on the bus
//void getDeviceAddress(OneWire& instance) {
//    byte i;
//    byte addr[8];
//
//    Serial.println("Getting the addresses...\n\r");
//    /* initiate a search for the OneWire object we created and read its value into
//    addr array we declared above*/
//
//    while (instance.search(addr)) {
//        Serial.print("The address is:\t");
//        //read each byte in the address array
//        for (i = 0; i < 8; i++) {
//            Serial.print("0x");
//            if (addr[i] < 16) {
//                Serial.print('0');
//            }
//            // print each byte in the address array in hex format
//            Serial.print(addr[i], HEX);
//            if (i < 7) {
//                Serial.print(", ");
//            }
//        }
//        // a check to make sure that what we read is correct.
//        if (OneWire::crc8(addr, 7) != addr[7]) {
//            Serial.print("CRC is not valid!\n");
//            return;
//        }
//        Serial.println();
//    }
//    instance.reset_search();
//    return;
//}

// Print temperature sensor info
//void printTSensorInfo(uint8_t*) {
//    // Argument is an array of size 8
//    for 
//}