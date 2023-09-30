#include <Arduino.h>
#include "io.h"

bool buttonsActive = false;
uint8_t const buttonPins[6] = {11, 12, 24, 25, 26, 27};
uint8_t const buttonLEDPin = 8;
uint8_t const prizeReleasePin = 41;

void setupButtons()
{
    for (uint8_t i = 0; i < 6; ++i)
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void enableButtons()
{
    buttonsActive = true;
    digitalWrite(buttonLEDPin, HIGH);
}

void disableButtons()
{
    buttonsActive = false;
    digitalWrite(buttonLEDPin, LOW);
}