#include <Arduino.h>
#include <FastLED.h>
#include "../io.h"
#include "../leds.h"
#include "../mode.h"
#include "../music.h"

uint8_t sectorBuild[][10] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
};
uint8_t sectorBuildIndex = 0;
bool levelThemePlaying = false;

void setupScrambleMode(unsigned long now)
{
    Serial.println("Setup Startup mode...");

    // scramble the game state for the level
    bool ready = false;
    uint8_t levelState = levelStates[currentLevel];
    while (!ready)
    {
        gameState[0] = 0;
        gameState[1] = 0;
        gameState[2] = 0;
        gameState[3] = 0;
        gameState[4] = 0;
        gameState[5] = 0;

        for (uint8_t i = 0; i < levelScrambles[currentLevel]; ++i)
        {
            uint8_t facet = random(6);
            uint8_t left = (facet + 5) % 6;
            uint8_t right = (facet + 7) % 6;
            gameState[left] = (gameState[left] + levelState - 1) % levelState;
            gameState[right] = (gameState[right] + levelState - 1) % levelState;
        }

        ready = false;
        for (uint8_t i = 1; i < 6; ++i)
        {
            if (gameState[0] != gameState[i])
            {
                ready = true;
                break;
            }
        }
    }
    // scramble the build plan for the sectors
    for (uint8_t i = 0; i < 6; ++i)
    {
        for (uint8_t j = 0; j < 10; ++j)
        {
            uint8_t a = random(10);
            uint8_t b = random(10);
            uint8_t temp = sectorBuild[i][a];
            sectorBuild[i][a] = sectorBuild[i][b];
            sectorBuild[i][b] = temp;
        }
    }
    sectorBuildIndex = 0;
    levelThemePlaying = false;
    printGameState();
}

void loopScrambleMode(unsigned long now)
{
    if (now - modeStartTime < 2500)
    {
        EVERY_N_MILLISECONDS(30)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                sideLEDs[i].fadeToBlackBy(64);
                topLEDs[i].fadeToBlackBy(64);
            }
        }
    }
    else if (sectorBuildIndex < 10)
    {
        if (!levelThemePlaying)
        {
            levelThemePlaying = true;
            playMusic(levelThemes[currentLevel], levelThemeSizes[currentLevel], now);
        }
        EVERY_N_MILLISECONDS(100)
        {
            for (uint8_t i = 0; i < 6; ++i)
            {
                topLEDs[i][topSectors[gameState[i]][sectorBuild[i][sectorBuildIndex]]] = colors[gameState[i]];
            }
            sectorBuildIndex += 1;
        }
    }
    else
    {
        changeMode(MODE_PLAY, now);
    }
}