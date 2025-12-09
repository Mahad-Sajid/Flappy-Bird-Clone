#pragma once
#include "globals.h"

//bird
void flapBird();
void updateBird(float deltaTime);

//pipes
void updatePipes(float deltaTime);

//score and collision detection 
bool checkCollision();
void updateScore();

//game update 
void updateGame(float deltaTime);
