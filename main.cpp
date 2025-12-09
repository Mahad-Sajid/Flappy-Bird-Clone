#include <SFML/Graphics.hpp>
#include <iostream>
#include "globals.h"
#include "game.h"
#include "graphics.h"
#include "filehandling.h"

using namespace sf;
using namespace std;

int main()
{
    // window dimensions: 800 x 600 seemed smoothest 
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;

    // create game window
    RenderWindow window(VideoMode({ WIDTH, HEIGHT }), "404-Not Flapping");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    // setup view for window resizing
    View view(FloatRect({ 0.f, 0.f }, { static_cast<float>(WIDTH), static_cast<float>(HEIGHT) }));
    window.setView(view);

    // load all game assets (textures, fonts, sounds)
    Graphics();

    for (int i = 0; i <= 100; ++i)
    {
        float progress = i / 100.f;      // 0.0 to 1.0
        drawLoadingScreen(window, progress);
        sleep(milliseconds(15)); // small delay so
    }

    // initialize game state
    initializeGame();
    loadSettings();
    settingsSelection = birdSpriteIndex;
    // load high scores from file
    loadHighScores();

    // clock for tracking time between frames
    Clock clock;

    // main game loop
    while (window.isOpen())
    {
        // get time since last frame (for smooth movement)
        float dt = clock.restart().asSeconds();

        // process all window events
        while (optional event = window.pollEvent())  // SFML 3 returns optional
        {
            // check if user closed window
            if (event->is<Event::Closed>())
            {
                window.close();
            }

            // handle window resizing
            if (event->is<Event::Resized>())
            {
                auto resizeEvent = event->getIf<Event::Resized>();
                FloatRect visibleArea({ 0.f, 0.f },
                    { static_cast<float>(resizeEvent->size.x),
                      static_cast<float>(resizeEvent->size.y) });
                window.setView(View(visibleArea));
            }

            // handle keyboard input
            if (const auto& keyPress = event->getIf<Event::KeyPressed>())
            {
                // MENU screen controls
                if (currentState == STATE_MENU)
                {
                    // move selection up
                    if (keyPress->code == Keyboard::Key::Up)
                    {
                        menuSelection--;
                        if (menuSelection < 0)
                        {
                            menuSelection = 4;  // wrap to bottom
                        }
                    }
                    // move selection down
                    else if (keyPress->code == Keyboard::Key::Down)
                    {
                        menuSelection++;
                        if (menuSelection > 4)
                        {
                            menuSelection = 0;  // wrap to top
                        }
                    }
                    // select menu option
                    else if (keyPress->code == Keyboard::Key::Enter || keyPress->code == Keyboard::Key::Space)
                    {
                        if (menuSelection == 0)  // New game
                        {
                            resetGame();
                            currentState = STATE_PLAYING;
                        }
                        else if (menuSelection == 1)  // Load Game
                        {
                            currentState = STATE_LOAD_GAME;
                            loadGameSelection = 0;
                        }
                        else if (menuSelection == 2)  // High Scores
                        {
                            currentState = STATE_HIGH_SCORES;
                        }
                        else if (menuSelection == 3)  // Settings
                        {
                            currentState = STATE_SETTINGS;
                        }
                        else if (menuSelection == 4)  // Exit
                        {
                            window.close();
                        }
                    }
                }

                // LOAD GAME screen controls
                else if (currentState == STATE_LOAD_GAME)
                {
                    // move up through save slots
                    if (keyPress->code == Keyboard::Key::Up)
                    {
                        loadGameSelection--;
                        if (loadGameSelection < 0)
                        {
                            loadGameSelection = 2;
                        }
                    }
                    // move down through save slots
                    else if (keyPress->code == Keyboard::Key::Down)
                    {
                        loadGameSelection++;
                        if (loadGameSelection > 2)
                        {
                            loadGameSelection = 0;
                        }
                    }
                    // try to load selected save slot
                    else if (keyPress->code == Keyboard::Key::Enter || keyPress->code == Keyboard::Key::Space)
                    {
                        if (loadGame(loadGameSelection))
                        {
                            currentState = STATE_PLAYING;  // load successful, start game
                        }
                    }
                    // go back to menu
                    else if (keyPress->code == Keyboard::Key::Escape)
                    {
                        currentState = STATE_MENU;
                    }
                }

                // HIGH SCORES screen controls
                else if (currentState == STATE_HIGH_SCORES)
                {
                    // return to menu
                    if (keyPress->code == Keyboard::Key::Escape)
                    {
                        currentState = STATE_MENU;
                    }
                }

                // SETTINGS screen controls
                else if (currentState == STATE_SETTINGS)
                {
                    // move left through bird colors
                    if (keyPress->code == Keyboard::Key::Left)
                    {
                        settingsSelection--;
                        if (settingsSelection < 0)
                        {
                            settingsSelection = 2;
                        }
                    }
                    // move right through bird colors
                    else if (keyPress->code == Keyboard::Key::Right)
                    {
                        settingsSelection++;
                        if (settingsSelection > 2)
                        {
                            settingsSelection = 0;
                        }
                    }
                    // confirm bird color selection
                    else if (keyPress->code == Keyboard::Key::Enter || keyPress->code == Keyboard::Key::Space)
                    {
                        birdSpriteIndex = settingsSelection;
                        saveSettings();
                    }
                    // return to menu
                    else if (keyPress->code == Keyboard::Key::Escape)
                    {
                        currentState = STATE_MENU;
                    }
                }

                // PLAYING state controls
                else if (currentState == STATE_PLAYING)
                {
                    // make bird jump
                    if (keyPress->code == Keyboard::Key::Space)
                    {
                        flapBird();
                        playFlapSound();
                    }
                    // pause game
                    else if (keyPress->code == Keyboard::Key::Escape || keyPress->code == Keyboard::Key::P)
                    {
                        currentState = STATE_PAUSED;
                    }
                    // quick save to slot 1
                    else if (keyPress->code == Keyboard::Key::Num1)
                    {
                        saveGame(0);
                    }
                    // quick save to slot 2
                    else if (keyPress->code == Keyboard::Key::Num2)
                    {
                        saveGame(1);
                    }
                    // quick save to slot 3
                    else if (keyPress->code == Keyboard::Key::Num3)
                    {
                        saveGame(2);
                    }
                }

                // PAUSED state controls
                else if (currentState == STATE_PAUSED)
                {
                    // resume game
                    if (keyPress->code == Keyboard::Key::Space || keyPress->code == Keyboard::Key::P)
                    {
                        currentState = STATE_PLAYING;
                    }
                    // return to menu
                    else if (keyPress->code == Keyboard::Key::Escape)
                    {
                        currentState = STATE_MENU;
                    }
                    // save from pause menu - slot 1
                    else if (keyPress->code == Keyboard::Key::Num1)
                    {
                        saveGame(0);
                    }
                    // save from pause menu - slot 2
                    else if (keyPress->code == Keyboard::Key::Num2)
                    {
                        saveGame(1);
                    }
                    // save from pause menu - slot 3
                    else if (keyPress->code == Keyboard::Key::Num3)
                    {
                        saveGame(2);
                    }
                }

                // GAME OVER state controls
                else if (currentState == STATE_GAME_OVER)
                {
                    // retry (start new game)
                    if (keyPress->code == Keyboard::Key::Space)
                    {
                        // update high scores before resetting
                        updateHighScores(currentScore);
                        resetGame();
                        currentState = STATE_PLAYING;
                    }
                    // return to menu
                    else if (keyPress->code == Keyboard::Key::Escape)
                    {
                        // update high scores before going to menu
                        updateHighScores(currentScore);
                        currentState = STATE_MENU;
                    }
                }
            }
        }

        // update game logic (only when playing)
        if (currentState == STATE_PLAYING)
        {
            updateGame(dt);
        }

        // clear window for drawing
        window.clear();

        // draw appropriate screen based on current state
        if (currentState == STATE_MENU)
        {
            drawbackground(window);
            drawground(window);
            drawmenu(window, menuSelection);
        }
        else if (currentState == STATE_LOAD_GAME)
        {
            drawloadgame(window, loadGameSelection);
        }
        else if (currentState == STATE_HIGH_SCORES)
        {
            drawhighscores(window);
        }
        else if (currentState == STATE_SETTINGS)
        {
            drawsettings(window, settingsSelection, birdSpriteIndex);
        }
        else if (currentState == STATE_PLAYING)
        {
            drawbackground(window);
            drawpipes(window);
            drawground(window);
            drawbird(window, birdSpriteIndex);
            drawscore(window, currentScore);
        }
        else if (currentState == STATE_PAUSED)
        {
            // draw same as playing but with pause overlay
            drawbackground(window);
            drawpipes(window);
            drawground(window);
            drawbird(window, birdSpriteIndex);
            drawscore(window, currentScore);
            drawpause(window);
        }
        else if (currentState == STATE_GAME_OVER)
        {
            drawgameover(window, currentScore);
        }

        // display everything we drew
        window.display();
    }

    return 0;
}
