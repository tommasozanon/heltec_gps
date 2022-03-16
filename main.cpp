// Change the code below by your sketch
// Code for Gps
#include <TinyGPS++.h>

TinyGPSPlus gps;

#include "HardwareSerial.h"
HardwareSerial gps_serial(2);

#define RXD2 16
#define TXD2 17

void setup() {
    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(9600);

    gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial.println("Serial Txd is on pin: " + String(TXD2));
    Serial.println("Serial Rxd is on pin: " + String(RXD2));
}

/*
void displayInfo() {
    gps.encode(gps_serial.read());
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

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

    Serial.println();
    Serial.println();
    delay(1000);
}



float latitude, longitude;

void loop() {

    if (gps_serial.available()) {
        Serial.print(char(gps_serial.read()));
        // displayInfo();
    }

    if (gps_serial.available()) {
        gps.encode(gps_serial.read());
        latitude = gps.location.lat();
        longitude = gps.location.lng();

        Serial.print("lat: ");
        Serial.println(latitude);

        Serial.print("lng: ");
        Serial.println(longitude);

        Serial.println(gps.location.isValid());
    }

}
*/

void printGPSInfo();
static void smartDelay(unsigned long ms);
void printTime();
void printDate();

void loop() {
    // print position, altitude, speed, time/date, and satellites:
    printGPSInfo();

    // "Smart delay" looks for GPS data while the Arduino's not doing anything else
    smartDelay(1000);
}

void printGPSInfo() {
    // Print latitude, longitude, altitude in feet, course, speed, date, time,
    // and the number of visible satellites.
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Long: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Alt: ");
    Serial.println(gps.altitude.feet());
    Serial.print("Course: ");
    Serial.println(gps.course.deg());
    Serial.print("Speed: ");
    Serial.println(gps.speed.mph());
    Serial.print("Date: ");
    printDate();
    Serial.print("Time: ");
    printTime();
    Serial.print("Sats: ");
    Serial.println(gps.satellites.value());
    Serial.println();
}

// This custom version of delay() ensures that the tinyGPS object
// is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        // If data has come in from the GPS module
        while (gps_serial.available())
            gps.encode(gps_serial.read()); // Send it to the encode function
                                           // tinyGPS.encode(char) continues to "load" the tinGPS object with new
                                           // data coming in from the GPS module. As full NMEA strings begin to come in
                                           // the tinyGPS library will be able to start parsing them for pertinent info
    } while (millis() - start < ms);
}

// printDate() formats the date into dd/mm/yy.
void printDate() {
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.println(gps.date.year());
}

// printTime() formats the time into "hh:mm:ss", and prints leading 0's
// where they're called for.
void printTime() {
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10)
        Serial.print('0');
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10)
        Serial.print('0');
    Serial.println(gps.time.second());
}