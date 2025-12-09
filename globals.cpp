#include "globals.h"
#include <cstdlib>
#include <ctime>

using namespace std;
// global variable definitions

// start at menu screen
int currentState = STATE_MENU;

// bird starting position and movement
float birdY = 10.0f;           // starts in middle of screen
float birdVelocity = 0.0f;     // not moving initially
int birdSpriteIndex = 0;       // default to yellow bird

// physics values (tuned for smooth 60fps gameplay)
const float GRAVITY = 40.0f;         // pulls bird down
const float FLAP_STRENGTH = -20.0f;  // negative means upward push

// pipe arrays storing data for 3 pipes
float pipeX[MAX_PIPES] = { 0.0f, 0.0f, 0.0f };
float pipeGapY[MAX_PIPES] = { 0.0f, 0.0f, 0.0f };

// pipe dimensions
const int PIPE_WIDTH = 6;   // columns wide
const int PIPE_GAP = 8;     // rows tall (gap size)
float PIPE_SPEED = 20.0f;   // starting speed (increases during gameplay)

// score stuff
int currentScore = 0;
bool scoreIncremented[MAX_PIPES] = { false, false, false };

// menu selections
int menuSelection = 0;
int settingsSelection = 0;
int loadGameSelection = 0;

// high score array
int highScores[MAX_HIGH_SCORES] = { 0, 0, 0, 0, 0 };

// current theme (starts with day theme)
int currentTheme = 0;

// called once when game starts - sets everything up
void initializeGame()
{
    // for adding randomness in pipes gaps every time we run the cede
    srand(static_cast<unsigned>(time(0)));

    // position pipes off-screen to the right, spaced out
    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipeX[i] = static_cast<float>(CONSOLE_WIDTH + i * 30);

        // random gap position (between row 5 and 14)
        pipeGapY[i] = static_cast<float>(5 + (rand() % 10));

        // mark as not scored yet
        scoreIncremented[i] = false;
    }

    // reset bird to starting position
    birdY = 10.0f;
    birdVelocity = 0.0f;

    // reset game state
    currentScore = 0;
    PIPE_SPEED = 20.0f;  // back to normal speed
    currentTheme = 0;    // back to day theme
}

// reset game state when player wants to try again
void resetGame()
{
    // reset bird position and physics
    birdY = 10.0f;
    birdVelocity = 0.0f;

    // clear score and reset difficulty
    currentScore = 0;
    PIPE_SPEED = 20.0f;  // back to starting speed
    currentTheme = 0;    // back to day theme

    // reposition all pipes
    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipeX[i] = static_cast<float>(CONSOLE_WIDTH + i * 30);
        pipeGapY[i] = static_cast<float>(5 + (rand() % 10));
        scoreIncremented[i] = false;
    }
}
