#ifndef SIDEREAL_MODE
#define SIDEREAL_MODE

#define MODE_BOOT 0
#define MODE_POST 1
#define MODE_ATTRACT 2
#define MODE_STARTUP 3
#define MODE_SCRAMBLE 4
#define MODE_PLAY 5
#define MODE_SOLVE 6
#define MODE_WIN 7
#define MODE_COOLDOWN 8

extern uint8_t currentMode;
extern unsigned long modeStartTime;
extern uint8_t currentLevel;
extern uint8_t gameState[];
extern const uint8_t levelScrambles[];
extern const uint8_t levelStates[];

void changeMode(uint8_t nextMode, unsigned long now);
void loopMode(unsigned long now);
void printGameState();

#endif