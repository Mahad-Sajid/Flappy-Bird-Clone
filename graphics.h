#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Audio/SoundBuffer.hpp>
using namespace sf;

// load textures, fonts
void Graphics();

//for loading screen
void drawLoadingScreen(RenderWindow& window, float progress);

// menu
void drawmenu(RenderWindow& window, int menuselect);

// backgrounds
void drawbackground(RenderWindow& window);
void drawground(RenderWindow& window);

// bird & pipes
void drawbird(RenderWindow& window, int birdchoice);
void drawpipes(RenderWindow& window);

// score
void drawscore(RenderWindow& window, int score);

// pause, settings, game over
void drawpause(RenderWindow& window);
void drawsettings(RenderWindow& window, int settingsSelect, int birdChoice);
void drawgameover(RenderWindow& window, int score);

// high scores screen
void drawhighscores(RenderWindow& window);

// load game screen
void drawloadgame(RenderWindow& window, int selection);

//for audios
void playFlapSound();
void playHitSound();
void playPointSound();
