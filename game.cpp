#include "game.h"
#include <cstdlib>
#include "graphics.h"

// make the bird jump when spacebar is pressed
void flapBird()
{
    birdVelocity = FLAP_STRENGTH; // instant upward velocity
}

// updating bird ki position based on physics
void updateBird(float deltaTime)
{
    // apply gravity 
    birdVelocity += GRAVITY * deltaTime;

    // move bird based on current velocity
    birdY += birdVelocity * deltaTime;

    // prevent bird from going above the screen
    if (birdY < 0.0f)
    {
        birdY = 0.0f;          // stays to top edge
        birdVelocity = 0.0f;   // stop upward movement
    }
}

// move pipes from right to left across screen
void updatePipes(float deltaTime)
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        // move pipe left based on current speed
        pipeX[i] -= PIPE_SPEED * deltaTime;

        // if pipe went off left side of screen
        if (pipeX[i] < -PIPE_WIDTH)
        {
            // respawn it on the right side
            pipeX[i] = static_cast<float>(CONSOLE_WIDTH);

            // random gap bw 5 to 14
            pipeGapY[i] = static_cast<float>(5 + (rand() % 10));

            // reset score flag for pipe
            scoreIncremented[i] = false;
        }
    }
}

// check if bird hit anything
bool checkCollision()
{
    // convert bird's float position to integer row
    int birdRow = static_cast<int>(birdY);
    int birdCol = 10;

    // check if bird hit the ground 
    if (birdRow >= CONSOLE_HEIGHT)
    {
        return true;  // collision detected at ground
    }

    // check collision with each pipe
    for (int i = 0; i < MAX_PIPES; i++)
    {
        // pipe position to integer
        int px = static_cast<int>(pipeX[i]);
        int pw = PIPE_WIDTH;

        // check if bird is horizontally aligned with this pipe
        if (birdCol >= px && birdCol < (px + pw))
        {
            // find where the gap is
            int gapTop = static_cast<int>(pipeGapY[i]);
            int gapBottom = static_cast<int>(pipeGapY[i]) + PIPE_GAP;

            // if bird is outside the gap
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
    int birdCol = 10;

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

            // mark pipe as scored
            scoreIncremented[i] = true;

            // point sound
            playPointSound();

            // increase speed every 5 points
            if (currentScore % 5 == 0)
            {
                PIPE_SPEED += 2.0f;
            }

            // changing theme after every 7 points 
            if (currentScore % 7 == 0)
            {
                currentTheme = currentTheme + 1;

                // after night again from day
                if (currentTheme > 2)
                {
                    currentTheme = 0;
                }
            }
        }
    }
}

// main game loop
void updateGame(float deltaTime)
{
    updateBird(deltaTime);
    updatePipes(deltaTime);
    updateScore();
    if (checkCollision())
    {
        playHitSound();                  // crash sound
        currentState = STATE_GAME_OVER;  // switch to game over 
    }
}
