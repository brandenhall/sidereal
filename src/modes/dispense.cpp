#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

uint8_t topArrowIndex;
uint8_t sideArrowIndex;
uint8_t dispenseState;
const uint dispenseTime = 4000;
const uint dispenseDuration = 1500;

void setupDispenseMode(unsigned long now)
{
    Serial.println("Setup Dispense mode...");
    writeLog("Mode: Dispense");
    disableButtons();
    dispenseState = 0;
}

void loopDispenseMode(unsigned long now)
{
    unsigned long duration = now - modeStartTime;

    EVERY_N_MILLISECONDS(60)
    {
        if (duration < 20000)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                sideLEDs[i].fadeToBlackBy(200);
                topLEDs[i].fadeToBlackBy(200);
            }

            // release the prize ball!
            if (duration > dispenseTime && dispenseState == 0)
            {
                dispenseState = 1;
                digitalWrite(prizeReleasePin, HIGH);
                for (uint8_t i = 0; i < 6; ++i)
                {
                    sideLEDs[i].fill_solid(colors[i]);
                    topLEDs[i].fill_solid(colors[i]);
                }
            }
            else if (duration > dispenseTime + dispenseDuration && dispenseState == 1)
            {
                dispenseState = 2;
                digitalWrite(prizeReleasePin, LOW);
            }

            if (sideArrowIndex < 8)
            {
                for (uint8_t i = 0; i < sideArrowSizes[sideArrowIndex]; ++i)
                {
                    sideLEDs[0][sideArrows[sideArrowIndex][i]] = CRGB::White;
                }
            }

            if (topArrowIndex < 5)
            {
                for (uint8_t i = 0; i < topArrowSizes[topArrowIndex]; ++i)
                {
                    topLEDs[0][topArrows[topArrowIndex][i]] = CRGB::White;
                }
            }

            sideArrowIndex += 1;
            topArrowIndex += 1;
            if (sideArrowIndex > 12)
            {
                sideArrowIndex = 0;
                topArrowIndex = 0;
            }
        }
        else
        {
            changeMode(MODE_COOLDOWN, now);
        }
    }
}