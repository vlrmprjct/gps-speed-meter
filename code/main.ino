// GPS Speedometer
// Copyright (c) 2021 Thomas Meschke
//
// MIT License
// https://opensource.org/licenses/mit-license.php
//
// Put the GPS Module ( NEO-6M-x ) on the following pins:
// TX: Arduino Pro Micro / ATTINY 1634 => RX Pin
// RX: Arduino Pro Micro / ATTINY 1634 => TX Pin
//
// Important note:
// By using an ATTINY 1634 use Serial() instead of Serial1() !
//

#include <LedControl.h>;
#include <TinyGPS++.h>;

// 0 : ATTINY1634
// 1 : ARDUINO PRO MICRO
bool plattform = 0;

// 0 : SERIAL PRINT OFF
// 1 : SERIAL PRINT ON
bool debug = 0;

#define DATA 4
#define CLK 3
#define LOAD 2

LedControl lc(DATA, CLK, LOAD);
TinyGPSPlus gps;

unsigned long last = 0UL;

void setup() {

    // SERIAL USB CONNECTION
    if (debug && plattform)
        Serial.begin(115200);

    // SERIAL CONNECTION ON DEVICE TX + RX
    (plattform) ? Serial.begin(9600) : Serial1.begin(9600);

    // LED DISPLAY SETUP
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
}

void loop() {

    while ((plattform) ? Serial.read() : Serial1.read()) {

        gps.encode((plattform) ? Serial.read() : Serial1.read());

        if (millis() - last > 1000) {

            if (debug && plattform)
                serialMonitor(gps.speed.kmph(), gps.satellites.value());

            lc.shutdown(0, false);
            printDigit(gps.speed.kmph() * 100, false);

            // TEST DISPLAY OUTPUT
            // printDigit(randomDouble(25.00, 32.00), false);

            if (gps.charsProcessed() < 10) {
                printDigit(404, false);
            }

            last = millis();
        }
    }
}
