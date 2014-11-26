#include "includes.hpp"

#define ACHIEVEMENT_FILE "Data/Achievements.txt"

sf::Clock achievementTimer;
int achievementTotal = 0;

//TODO Make Achievements
enum Achievements {
    sample1,
    sample2,
    sample3,
    sample4,

    completedAll,

    ACHIEVEMENTNUMBER
    };


struct Achievement {

    bool Achieved;
    int Number;

    string Name;
    string Message;
    string completionMessage;

    bool checkCriteria () {
            bool newlyAchieved = false;

            switch (Number) {

//                case babySteps:
//                Name = "Baby Steps";
//                Message = "Play the tutorial";
//                if (!Achieved && tutorialPlaying) {
//                    newlyAchieved = true;
//                    }
//                break;

                case sample1:
                Name = "sample1";
                Message = "This is just a test";
//                if (!Achieved && tutorialPlaying) {
//                    newlyAchieved = true;
//                    }
                break;

                case sample2:
                Name = "sample2";
                Message = "This is just a test";
//                if (!Achieved && tutorialPlaying) {
//                    newlyAchieved = true;
//                    }
                break;

                case sample3:
                Name = "sample3";
                Message = "This is just a test";
//                if (!Achieved && tutorialPlaying) {
//                    newlyAchieved = true;
//                    }
                break;

                case sample4:
                Name = "sample4";
                Message = "This is just a test";
//                if (!Achieved && tutorialPlaying) {
//                    newlyAchieved = true;
//                    }
                break;


                case completedAll:
                Name = "Achievement Completion!";
                Message = "Achieve everything!!";
                break;


            } // End of Switch Statement

            if (newlyAchieved) {
                completionMessage = "You got the Achievement :\n " + Name + "!";
                return Achieved = true;
                }
            // When true is returned it
            // activates the notification
            return false;
        }

    Achievement () {
        Number = achievementTotal;
        achievementTotal++;
        };

    ~Achievement () {};
    };


Achievement *achievementManager;


void initAchievements () {
    achievementManager = new Achievement [ACHIEVEMENTNUMBER];

    ifstream readStream;
    readStream.open(ACHIEVEMENT_FILE);

    for (int i = 0; i < ACHIEVEMENTNUMBER; i++) {
        if (readStream) readStream >> achievementManager[i].Achieved;
        else achievementManager[i].Achieved = false;
        achievementManager[i].checkCriteria();
        }

    readStream.close();
    }


void saveAchievements () {
    ofstream writeStream;

    writeStream.open(ACHIEVEMENT_FILE);

    for (int i = 0; i < ACHIEVEMENTNUMBER; i++) {
        writeStream << achievementManager[i].Achieved;
        if (i < ACHIEVEMENTNUMBER - 1) writeStream << "\n";
        }

    writeStream.close();
    }


void achievementHandler () {
    int numberAchieved = 0;
    for (int i = 0; i < ACHIEVEMENTNUMBER; i++) {
        if (achievementManager[i].checkCriteria()) {
            notify(achievementManager[i].completionMessage);
            }
        if (achievementManager[i].Achieved) numberAchieved++;
        }
    if (numberAchieved == ACHIEVEMENTNUMBER - 1 && !achievementManager[Achievements::completedAll].Achieved) {
        achievementManager[Achievements::completedAll].Achieved = true;
        achievementManager[Achievements::completedAll].completionMessage = "Congratulations!\nYou've got all the Achievements!";
        notify(achievementManager[Achievements::completedAll].completionMessage);
        numberAchieved++;
        }
    }

