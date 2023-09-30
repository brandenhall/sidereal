#include <Arduino.h>
#include "music.h"

bool musicPlaying = false;
uint musicIndex = 0;
uint musicEnd = 0;
unsigned long musicStartTime = 0;

music *currentMusic;
const uint8_t malletPins[] = {33, 34, 35, 36, 37, 38, 39, 40};
unsigned long malletTimes[] = {0, 0, 0, 0, 0, 0, 0, 0};

music attractTheme0[] = {
    {0, 64},
    {1000, 32},
    {1125, 4},
    {3250, 16},
    {4500, 32},
    {4625, 8},
    {6750, 64},
    {7875, 32},
    {8000, 128}};

music attractTheme1[] = {
    {0, 64},
    {1000, 128},
    {2000, 16},
    {3000, 1},
    {4000, 4},
    {6000, 64},
    {7000, 128},
    {8000, 16},
    {9000, 1},
    {10000, 4}};

music attractTheme2[] = {
    {0, 1},
    {500, 36},
    {1000, 128},
    {1500, 48},
    {2000, 1},
    {2500, 36},
    {3000, 128},
    {3250, 16},
    {3500, 4},
    {4000, 132}};

music attractTheme3[] = {
    {0, 1},
    {1000, 16},
    {2000, 8},
    {3000, 128},
    {4000, 1},
    {5000, 16},
    {5500, 1},
    {6000, 8},
    {7000, 128},
    {7500, 32}};

music attractTheme4[] = {
    {0, 48},
    {1000, 4},
    {2000, 48},
    {3000, 32},
    {4000, 20},
    {5000, 1},
    {6000, 164}};

music attractTheme5[] = {
    {0, 4},
    {500, 8},
    {1000, 4},
    {1500, 32},
    {2000, 1},
    {2500, 8},
    {3000, 4},
    {3500, 128},
    {4000, 32},
    {4250, 16},
    {4500, 8}};

const uint attractThemeSizes[] = {
    sizeof(attractTheme0) / sizeof(music),
    sizeof(attractTheme1) / sizeof(music),
    sizeof(attractTheme2) / sizeof(music),
    sizeof(attractTheme3) / sizeof(music),
    sizeof(attractTheme4) / sizeof(music),
    sizeof(attractTheme5) / sizeof(music)};
music *attractThemes[] = {attractTheme0, attractTheme1, attractTheme2, attractTheme3, attractTheme4, attractTheme5};

music levelTheme0[] = {
    {0, 33}};

music levelTheme1[] = {
    {0, 2},
    {375, 64}};

music levelTheme2[] = {
    {0, 128},
    {250, 8},
    {500, 4}};

music levelTheme3[] = {
    {0, 32},
    {500, 1},
    {1000, 4},
    {1500, 8}};

music levelTheme4[] = {
    {0, 64},
    {500, 32},
    {1000, 128},
    {1250, 8},
    {1500, 16}};

music levelTheme5[] = {
    {0, 32},
    {500, 16},
    {1000, 8},
    {1500, 4},
    {1750, 2},
    {2000, 33}};

const uint levelThemeSizes[] = {
    sizeof(levelTheme0) / sizeof(music),
    sizeof(levelTheme1) / sizeof(music),
    sizeof(levelTheme2) / sizeof(music),
    sizeof(levelTheme3) / sizeof(music),
    sizeof(levelTheme4) / sizeof(music),
    sizeof(levelTheme5) / sizeof(music)};
music *levelThemes[] = {levelTheme0, levelTheme1, levelTheme2, levelTheme3, levelTheme4, levelTheme5};

music mainTheme[] = {
    {0, 1},
    {500, 2},
    {750, 4},
    {1250, 8},
    {1500, 16},
    {1750, 32},
    {2000, 1},
    {2125, 4},
    {2250, 8},
    {2375, 32},
    {2500, 1},
    {3000, 32}};
const uint mainThemeSize = sizeof(mainTheme) / sizeof(music);

music solveTheme[] = {
    {0, 32},
    {125, 1},
    {250, 8},
    {375, 32},
    {750, 41}};
const uint solveThemeSize = sizeof(solveTheme) / sizeof(music);

music winTheme[] = {
    {0, 128},
    {125, 1},
    {250, 4},
    {375, 16},
    {500, 128},
    {875, 132},
    {1500, 48},
    {1750, 8},
    {2000, 4},
    {2250, 129},
    {2500, 32},
    {2750, 16},
    {3000, 8},
    {3250, 4},
    {3500, 1},
    {3750, 144},
    {4375, 17},
    {4625, 8},
    {4875, 4},
    {5125, 128},
    {5375, 32},
    {5625, 1},
    {5875, 136},
    {6125, 32},
    {6375, 16},
    {6625, 20}};
const uint winThemeSize = sizeof(winTheme) / sizeof(music);

void playMusic(music *nextMusic, uint length, unsigned long now)
{
    musicPlaying = true;
    currentMusic = nextMusic;
    musicIndex = 0;
    musicEnd = length;
    musicStartTime = now;
}

void swingMallet(uint8_t index, unsigned long now)
{
    digitalWrite(malletPins[index], HIGH);
    malletTimes[index] = now;
}

void updateMusic(unsigned long now)
{
    unsigned long malletTime;

    for (uint8_t i = 0; i < 8; ++i)
    {
        malletTime = malletTimes[i];
        if (malletTime > 0 && now - malletTime >= MALLET_DURATION)
        {
            malletTimes[i] = 0;
            digitalWrite(malletPins[i], LOW);
        }
    }

    // handle music
    if (musicPlaying)
    {
        unsigned long duration = now - musicStartTime;
        uint8_t chord;
        bool complete = false;

        if (musicIndex < musicEnd)
        {
            // see if a new chords is ready
            if (duration >= (*currentMusic).time)
            {

                chord = (*currentMusic).chord;
                for (uint8_t i = 0; i < 8; ++i)
                {
                    if (((chord >> i) & 0x01) == 1)
                    {
                        swingMallet(i, now);
                    }
                }

                musicIndex += 1;

                if (musicIndex >= musicEnd)
                {
                    complete = true;
                }
                else
                {
                    currentMusic += 1; // pointer math, SCARY!
                }
            }
        }
        musicPlaying = !complete;
    }
}