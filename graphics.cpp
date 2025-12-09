#include "graphics.h"
#include "globals.h"
#include "filehandling.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

//global textures / fonts
Texture g_title;
Texture g_bgTexture;
Texture g_bgeveningTexture;
Texture g_bgNightTexture;
Texture g_groundTexture;
Texture g_birdTexture[3];
Font    g_font;
Texture g_pipeTopTexture;
Texture g_pipeBottomTexture;

//for sound
SoundBuffer g_flap;
SoundBuffer g_point;
SoundBuffer g_hit;

Sound g_flapS{ g_flap };
Sound g_hitS{ g_hit };
Sound g_pointS{ g_point };

void Graphics()
{
    if (!g_bgTexture.loadFromFile("assets\\bgday.jpg"))
        cout << "Failed to load bgday" << endl;

    if (!g_bgeveningTexture.loadFromFile("assets\\bgevening.png"))
        cout << "Failed to load bgevening" << endl;

    if (!g_bgNightTexture.loadFromFile("assets\\bgnight.jpg"))
        cout << "Failed to load bgnight" << endl;

    if (!g_groundTexture.loadFromFile("assets\\ground.png"))
        cout << "Failed to load ground" << endl;

    if (!g_birdTexture[0].loadFromFile("assets\\yellowbird.png"))
        cout << "Failed to load yellow bird" << endl;

    if (!g_birdTexture[1].loadFromFile("assets\\bluebird.png"))
        cout << "Failed to load blue bird" << endl;

    if (!g_birdTexture[2].loadFromFile("assets\\redbird.png"))
        cout << "Failed to load red bird" << endl;

    if (!g_font.openFromFile("assets\\font.ttf"))
        cout << "Failed to load main font" << endl;

    if (!g_pipeTopTexture.loadFromFile("assets\\pipetop.png"))
        cout << "Failed to load pipe top" << endl;

    if (!g_pipeBottomTexture.loadFromFile("assets\\pipebottom.png"))
        cout << "Failed to load pipe bottom" << endl;

    if (!g_flap.loadFromFile("assets\\audio_wing.wav"))
        cout << "Failed to load flap audio" << endl;
    else
        g_flapS.setBuffer(g_flap);

    if (!g_hit.loadFromFile("assets\\audio_hit.mp3"))
        cout << "Failed to load hit audio" << endl;
    else
        g_hitS.setBuffer(g_hit);

    if (!g_point.loadFromFile("assets\\audio_point.wav"))
        cout << "Failed to load point audio" << endl;
    else
        g_pointS.setBuffer(g_point);
}

//background with theme support (3 themes)
void drawbackground(RenderWindow& window)
{
    Texture& texToUse =
        (currentTheme == 0) ? g_bgTexture :
        (currentTheme == 1) ? g_bgeveningTexture :
        g_bgNightTexture;

    Sprite bg(texToUse);


    //get size of window
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //get size of texture
    float textureWidth = bg.getTexture().getSize().x;
    float textureHeight = bg.getTexture().getSize().y;

    //scalre bg to fit window
    float scaleX = windowWidth / textureWidth;
    float scaleY = windowHeight / textureHeight;
    bg.setScale({ scaleX, scaleY });

    window.draw(bg);
}

//ground drawing 
void drawground(RenderWindow& window)
{
    Sprite ground(g_groundTexture);

    // Get window size
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // Get ground texture size
    float groundTextureWidth = g_groundTexture.getSize().x;
    float groundTextureHeight = g_groundTexture.getSize().y;

    // Ground should be 15% of window height
    float desiredGroundHeight = windowHeight * 0.15f;

    // Calculate scale for both width and height
    float scaleX = windowWidth / groundTextureWidth;
    float scaleY = desiredGroundHeight / groundTextureHeight;

    // Apply scale to ground
    ground.setScale({ scaleX, scaleY});

    // Put ground at bottom
    float groundX = 0.0f;
    float groundY = windowHeight - desiredGroundHeight;

    ground.setPosition({ groundX, groundY });

    // Draw the ground
    window.draw(ground);
}

//menu
void drawmenu(RenderWindow& window, int menuselect)
{
    drawbackground(window);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //404 not flapping title
    Text title(g_font);
    title.setString("404 not Flapping");
    //using percetanges for text size that will change according to window size
    title.setCharacterSize(windowHeight * 0.10f);
    title.setFillColor(Color::White);

    FloatRect titleBounds = title.getLocalBounds();
    float titleX = (windowWidth - titleBounds.size.x) / 2.0f;
    float titleY = windowHeight * 0.18f;
    title.setPosition({ titleX, titleY });
    window.draw(title);

    //new game
    Text newGame(g_font);
    newGame.setString("New Game");
    newGame.setCharacterSize(windowHeight * 0.04f);

    FloatRect newGameBounds = newGame.getLocalBounds();
    float newGameX = (windowWidth - newGameBounds.size.x) / 2.0f;
    float newGameY = windowHeight * 0.35f;
    newGame.setPosition({ newGameX, newGameY });

    if (menuselect == 0)
        newGame.setFillColor(Color::Yellow);
    else
        newGame.setFillColor(Color::White);

    window.draw(newGame);

    //load game
    Text loadGame(g_font);
    loadGame.setString("Load Game");
    loadGame.setCharacterSize(windowHeight * 0.04f);

    FloatRect loadGameBounds = loadGame.getLocalBounds();
    float loadGameX = (windowWidth - loadGameBounds.size.x) / 2.0f;
    float loadGameY = windowHeight * 0.43f;
    loadGame.setPosition({ loadGameX, loadGameY });

    if (menuselect == 1)
        loadGame.setFillColor(Color::Yellow);
    else
        loadGame.setFillColor(Color::White);

    window.draw(loadGame);

    //highscore
    Text highScores(g_font);
    highScores.setString("High Scores");
    highScores.setCharacterSize(windowHeight * 0.04f);

    FloatRect highScoresBounds = highScores.getLocalBounds();
    float highScoresX = (windowWidth - highScoresBounds.size.x) / 2.0f;
    float highScoresY = windowHeight * 0.51f;
    highScores.setPosition({ highScoresX, highScoresY });

    if (menuselect == 2)
        highScores.setFillColor(Color::Yellow);
    else
        highScores.setFillColor(Color::White);

    window.draw(highScores);

    //settings
    Text settings(g_font);
    settings.setString("Settings");
    settings.setCharacterSize(windowHeight * 0.04f);

    FloatRect settingsBounds = settings.getLocalBounds();
    float settingsX = (windowWidth - settingsBounds.size.x) / 2.0f;
    float settingsY = windowHeight * 0.59f;
    settings.setPosition({ settingsX, settingsY });

    if (menuselect == 3)
        settings.setFillColor(Color::Yellow);
    else
        settings.setFillColor(Color::White);

    window.draw(settings);

    //exit
    Text exitGame(g_font);
    exitGame.setString("Exit");
    exitGame.setCharacterSize(windowHeight * 0.04f);

    FloatRect exitGameBounds = exitGame.getLocalBounds();
    float exitGameX = (windowWidth - exitGameBounds.size.x) / 2.0f;
    float exitGameY = windowHeight * 0.67f;
    exitGame.setPosition({ exitGameX, exitGameY });

    if (menuselect == 4)
        exitGame.setFillColor(Color::Yellow);
    else
        exitGame.setFillColor(Color::White);

    window.draw(exitGame);
}

//bird
void drawbird(RenderWindow& window, int birdchoice)
{
    //choice wrapping
    if (birdchoice < 0) {
        birdchoice = 0;
    }
    if (birdchoice > 2) {
        birdchoice = 2;
    }

    Sprite birdSprite(g_birdTexture[birdchoice]);

    //get size of window
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;
    float groundHeight = g_groundTexture.getSize().y;

    // Calculate sky area
    float skyHeight = windowHeight - groundHeight;

    // Calculate column and row sizes
    float colWidth = windowWidth / CONSOLE_WIDTH;
    float rowHeight = skyHeight / CONSOLE_HEIGHT;

    // Calculate bird position
    float birdPixelX = 10.0f * colWidth;
    float birdPixelY = birdY * rowHeight;

    // Scale bird to fit 3 columns wide
    float birdTextureWidth = g_birdTexture[birdchoice].getSize().x;
    float targetWidth = colWidth * 3.0f;
    float birdScale = targetWidth / birdTextureWidth;

    birdSprite.setScale({ birdScale, birdScale });
    birdSprite.setPosition({ birdPixelX, birdPixelY });

    window.draw(birdSprite);
}

// Score (centered at top)
void drawscore(RenderWindow& window, int score)
{
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // Create score text
    Text scoreText(g_font);
    scoreText.setString(to_string(score));
    scoreText.setCharacterSize(windowHeight * 0.08f);
    scoreText.setFillColor(Color::White);

    // Center the score at top
    FloatRect bounds = scoreText.getLocalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f;
    float y = windowHeight * 0.04f;
    scoreText.setPosition({ x, y });

    window.draw(scoreText);
}

//pause drawing
void drawpause(RenderWindow& window)
{
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //draw pause title
    Text paused(g_font);
    paused.setString("PAUSED");
    paused.setCharacterSize(windowHeight * 0.08f);
    paused.setFillColor(Color::Yellow);

    //to make it centre aligned
    FloatRect pausedBounds = paused.getLocalBounds();
    float pausedX = (windowWidth - pausedBounds.size.x) / 2.0f;
    float pausedY = windowHeight * 0.25f;

    paused.setPosition({ pausedX, pausedY });
    window.draw(paused);

    //drawing instructions
    Text inst(g_font);
    inst.setString("Space to Resume\n\nEsc to Main Menu\n");
    inst.setCharacterSize(windowHeight * 0.04f);
    inst.setFillColor(Color::White);

    Text slotinst(g_font);
    slotinst.setString("1 2 3 to save Slot");
    slotinst.setCharacterSize(windowHeight * 0.04f);
    slotinst.setFillColor(Color::White);

    FloatRect instBounds = inst.getLocalBounds();
    float instX = (windowWidth - instBounds.size.x) / 2.0f;
    float instY = windowHeight * 0.39f;
    inst.setPosition({ instX, instY });
    window.draw(inst);

    FloatRect slotinstBounds = slotinst.getLocalBounds();
    float slotinstX = (windowWidth - slotinstBounds.size.x) / 2.0f;
    float slotinstY = windowHeight * 0.55f;
    slotinst.setPosition({ slotinstX, slotinstY });
    window.draw(slotinst);
}

//settings screen
void drawsettings(RenderWindow& window, int settingsSelect, int birdChoice)
{
    drawbackground(window);
    drawground(window);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //stting title
    Text title(g_font);
    title.setString("SETTINGS");
    title.setCharacterSize(windowHeight * 0.07f);
    title.setFillColor(Color::White);

    FloatRect titleBounds = title.getLocalBounds();
    float titleX = (windowWidth - titleBounds.size.x) / 2.0f;
    float titleY = windowHeight * 0.1f;
    title.setPosition({ titleX, titleY });
    window.draw(title);

    //draw subtitle
    Text subtitle(g_font);
    subtitle.setString("Select Bird");
    subtitle.setCharacterSize(windowHeight * 0.04f);
    subtitle.setFillColor(Color::Yellow);

    FloatRect subtitleBounds = subtitle.getLocalBounds();
    float subtitleX = (windowWidth - subtitleBounds.size.x) / 2.0f;
    float subtitleY = windowHeight * 0.21f;
    subtitle.setPosition({ subtitleX, subtitleY });
    window.draw(subtitle);

    //drawing birdy options
    float birdY = windowHeight * 0.32f;
    float totalBirdWidth = windowWidth * 0.6f;
    float gapBetweenBirds = totalBirdWidth / 3.0f;
    float startX = (windowWidth - totalBirdWidth) / 2.0f + gapBetweenBirds / 2.0f;

    //scaling sprites
    float birdScale = windowHeight * 0.0026f;

    for (int i = 0; i < 3; i++)
    {
        float birdX = startX + (i * gapBetweenBirds);

        //drawing highligh box when selected
        if (i == settingsSelect)
        {
            float highlightSize = windowHeight * 0.1f;
            RectangleShape highlight;
            highlight.setSize(Vector2f(highlightSize, highlightSize));
            highlight.setFillColor(Color(255, 255, 255, 80));

            float highlightX = birdX - (highlightSize * 0.1f);
            float highlightY = birdY - (highlightSize * 0.1f);
            highlight.setPosition({ highlightX, highlightY });
            window.draw(highlight);
        }

        //drawing birdy
        Sprite bird(g_birdTexture[i]);
        bird.setPosition({ birdX, birdY });
        bird.setScale({ birdScale, birdScale });
        window.draw(bird);
    }

    //inst text
    Text inst(g_font);
    inst.setString("Enter to select   Esc to back");
    inst.setCharacterSize(windowHeight * 0.03f);
    inst.setFillColor(Color::White);

    FloatRect hintBounds = inst.getLocalBounds();
    float instX = (windowWidth - hintBounds.size.x) / 2.0f;
    float instY = windowHeight * 0.5f;
    inst.setPosition({ instX, instY });
    window.draw(inst);
}

//game over screen
void drawgameover(RenderWindow& window, int score)
{
    drawbackground(window);
    drawground(window);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //game over tag
    Text gameOver(g_font);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(windowHeight * 0.08f);
    gameOver.setFillColor(Color::Red);

    FloatRect gameOverBounds = gameOver.getLocalBounds();
    float gameOverX = (windowWidth - gameOverBounds.size.x) / 2.0f;
    float gameOverY = windowHeight * 0.2f;
    gameOver.setPosition({ gameOverX, gameOverY });
    window.draw(gameOver);

    //score text
    string scoreString = "Score: " + to_string(score);
    Text scoreText(g_font);
    scoreText.setString(scoreString);
    scoreText.setCharacterSize(windowHeight * 0.068f);
    scoreText.setFillColor(Color::White);

    FloatRect scoreBounds = scoreText.getLocalBounds();
    float scoreX = (windowWidth - scoreBounds.size.x) / 2.0f;
    float scoreY = windowHeight * 0.31f;
    scoreText.setPosition({ scoreX, scoreY });
    window.draw(scoreText);

    //retry hint
    Text retry(g_font);
    retry.setString("Space to Retry");
    retry.setCharacterSize(windowHeight * 0.03f);
    retry.setFillColor(Color::Yellow);

    FloatRect retryBounds = retry.getLocalBounds();
    float retryX = (windowWidth - retryBounds.size.x) / 2.0f;
    float retryY = windowHeight * 0.47f;
    retry.setPosition({ retryX, retryY });
    window.draw(retry);

    //menu hint
    Text menu(g_font);
    menu.setString("Esc for Main Menu");
    menu.setCharacterSize(windowHeight * 0.03f);
    menu.setFillColor(Color::Yellow);

    FloatRect menuBounds = menu.getLocalBounds();
    float menuX = (windowWidth - menuBounds.size.x) / 2.0f;
    float menuY = windowHeight * 0.53f;
    menu.setPosition({ menuX, menuY });
    window.draw(menu);
}

//high score screen
void drawhighscores(RenderWindow& window)
{
    drawbackground(window);
    drawground(window);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //drawing title
    Text title(g_font);
    title.setString("HIGH SCORES");
    title.setCharacterSize(windowHeight * 0.06f);
    title.setFillColor(Color::Yellow);

    FloatRect titleBounds = title.getLocalBounds();
    float titleX = (windowWidth - titleBounds.size.x) / 2.0f;
    float titleY = windowHeight * 0.12f;
    title.setPosition({ titleX, titleY });
    window.draw(title);

    //highscore display
    float startY = windowHeight * 0.25f;
    float gap = windowHeight * 0.088f;

    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        string rankString = to_string(i + 1) + ".  " + to_string(highScores[i]);

        Text scoreText(g_font);
        scoreText.setString(rankString);
        scoreText.setCharacterSize(windowHeight * 0.068f);
        scoreText.setFillColor(Color::White);

        //score centralixed
        FloatRect scoreBounds = scoreText.getLocalBounds();
        float scoreX = (windowWidth - scoreBounds.size.x) / 2.0f;
        float scoreY = startY + (i * gap);
        scoreText.setPosition({ scoreX, scoreY });

        window.draw(scoreText);
    }

    //instruction text
    Text inst(g_font);
    inst.setString("Press Esc to return");
    inst.setCharacterSize(windowHeight * 0.03f);
    inst.setFillColor(Color::Yellow);

    FloatRect instBounds = inst.getLocalBounds();
    float hintX = (windowWidth - instBounds.size.x) / 2.0f;
    float hintY = windowHeight * 0.74f;
    inst.setPosition({ hintX, hintY });
    window.draw(inst);
}

//load game screen
void drawloadgame(RenderWindow& window, int selection)
{
    drawbackground(window);
    drawground(window);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    //title
    Text title(g_font);
    title.setString("LOAD GAME");
    title.setCharacterSize(windowHeight * 0.06f);
    title.setFillColor(Color::White);

    FloatRect titleBounds = title.getLocalBounds();
    float titleX = (windowWidth - titleBounds.size.x) / 2.0f;
    float titleY = windowHeight * 0.1f;
    title.setPosition({ titleX, titleY });
    window.draw(title);

    //drawing slots
    float startY = windowHeight * 0.27f;
    float gap = windowHeight * 0.098f;

    for (int i = 0; i < 3; i++)
    {
        string slotString = "Slot " + to_string(i + 1);
        if (!hasSaveData(i))
        {
            slotString += " Empty";
        }

        Text slotText(g_font);
        slotText.setString(slotString);
        slotText.setCharacterSize(windowHeight * 0.07f);

        //highlighting
        if (i == selection)
            slotText.setFillColor(Color::Yellow);
        else
            slotText.setFillColor(Color::White);

        //centring slots
        FloatRect slotBounds = slotText.getLocalBounds();
        float slotX = (windowWidth - slotBounds.size.x) / 2.0f;
        float slotY = startY + (i * gap);
        slotText.setPosition({ slotX, slotY });

        window.draw(slotText);
    }

    //inst text
    Text inst(g_font);
    inst.setString("Enter to Load   Esc to Back");
    inst.setCharacterSize(windowHeight * 0.03f);
    inst.setFillColor(Color::White);

    FloatRect instBounds = inst.getLocalBounds();
    float instX = (windowWidth - instBounds.size.x) / 2.0f;
    float instY = windowHeight * 0.625f;
    inst.setPosition({ instX, instY });
    window.draw(inst);
}

void drawpipes(RenderWindow& window)
{
    //window size
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;
    float groundHeight = g_groundTexture.getSize().y;

    //sky area
    float skyHeight = windowHeight - groundHeight;

    //col and row size
    float colWidth = windowWidth / CONSOLE_WIDTH;
    float rowHeight = skyHeight / CONSOLE_HEIGHT;

    //pipe scale
    float pipeTextureWidth = g_pipeTopTexture.getSize().x;
    float targetPipeWidth = PIPE_WIDTH * colWidth;
    float pipeScale = targetPipeWidth / pipeTextureWidth;

    //drawing pipes
    for (int i = 0; i < MAX_PIPES; i++)
    {
        //converting to pixels
        float xPixels = pipeX[i] * colWidth;
        float gapTopPixels = pipeGapY[i] * rowHeight;
        float gapHeightPixels = PIPE_GAP * rowHeight;

        //darwing top pipe
        Sprite topPipe(g_pipeTopTexture);
        float topPipeHeight = g_pipeTopTexture.getSize().y * pipeScale;
        topPipe.setScale({ pipeScale, pipeScale });
        topPipe.setPosition({ xPixels, gapTopPixels - topPipeHeight });
        window.draw(topPipe);

        //drawing bottom pipe
        Sprite bottomPipe(g_pipeBottomTexture);
        bottomPipe.setScale({ pipeScale, pipeScale });
        bottomPipe.setPosition({ xPixels, gapTopPixels + gapHeightPixels });
        window.draw(bottomPipe);
    }
}

//sound functions
void playFlapSound()
{
    g_flapS.play();
}

void playHitSound()
{
    g_hitS.play();
}

void playPointSound()
{
    g_pointS.play();
}
