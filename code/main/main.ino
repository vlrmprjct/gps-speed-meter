// GPS Speedometer v1.0.3
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

// 0 : SERIAL PRINT OFF
// 1 : SERIAL PRINT ON
bool debug = 0;

// 0 : TEST DISPLAY OFF
// 1 : TEST DISPLAY ON
bool test = 0;

#define DATA 4
#define CLK 3
#define LOAD 2

LedControl lc(DATA, CLK, LOAD);
TinyGPSPlus gps;

int stateLED = LOW;
unsigned long last = 0UL;

void setup() {

    // SERIAL USB CONNECTION
    // Serial.begin(115200);

    // SERIAL CONNECTION ON DEVICE TX + RX
    // ATTINY1634
    Serial.begin(9600);
    // ARDUINO PRO MICRO
    // Serial1.begin(9600);

    // LED DISPLAY SETUP
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);

    // STATUS LED
    pinMode(8, OUTPUT);
}

void loop() {

    while (Serial.available()) {

        gps.encode(Serial.read());

        if (millis() - last > 1000) {

            if (debug)
                serialMonitor(gps.speed.kmph(), gps.satellites.value());

            lc.shutdown(0, false);

            // NORMAL GPS OUTPUT
            if(!test)
                printDigit(gps.speed.kmph(), false);

            // TEST DISPLAY OUTPUT
            if(test)
                printDigit(randomDouble(125.00, 135.00), false);

            if (gps.charsProcessed() < 10) {
                printDigit(404, false);
            }

            last = millis();

            stateLED = (stateLED == LOW) ? HIGH : LOW;
            digitalWrite(8, stateLED);
        }
    }
}
