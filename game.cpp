#include "game.h"
#include <cstdlib>
#include "graphics.h"

// make the bird jump when spacebar is pressed
void flapBird()
{
    birdVelocity = FLAP_STRENGTH;  // instant upward velocity
}

// update bird position based on physics
void updateBird(float deltaTime)
{
    // apply gravity (makes bird fall faster over time)
    birdVelocity += GRAVITY * deltaTime;

    // move bird based on current velocity
    birdY += birdVelocity * deltaTime;

    // prevent bird from going above the screen
    if (birdY < 0.0f)
    {
        birdY = 0.0f;          // clamp to top edge
        birdVelocity = 0.0f;   // stop upward movement
    }
}

// move pipes from right to left across screen
void updatePipes(float deltaTime)
{
    // loop through all 3 pipes
    for (int i = 0; i < MAX_PIPES; i++)
    {
        // move pipe left based on current speed
        pipeX[i] -= PIPE_SPEED * deltaTime;

        // if pipe went off left side of screen
        if (pipeX[i] < -PIPE_WIDTH)
        {
            // respawn it on the right side
            pipeX[i] = static_cast<float>(CONSOLE_WIDTH);

            // give it a new random gap position
            pipeGapY[i] = static_cast<float>(5 + (std::rand() % 10));

            // reset score flag so we can score this pipe again
            scoreIncremented[i] = false;
        }
    }
}

// check if bird hit anything (pipes or ground)
bool checkCollision()
{
    // convert bird's float position to integer row
    int birdRow = static_cast<int>(birdY);
    int birdCol = 10;  // bird is always at column 10

    // check if bird hit the ground (bottom of screen)
    if (birdRow >= CONSOLE_HEIGHT )
    {
        return true;  // collision detected!
    }

    // check collision with each pipe
    for (int i = 0; i < MAX_PIPES; i++)
    {
        // convert pipe position to integer
        int px = static_cast<int>(pipeX[i]);
        int pw = PIPE_WIDTH;

        // check if bird is horizontally aligned with this pipe
        if (birdCol >= px && birdCol < (px + pw))
        {
            // find where the gap is
            int gapTop = static_cast<int>(pipeGapY[i]);
            int gapBottom = static_cast<int>(pipeGapY[i]) + PIPE_GAP;

            // check if bird is outside the gap (hit pipe)
            if (birdRow < gapTop || birdRow >= gapBottom)
            {
                return true;  // collision with pipe!
            }
        }
    }
   
    return false;  // no collision
}

// handle score updates when bird passes pipes
void updateScore()
{
    int birdCol = 10;  // bird's horizontal position

    // check each pipe
    for (int i = 0; i < MAX_PIPES; i++)
    {
        // find center of pipe
        int pipeCenterX = static_cast<int>(pipeX[i] + PIPE_WIDTH / 2);

        // if bird passed center and we haven't scored this pipe yet
        if (birdCol > pipeCenterX && !scoreIncremented[i])
        {
            // increase score
            currentScore++;

            // mark this pipe as scored
            scoreIncremented[i] = true;

            // play point sound
            playPointSound();

            // increase speed every 5 points to make game harder
            if (currentScore % 5 == 0)
            {
                PIPE_SPEED += 2.0f;  // speed boost!
            }

            // change theme every 7 points for variety
            if (currentScore % 7 == 0)
            {
                currentTheme = currentTheme + 1;  // next theme

                // wrap back to day theme after night
                if (currentTheme > 2)
                {
                    currentTheme = 0;
                }
            }
        }
    }
}

// main game loop - called every frame
void updateGame(float deltaTime)
{
    // update bird physics
    updateBird(deltaTime);

    // update pipe positions
    updatePipes(deltaTime);

    // check for scoring
    updateScore();

    // check if bird hit anything
    if (checkCollision())
    {
        playHitSound();                  // play crash sound
        currentState = STATE_GAME_OVER;  // switch to game over screen
    }
}
