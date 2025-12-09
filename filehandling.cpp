#include "filehandling.h"
#include "globals.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// save current game state to a file (slot 1, 2, or 3)
void saveGame(int slot)
{
    //filename built based on slot number
    stringstream ss;
    ss << "savegame" << slot << ".txt";
    string filename = ss.str();

    ofstream outFile(filename);

    if (outFile.is_open())
    {
        // save bird data 
        outFile << birdY << endl;
        outFile << birdVelocity << endl;
        outFile << birdSpriteIndex << endl;
        outFile << currentScore << endl;
        outFile << currentTheme << endl;

        // save all pipe data
        for (int i = 0; i < MAX_PIPES; i++)
        {
            outFile << pipeX[i] << endl;
            outFile << pipeGapY[i] << endl;
            outFile << scoreIncremented[i] << endl;
        }

        outFile.close();
        cout << "Game Saved to slot " << slot << "!" << endl;
    }
    else
    {
        cout << "Save Failed!" <<endl;
    }
}

// load game from a save file
bool loadGame(int slot)
{
    // build filename
    stringstream ss;
    ss << "savegame" << slot << ".txt";
    string filename = ss.str();
    ifstream inFile(filename);

    if (inFile.is_open())
    {
        // load bird data
        inFile >> birdY;
        inFile >> birdVelocity;
        inFile >> birdSpriteIndex;
        inFile >> currentScore;
        inFile >> currentTheme;

        // load all pipe data
        for (int i = 0; i < MAX_PIPES; i++)
        {
            inFile >> pipeX[i];
            inFile >> pipeGapY[i];
            inFile >> scoreIncremented[i];
        }

        // close file
        inFile.close();
        cout << "Game Loaded from slot " << slot << "!" << endl;
        return true;  // load successful
    }
    else
    {
        cout << "No saved game found in slot " << slot << "!" << endl;
        return false;  // load failed
    }
}

// check if a save slot has data in it
bool hasSaveData(int slot)
{
    // build filename
    stringstream ss;
    ss << "savegame" << slot << ".txt";
    string filename = ss.str();
    ifstream inFile(filename);
    bool exists = inFile.is_open();

    // close if it opened successfully
    if (exists)
    {
        inFile.close();
    }

    return exists;
}

// loading highscores from file
void loadHighScores()
{
    ifstream inFile("highscores.txt");

    if (inFile.is_open())
    {
        // read all 5 high scores
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            inFile >> highScores[i];
        }
        inFile.close();
    }
    else
    {
        // if file doesn't exist, initialize with zeros
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            highScores[i] = 0;
        }
    }
}

// save high scores to file
void saveHighScores()
{
    ofstream outFile("highscores.txt");

    if (outFile.is_open())
    {
        // write all 5 scores
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            outFile << highScores[i] <<endl;
        }
        outFile.close();
    }
}

// sorting highscores
void updateHighScores(int newScore)
{
    // loop through existing high scores
    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        if (newScore > highScores[i])
        {
            for (int j = MAX_HIGH_SCORES - 1; j > i; j--)
            {
                highScores[j] = highScores[j - 1];
            }
            highScores[i] = newScore;
            saveHighScores();
            break;  
        }
    }
}
