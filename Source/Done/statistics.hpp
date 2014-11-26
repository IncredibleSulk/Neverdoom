#include "includes.hpp"

string statisticsFile = "Data/Statistics.txt";

int shotsFired;
int shotsMissed;

void loadStatistics () {
    ifstream readStats;
    readStats.open(statisticsFile);


//        if (readStats) readStats >> enemyKilled; else enemyKilled = 0;
//        if (readStats) readStats >> shotsFired; else shotsFired = 0;
//        if (readStats) readStats >> shotsMissed; else shotsMissed = 0;



    while (readStats) {
        // Clear all others
        string flush;
        readStats >> flush;
        }
    //accuracy = (shotsMissed * 100) / shotsFired;

    readStats.close();
    }



void saveStatistics () {
    ofstream writeStats;
    writeStats.open(statisticsFile);

//    writeStats << enemyKilled << "\n";
//    writeStats << shotsFired << "\n";
//    writeStats << shotsMissed << "\n";

    writeStats.close();
    }
