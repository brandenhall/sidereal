#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../music.h"

void setupPlayMode(unsigned long now)
{
    Serial.println("Setup Startup mode...");
    enableButtons();
}

void loopPlayMode(unsigned long now)
{
}