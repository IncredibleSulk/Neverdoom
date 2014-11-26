#include "includes.hpp"

#define settingsFile "Data/Settings.txt"


void loadSettings () {
    ifstream readSaves;
    readSaves.open(settingsFile);

    if (readSaves) readSaves >> fullscreenEnabled; else fullscreenEnabled = false;
    if (readSaves) readSaves >> soundEnabled; else soundEnabled = true;
    if (readSaves) readSaves >> Volume; else Volume = 100;
    if (readSaves) readSaves >> backgroundNumber; else backgroundNumber = 1;

    while (readSaves) {
        // Clear all others
        string flush;
        readSaves >> flush;
        }

    readSaves.close();
    }



void saveSettings () {
    ofstream writeSaves;
    writeSaves.open(settingsFile);

    writeSaves << fullscreenEnabled << "\n";
    writeSaves << soundEnabled << "\n";
    writeSaves << Volume << "\n";
    writeSaves << backgroundNumber;

    writeSaves.close();
    }
