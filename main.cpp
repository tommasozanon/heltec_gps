// Change the code below by your sketch
// Code for Gps
#include <TinyGPS++.h>

TinyGPSPlus gps;

#include "HardwareSerial.h"
HardwareSerial gps_serial(2);

#define RXD2 16
#define TXD2 17
void displayInfo() {
    if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
        Serial.print("Altitude: ");
        Serial.println(gps.altitude.meters());
    } else {
        Serial.println("Location: Not Available");
    }

    Serial.print("Date: ");
    if (gps.date.isValid()) {
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.println(gps.date.year());
    } else {
        Serial.println("Not Available");
    }

    Serial.print("Time: ");
    if (gps.time.isValid()) {
        if (gps.time.hour() < 10)
            Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(":");
        if (gps.time.minute() < 10)
            Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(":");
        if (gps.time.second() < 10)
            Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(".");
        if (gps.time.centisecond() < 10)
            Serial.print(F("0"));
        Serial.println(gps.time.centisecond());
    } else {
        Serial.println("Not Available");
    }

    Serial.println();
    Serial.println();
    delay(1000);
}

void setup() {
    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(9600);

    gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);

    Serial.println("Serial Txd is on pin: " + String(TX));
    Serial.println("Serial Rxd is on pin: " + String(RX));
}

void loop() {
    while (gps_serial.available()) {
        Serial.print(char(gps_serial.read())); // read from gps, write to serial debug port
        //  Serial.println(gps.time.hour());
        // delay(500);                            ///*
        // Serial.println(gps.location.isValid());

        //*/
        // Serial.println(gps.location.lng());
        // displayInfo();
    }
}