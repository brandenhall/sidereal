#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

const unsigned long timeoutDuration = 300000;             // 5 minute timeout
unsigned long lastButtonTime;                             // last time a button was pressed
uint8_t spins[] = {0, 0, 0, 0, 0, 0};                     // position of the side spins
const uint8_t spinFades[] = {64, 96, 128, 160, 192, 224}; // fade rate of the side spins
bool changing = false;                                    // rotating to new game state
uint8_t changingIndex;                                    // index of the changing process
uint8_t leftFacet;
uint8_t rightFacet;
uint8_t nextLeft;
uint8_t nextRight;
uint8_t leftState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t rightState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t leftBuild[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t rightBuild[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

bool checkSolved()
{
    bool solved = true;
    for (uint8_t i = 0; i < 6; ++i)
    {
        if (gameState[i] != currentLevel)
        {
            solved = false;
            break;
        }
    }
    return solved;
}

void setupPlayMode(unsigned long now)
{
    Serial.println("Setup Play mode...");
    writeLog("Mode: Play");
    writeLog("Level: " + String(currentLevel));
    spins[0] = 0;
    spins[1] = 0;
    spins[2] = 0;
    spins[3] = 0;
    spins[4] = 0;
    spins[5] = 0;
    enableButtons();
    lastButtonTime = now;
}

void loopPlayMode(unsigned long now)
{
    if (now - lastButtonTime > timeoutDuration)
    {
        changeMode(MODE_ATTRACT, now);
        return;
    }

    if (!changing)
    {
        // buttons
        for (uint8_t i = 0; i < 6; ++i)
        {
            if (digitalRead(buttonPins[i]) == 0)
            {
                lastButtonTime = now;
                changing = true;
                changingIndex = 0;
                leftFacet = (i + 5) % 6;
                rightFacet = (i + 7) % 6;
                disableButtons();

                for (uint8_t j = 0; j < 10; ++j)
                {
                    uint8_t a = random(10);
                    uint8_t b = random(10);
                    uint8_t temp = leftBuild[a];
                    leftBuild[a] = leftBuild[b];
                    leftBuild[b] = temp;
                    leftState[j] = gameState[leftFacet];
                }

                for (uint8_t j = 0; j < 10; ++j)
                {
                    uint8_t a = random(10);
                    uint8_t b = random(10);
                    uint8_t temp = rightBuild[a];
                    rightBuild[a] = rightBuild[b];
                    rightBuild[b] = temp;
                    rightState[j] = gameState[rightFacet];
                }

                gameState[leftFacet] = (gameState[leftFacet] + 1) % levelNumStates[currentLevel];
                gameState[rightFacet] = (gameState[rightFacet] + 1) % levelNumStates[currentLevel];
                break;
            }
        }
    }
    else
    {
        EVERY_N_MILLISECONDS(15)
        {
            topLEDs[leftFacet].fadeToBlackBy(128);
            topLEDs[rightFacet].fadeToBlackBy(128);

            leftState[min(changingIndex, 9)] = gameState[leftFacet];
            rightState[min(changingIndex, 9)] = gameState[rightFacet];
            for (uint8_t i = 0; i < 10; ++i)
            {
                uint8_t state = leftState[i];
                uint8_t build = leftBuild[i];
                topLEDs[leftFacet][topSectors[state][build]] = colors[state];
                state = rightState[i];
                build = rightBuild[i];
                topLEDs[rightFacet][topSectors[state][build]] = colors[state];
            }

            changingIndex += 1;
            if (changingIndex == 20)
            {
                changing = false;
                changingIndex = 0;

                if (checkSolved())
                {
                    if (currentLevel < 5)
                    {
                        changeMode(MODE_SOLVE, now);
                    }
                    else
                    {
                        changeMode(MODE_WIN, now);
                    }
                }
                else
                {
                    enableButtons();
                }
            }
        }
    }
    // side spin
    EVERY_N_MILLISECONDS(60)
    {
        uint8_t size;
        for (uint8_t level = 0; level <= currentLevel && level < 5; ++level)
        {
            size = sideRingSizes[5 - level];

            for (uint8_t i = 0; i < 6; ++i)
            {
                for (uint8_t j = 0; j < size; ++j)
                {
                    sideLEDs[i][sideRings[5 - level][j]].fadeToBlackBy(spinFades[level]);
                }
                sideLEDs[i][sideRings[5 - level][spins[level]]] = colors[level];
                sideLEDs[i][sideRings[5 - level][(spins[level] + size / 2) % size]] = colors[level];
            }
            spins[level] = (spins[level] + 1) % size;
        }

        if (currentLevel == 5)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                sideLEDs[i][sideRings[0][0]].fadeToBlackBy(spinFades[currentLevel]);
                if (spins[currentLevel] == 0)
                {
                    sideLEDs[i][sideRings[0][0]] = colors[currentLevel];
                }
            }
            spins[currentLevel] = (spins[currentLevel] + 1) % 6;
        }
    }
}