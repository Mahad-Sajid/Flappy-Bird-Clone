#include "filehandling.h"
#include "globals.h"
#include <fstream>
#include <iostream>
#include <cstdio>  
using namespace std;

void saveGame(int slot)
{
    char filename[20];
    snprintf(filename, sizeof(filename), "savegame%d.txt", slot);

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
        cout << "Save Failed!" << endl;
    }
}

bool loadGame(int slot)
{
    char filename[20];
    snprintf(filename, sizeof(filename), "savegame%d.txt", slot);

    ifstream inFile(filename);

    if (inFile.is_open())
    {
        // check empty file
        inFile.seekg(0, ios::end);
        streampos fileSize = inFile.tellg();

        if (fileSize == 0)
        {
            inFile.close();
            remove(filename);
            cout << "Empty save file deleted from slot " << slot << "!" << endl;
            return false;
        }

        inFile.seekg(0, ios::beg);

        // load data
        inFile >> birdY;
        inFile >> birdVelocity;
        inFile >> birdSpriteIndex;
        inFile >> currentScore;
        inFile >> currentTheme;

        for (int i = 0; i < MAX_PIPES; i++)
        {
            inFile >> pipeX[i];
            inFile >> pipeGapY[i];
            inFile >> scoreIncremented[i];
        }

        inFile.close();
        cout << "Game Loaded from slot " << slot << "!" << endl;
        return true;
    }

    cout << "No saved game found in slot " << slot << "!" << endl;
    return false;
}

bool hasSaveData(int slot)
{
    char filename[20];
    snprintf(filename, sizeof(filename), "savegame%d.txt", slot);

    ifstream inFile(filename);

    if (!inFile.is_open())
        return false;

    inFile.seekg(0, ios::end);
    streampos fileSize = inFile.tellg();

    if (fileSize == 0)
    {
        inFile.close();
        remove(filename);
        return false;
    }

    inFile.close();
    return true;
}

void loadHighScores()
{
    ifstream inFile("highscores.txt");

    if (inFile.is_open())
    {
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            inFile >> highScores[i];
        }
        inFile.close();
    }
    else
    {
        // initialize with zeros
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            highScores[i] = 0;
        }
    }
}
void saveHighScores()
{
    ofstream outFile("highscores.txt");

    if (outFile.is_open())
    {
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            outFile << highScores[i] << endl;
        }
        outFile.close();
    }
}

void updateHighScores(int newScore)
{
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

void saveSettings()
{
    string filename = "settings.txt";
    ofstream outFile(filename);

    if (outFile.is_open())
    {
        // save birdSpriteIndex and currentTheme
        outFile << birdSpriteIndex << '\n';
        outFile << currentTheme << '\n';
        outFile.close();
    }

}

void loadSettings()
{
    string filename = "settings.txt";
    ifstream inFile(filename);

    if (inFile.is_open())
    {
        // load saved values
        inFile >> birdSpriteIndex;
        inFile >> currentTheme;
        inFile.close();
    }
    else
    {
        // default values if file does not exist yet
        birdSpriteIndex = 0;   // Yellow bird as default
        currentTheme = 0;   // Day theme as default (if you use themes)
    }
}
