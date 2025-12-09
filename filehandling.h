#pragma once
#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "globals.h"

// Save/Load game state with slot number
void saveGame(int slot = 0);
bool loadGame(int slot = 0);
bool hasSaveData(int slot);

// High scores
void loadHighScores();
void saveHighScores();
void updateHighScores(int newScore);

#endif
