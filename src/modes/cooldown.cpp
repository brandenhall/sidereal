#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

const unsigned long cooldownTime = 60000;

void setupCooldownMode(unsigned long now)
{
    Serial.println("Setup Cooldown  mode...");
    writeLog("Mode: Cooldown");
    disableButtons();
}

void loopCooldownMode(unsigned long now)
{
    EVERY_N_MILLISECONDS(60)
    {
        for (uint8_t i = 0; i < 6; ++i)
        {
            sideLEDs[i].fadeToBlackBy(160);
            topLEDs[i].fadeToBlackBy(160);
        }

        if (now - modeStartTime > cooldownTime)
        {
            changeMode(MODE_ATTRACT, now);
        }
    }
}