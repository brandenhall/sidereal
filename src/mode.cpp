#include <Arduino.h>
#include "mode.h"
#include "modes/attract.h"
#include "modes/cooldown.h"
#include "modes/play.h"
#include "modes/post.h"
#include "modes/scramble.h"
#include "modes/solve.h"
#include "modes/startup.h"
#include "modes/win.h"

uint8_t currentMode = 0;
unsigned long modeStartTime = 0;
uint8_t currentLevel = 0;
uint8_t gameState[] = {0, 0, 0, 0, 0, 0};
const uint8_t levelScrambles[] = {2, 4, 6, 8, 10, 12};
const uint8_t levelStates[] = {2, 3, 4, 5, 6, 6};

void printGameState()
{
    Serial.print("Game state: ");
    for (uint8_t i = 0; i < 6; ++i)
    {
        Serial.print(gameState[i]);
        Serial.print(" ");
    }
    Serial.println("");
}

void changeMode(uint8_t nextMode, unsigned long now)
{
    currentMode = nextMode;
    modeStartTime = now;

    switch (nextMode)
    {
    case MODE_POST:
        setupPostMode(now);
        break;
    case MODE_ATTRACT:
        setupAttractMode(now);
        break;
    case MODE_STARTUP:
        setupStartupMode(now);
        break;
    case MODE_SCRAMBLE:
        setupScrambleMode(now);
        break;
    case MODE_PLAY:
        setupPlayMode(now);
        break;
    case MODE_SOLVE:
        setupSolveMode(now);
        break;
    case MODE_WIN:
        setupWinMode(now);
        break;
    case MODE_COOLDOWN:
        setupCooldownMode(now);
        break;
    }
}

void loopMode(unsigned long now)
{
    switch (currentMode)
    {
    case MODE_POST:
        loopPostMode(now);
        break;
    case MODE_ATTRACT:
        loopAttractMode(now);
        break;
    case MODE_STARTUP:
        loopStartupMode(now);
        break;
    case MODE_SCRAMBLE:
        loopScrambleMode(now);
        break;
    case MODE_PLAY:
        loopPlayMode(now);
        break;
    case MODE_SOLVE:
        loopSolveMode(now);
        break;
    case MODE_WIN:
        loopWinMode(now);
        break;
    case MODE_COOLDOWN:
        loopCooldownMode(now);
        break;
    }
}