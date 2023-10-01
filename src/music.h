#ifndef SIDEREAL_MUSIC
#define SIDEREAL_MUSIC

#define MALLET_DURATION 40

struct music
{
    uint16_t time;
    uint8_t chord;
};

extern bool visualizeMusic;
extern bool musicPlaying;

extern const uint attractThemeSizes[];
extern music *attractThemes[];

extern const uint levelThemeSizes[];
extern music *levelThemes[];

extern music mainTheme[];
extern const uint mainThemeSize;
extern music solveTheme[];
extern const uint solveThemeSize;
extern music winTheme[];
extern const uint winThemeSize;

void playMusic(music *nextMusic, uint length, unsigned long now);
void swingMallet(uint8_t index, unsigned long now);
void updateMusic(unsigned long now);

#endif