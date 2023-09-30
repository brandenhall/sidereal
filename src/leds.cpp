#include <Arduino.h>
#include <FastLED.h>
#include "leds.h"

const uint8_t topSectors[][10] = {
    {0, 1, 2, 3, 7, 6, 5, 11, 12, 18},
    {0, 8, 7, 9, 10, 11, 21, 20, 19, 18},
    {21, 20, 19, 18, 22, 23, 24, 32, 31, 33},
    {18, 24, 25, 31, 30, 29, 33, 34, 35, 36},
    {18, 17, 16, 15, 25, 26, 27, 29, 28, 36},
    {3, 5, 4, 12, 13, 14, 18, 17, 16, 15},
};

const uint8_t topRing0[] = {18};
const uint8_t topRing1[] = {11, 12, 17, 25, 24, 19};
const uint8_t topRing2[] = {7, 6, 5, 13, 16, 26, 29, 30, 31, 23, 20, 10};
const uint8_t topRing3[] = {0, 1, 2, 3, 4, 14, 15, 27, 28, 36, 35, 34, 33, 32, 22, 21, 9, 8};
const uint8_t topRingSizes[] = {sizeof(topRing0), sizeof(topRing1), sizeof(topRing2), sizeof(topRing3)};
const uint8_t *topRings[] = {topRing0, topRing1, topRing2, topRing3};

const uint8_t topArrow0[] = {1, 2, 6};
const uint8_t topArrow1[] = {0, 7, 11, 18, 12, 5, 3};
const uint8_t topArrow2[] = {8, 10, 19, 24, 30, 25, 17, 13, 4};
const uint8_t topArrow3[] = {9, 20, 23, 31, 34, 35, 29, 26, 16, 14};
const uint8_t topArrow4[] = {21, 22, 32, 33, 36, 28, 27, 15};
const uint8_t topArrowSizes[] = {sizeof(topArrow0), sizeof(topArrow1), sizeof(topArrow2), sizeof(topArrow3), sizeof(topArrow4)};
const uint8_t *topArrows[] = {topArrow0, topArrow1, topArrow2, topArrow3, topArrow4};

const uint8_t sideRing0[] = {45};
const uint8_t sideRing1[] = {35, 34, 46, 55, 56, 44};
const uint8_t sideRing2[] = {24, 25, 26, 33, 47, 54, 66, 65, 64, 57, 43, 36};
const uint8_t sideRing3[] = {18, 17, 16, 15, 27, 32, 48, 53, 67, 72, 73, 74, 75, 63, 58, 42, 37, 23};
const uint8_t sideRing4[] = {7, 8, 9, 10, 11, 14, 28, 31, 49, 52, 68, 71, 83, 82, 81, 80, 79, 76, 62, 59, 41, 38, 22, 19};
const uint8_t sideRing5[] = {5, 4, 3, 2, 1, 0, 12, 13, 29, 30, 50, 51, 69, 70, 84, 85, 86, 87, 88, 89, 90, 78, 77, 61, 60, 40, 39, 21, 20, 6};
const uint8_t sideRingSizes[] = {sizeof(sideRing0), sizeof(sideRing1), sizeof(sideRing2), sizeof(sideRing3), sizeof(sideRing4), sizeof(sideRing5)};
const uint8_t *sideRings[] = {sideRing0, sideRing1, sideRing2, sideRing3, sideRing4, sideRing5};

const uint8_t sideArrow0[] = {3, 2, 9};
const uint8_t sideArrow1[] = {4, 8, 17, 25, 16, 10, 1};
const uint8_t sideArrow2[] = {5, 7, 18, 24, 35, 45, 34, 26, 15, 11, 0};
const uint8_t sideArrow3[] = {6, 19, 23, 36, 44, 56, 65, 55, 46, 33, 27, 14, 12};
const uint8_t sideArrow4[] = {20, 22, 37, 43, 57, 64, 74, 81, 73, 66, 54, 47, 32, 28, 13};
const uint8_t sideArrow5[] = {21, 38, 42, 58, 63, 75, 80, 88, 87, 82, 72, 67, 53, 48, 31, 29};
const uint8_t sideArrow6[] = {39, 41, 59, 62, 76, 79, 89, 86, 83, 71, 68, 52, 49, 30};
const uint8_t sideArrow7[] = {40, 60, 61, 77, 78, 90, 85, 84, 70, 69, 51, 50};
const uint8_t sideArrowSizes[] = {sizeof(sideArrow0), sizeof(sideArrow1), sizeof(sideArrow2), sizeof(sideArrow3), sizeof(sideArrow4), sizeof(sideArrow5), sizeof(sideArrow6), sizeof(sideArrow7)};
const uint8_t *sideArrows[] = {sideArrow0, sideArrow1, sideArrow2, sideArrow3, sideArrow4, sideArrow5, sideArrow6, sideArrow7};

const int8_t sideLinks[][6] = {
    {-1, -1, 12, 11, 1, -1},  // 0
    {-1, 0, 11, 10, 2, -1},   // 1
    {-1, 1, 10, 9, 3, -1},    // 2
    {-1, 2, 9, 8, 4, -1},     // 3
    {-1, 3, 8, 7, 5, -1},     // 4
    {-1, 4, 7, 6, -1, -1},    // 5
    {5, 7, 19, 20, -1, -1},   // 6
    {4, 8, 18, 19, 6, 5},     // 7
    {3, 9, 17, 18, 7, 4},     // 8
    {2, 10, 16, 17, 8, 3},    // 9
    {1, 11, 15, 16, 9, 2},    // 10
    {0, 12, 14, 15, 10, 1},   // 11
    {-1, -1, 13, 14, 11, 0},  // 12
    {-1, -1, 29, 28, 14, 12}, // 13
    {12, 13, 28, 27, 15, 11}, // 14
    {11, 14, 27, 26, 16, 10}, // 15
    {10, 15, 26, 25, 17, 9},  // 16
    {9, 16, 25, 24, 18, 8},   // 17
    {8, 17, 24, 23, 19, 7},   // 18
    {7, 18, 23, 22, 20, 6},   // 19
    {06, 19, 22, 21, -1, -1}, // 20
    {20, 22, 38, 39, -1, -1}, // 21
    {19, 23, 37, 38, 21, 20}, // 22
    {18, 24, 36, 37, 22, 19}, // 23
    {17, 25, 35, 36, 23, 18}, // 24
    {16, 26, 34, 35, 24, 17}, // 25
    {15, 27, 33, 34, 25, 16}, // 26
    {14, 28, 32, 33, 26, 15}, // 27
    {13, 29, 31, 32, 27, 14}, // 28
    {-1, -1, 30, 31, 28, 13}, // 29
    {-1, -1, 50, 49, 31, 29}, // 30
    {29, 30, 49, 48, 32, 28}, // 31
    {28, 31, 48, 47, 33, 27}, // 32
    {27, 32, 47, 46, 34, 26}, // 33
    {26, 33, 46, 45, 35, 25}, // 34
    {25, 34, 45, 44, 36, 24}, // 35
    {24, 35, 44, 43, 37, 23}, // 36
    {23, 36, 43, 42, 38, 22}, // 37
    {22, 37, 42, 41, 39, 21}, // 38
    {21, 38, 41, 40, -1, -1}, // 39
    {39, 41, 60, -1, -1, -1}, // 40
    {38, 42, 59, 60, 40, 39}, // 41
    {37, 43, 58, 59, 41, 38}, // 42
    {36, 44, 57, 58, 42, 37}, // 43
    {35, 45, 56, 57, 43, 36}, // 44
    {34, 46, 55, 56, 44, 35}, // 45
    {33, 47, 54, 55, 45, 34}, // 46
    {32, 48, 53, 54, 46, 33}, // 47
    {31, 49, 52, 53, 47, 32}, // 48
    {30, 50, 51, 52, 48, 31}, // 49
    {-1, -1, -1, 51, 49, 30}, // 50
    {50, -1, -1, 69, 52, 49}, // 51
    {49, 51, 69, 68, 53, 48}, // 52
    {48, 52, 68, 67, 54, 47}, // 53
    {47, 53, 67, 66, 55, 46}, // 54
    {46, 54, 66, 65, 56, 45}, // 55
    {45, 55, 65, 64, 57, 44}, // 56
    {44, 56, 64, 63, 58, 43}, // 57
    {43, 57, 63, 62, 59, 42}, // 58
    {42, 58, 62, 61, 60, 41}, // 59
    {41, 59, 61, -1, -1, 40}, // 60
    {59, 62, 77, -1, -1, 62}, // 61
    {58, 63, 76, 77, 61, 59}, // 62
    {57, 64, 75, 76, 62, 58}, // 63
    {56, 65, 74, 75, 63, 57}, // 64
    {55, 66, 73, 74, 64, 56}, // 65
    {54, 67, 72, 73, 65, 55}, // 66
    {53, 68, 71, 72, 66, 54}, // 67
    {52, 69, 70, 71, 67, 53}, // 68
    {51, -1, -1, 70, 68, 52}, // 69
    {69, -1, -1, 84, 71, 69}, // 70
    {68, 70, 84, 83, 72, 67}, // 71
    {67, 71, 83, 82, 73, 66}, // 72
    {66, 72, 82, 81, 74, 65}, // 73
    {65, 73, 81, 80, 75, 64}, // 74
    {64, 74, 80, 79, 76, 63}, // 75
    {63, 75, 79, 78, 77, 62}, // 76
    {62, 76, 78, -1, -1, 61}, // 77
    {76, 79, 90, -1, -1, 77}, // 78
    {75, 80, 89, 90, 78, 76}, // 79
    {74, 81, 88, 89, 79, 75}, // 80
    {73, 82, 87, 88, 80, 74}, // 81
    {72, 83, 86, 87, 81, 73}, // 82
    {71, 84, 85, 86, 82, 72}, // 83
    {70, -1, -1, 85, 83, 71}, // 84
    {84, -1, -1, -1, 86, 83}, // 85
    {83, 85, -1, -1, 87, 82}, // 86
    {82, 86, -1, -1, 88, 81}, // 87
    {81, 87, -1, -1, 89, 80}, // 88
    {80, 88, -1, -1, 90, 79}, // 89
    {79, 89, -1, -1, -1, 78}  // 90
};

CRGB rawAlphaLEDs[ALPHA_NUM_LEDS];
CRGBSet alphaLEDs(rawAlphaLEDs, ALPHA_NUM_LEDS);
CRGB rawBetaLEDs[BETA_NUM_LEDS];
CRGBSet betaLEDs(rawBetaLEDs, BETA_NUM_LEDS);
CRGB rawGammaLEDs[GAMMA_NUM_LEDS];
CRGBSet gammaLEDs(rawGammaLEDs, GAMMA_NUM_LEDS);

CRGBSet sideLEDs[6] = {
    alphaLEDs(0, 90),
    alphaLEDs(91, 181),
    alphaLEDs(182, 272),
    betaLEDs(0, 90),
    betaLEDs(91, 181),
    betaLEDs(182, 272),
};

CRGBSet topLEDs[6] = {
    gammaLEDs(0, 36),
    gammaLEDs(37, 73),
    gammaLEDs(74, 110),
    gammaLEDs(111, 147),
    gammaLEDs(148, 184),
    gammaLEDs(185, 221)};

const CRGB colors[] = {
    CRGB(255, 0, 0),
    CRGB(255, 127, 0),
    CRGB(255, 255, 0),
    CRGB(0, 255, 0),
    CRGB(0, 127, 255),
    CRGB(127, 0, 255)};

void setupLEDs()
{
    FastLED.addLeds<WS2812, ALPHA_LED_PIN, GRB>(rawAlphaLEDs, ALPHA_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<WS2812, BETA_LED_PIN, GRB>(rawBetaLEDs, BETA_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<WS2812, GAMMA_LED_PIN, GRB>(rawGammaLEDs, GAMMA_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}