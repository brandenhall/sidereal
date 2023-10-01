#ifndef SIDEREAL_LEDS
#define SIDEREAL_LEDS

#define LED_TYPE WS2812
#define ALPHA_LED_PIN 19
#define BETA_LED_PIN 18
#define GAMMA_LED_PIN 14
#define ALPHA_NUM_LEDS 273
#define BETA_NUM_LEDS 273
#define GAMMA_NUM_LEDS 273
#define COLOR_ORDER GRB
#define NUM_STRIPS 3
#define NUM_LEDS 819
#define BRIGHTNESS 128
#define FRAMES_PER_SECOND 120

#define NUM_SIDE_LEDS 91
#define NUM_TOP_LEDS 37

extern const uint8_t topSectors[][10];
extern const uint8_t topSectorCenters[];

extern const uint8_t topRing0[];
extern const uint8_t topRing1[];
extern const uint8_t topRing2[];
extern const uint8_t topRing3[];
extern const uint8_t topRingSizes[4];
extern const uint8_t *topRings[4];

extern const uint8_t topArrow0[];
extern const uint8_t topArrow1[];
extern const uint8_t topArrow2[];
extern const uint8_t topArrow3[];
extern const uint8_t topArrow4[];
extern const uint8_t topArrowSizes[5];
extern const uint8_t *topArrows[5];

extern const uint8_t sideRing0[];
extern const uint8_t sideRing1[];
extern const uint8_t sideRing2[];
extern const uint8_t sideRing3[];
extern const uint8_t sideRing4[];
extern const uint8_t sideRing5[];
extern const uint8_t sideRingSizes[6];
extern const uint8_t *sideRings[6];

extern const uint8_t sideArrow0[];
extern const uint8_t sideArrow1[];
extern const uint8_t sideArrow2[];
extern const uint8_t sideArrow3[];
extern const uint8_t sideArrow4[];
extern const uint8_t sideArrow5[];
extern const uint8_t sideArrow6[];
extern const uint8_t sideArrow7[];
extern const uint8_t sideArrowSizes[8];
extern const uint8_t *sideArrows[8];

extern const int8_t sideLinks[][6];

extern CRGB rawAlphaLEDs[];
extern CRGBSet alphaLEDs;
extern CRGB rawBetaLEDs[];
extern CRGBSet betaLEDs;
extern CRGB rawGammaLEDs[];
extern CRGBSet gammaLEDs;

extern CRGBSet sideLEDs[];
extern CRGBSet topLEDs[];
extern const CRGB colors[];

void setupLEDs();

#endif