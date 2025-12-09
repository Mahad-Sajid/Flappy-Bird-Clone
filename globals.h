#pragma once

// console grid dimensions (virtual coordinate system)
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 24;

// high score tracking
const int MAX_HIGH_SCORES = 5;
extern int highScores[MAX_HIGH_SCORES];

// game state values - using simple integers instead of enum
const int STATE_MENU = 0;
const int STATE_PLAYING = 1;
const int STATE_PAUSED = 2;
const int STATE_GAME_OVER = 3;
const int STATE_SETTINGS = 4;
const int STATE_HIGH_SCORES = 5;
const int STATE_LOAD_GAME = 6;

// current game state tracker
extern int currentState;

// bird position and movement stuff
extern float birdY;          // vertical position (0 to 23)
extern float birdVelocity;   // how fast bird is moving up/down
extern int birdSpriteIndex;  // which bird color: 0=yellow, 1=blue, 2=red

// physics constants for bird movement
extern const float GRAVITY;
extern const float FLAP_STRENGTH;

// pipe stuff
const int MAX_PIPES = 3;
extern float pipeX[MAX_PIPES];         // horizontal position of each pipe
extern float pipeGapY[MAX_PIPES];      // where the gap starts (top edge)
extern const int PIPE_WIDTH;           // how wide pipes are
extern const int PIPE_GAP;             // gap size the bird flies through
extern float PIPE_SPEED;               // how fast pipes move (increases over time)

// score tracking
extern int currentScore;
extern bool scoreIncremented[MAX_PIPES];  // prevents double-counting scores

// menu navigation
extern int menuSelection;      // which menu pos
extern int settingsSelection;  // which bird color 
extern int loadGameSelection;  // which save slot 

// visual theme system
extern int currentTheme;  // 0=day, 1=evening, 2=night

// setup functions
void initializeGame();  // called once at startup
void resetGame();       // called when starting new game or retrying
