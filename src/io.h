#ifndef SIDEREAL_IO
#define SIDEREAL_IO

extern bool buttonsActive;
extern const uint8_t buttonPins[6];
extern const uint8_t buttonLEDPin;
extern const uint8_t prizeReleasePin;

void setupButtons();
void enableButtons();
void disableButtons();

#endif