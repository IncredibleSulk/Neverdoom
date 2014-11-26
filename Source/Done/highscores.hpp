#include "includes.hpp"

#define HIGHSCORE_FILE "Data/Highscores.txt"
#define maxNameSize 10

typedef pair <int, string> Score;
typedef map  <int, string> highscoreMap;

// Uses ifstream readStream;
// Uses ofstream writeStream;

sf::Text *highscoreNameString;
sf::Text *highscoreScoreString;

highscoreMap highscoreTable;

string *highscoreName;
int *highscoreScore;
int lowestScore;

bool fileRead = false;


void sortScores () {
    int index = 0;

    for (highscoreMap::reverse_iterator i = highscoreTable.rbegin(); i != highscoreTable.rend(); i++){
        if (index >= 10) break;
        if (index == 9) {
            lowestScore = i->first;
            }

        string str;
        stringstream stream;

        stream << i->second;
        str = stream.str();
        highscoreNameString[index].setString(str);

        stream.str("");
        stream << " : " << i->first;
        str = stream.str();
        highscoreScoreString[index].setString(str);

        if (i ->first == previousScore) highscoreNameString[index].setColor(sf::Color::Red), highscoreScoreString[index].setColor(sf::Color::Red);
        else highscoreNameString[index].setColor(sf::Color::Cyan), highscoreScoreString[index].setColor(sf::Color::Cyan);

        index++;
        }
    }


void loadScores () {
    if (!fileRead) {
        ifstream readStream;

        highscoreNameString = new sf::Text [10];
        highscoreScoreString = new sf::Text [10];

        highscoreName = new string [10];
        highscoreScore = new int [10];

        readStream.open(HIGHSCORE_FILE);

        int position = fontYDefault + headerPadding;

        if (!readStream) {
            highscoreTable.insert(Score (100000, "Godlike   "));
            highscoreTable.insert(Score (90000,  "Boss      "));
            highscoreTable.insert(Score (80000,  "Awesome   "));
            highscoreTable.insert(Score (70000,  "Gamer     "));
            highscoreTable.insert(Score (60000,  "Adept     "));
            highscoreTable.insert(Score (50000,  "Proficient"));
            highscoreTable.insert(Score (40000,  "Practiced "));
            highscoreTable.insert(Score (30000,  "Learner   "));
            highscoreTable.insert(Score (20000,  "Noob      "));
            highscoreTable.insert(Score (10000,  "Socialite "));
            }

        for (int i = 0; i < 10; i++) {
            if (readStream) {
                readStream >> highscoreName[i];
                readStream >> highscoreScore[i];

                highscoreName[i].resize(maxNameSize, ' ');

                highscoreTable.insert(Score (highscoreScore[i], highscoreName[i]));
                }

            position += 42;
            highscoreNameString[i].setCharacterSize(fontSize - 20);
            highscoreNameString[i].setPosition( 100, position);
            highscoreNameString[i].setColor(sf::Color(0, 255, 255));
            highscoreNameString[i].setFont(Font);

            highscoreScoreString[i].setCharacterSize(fontSize - 20);
            highscoreScoreString[i].setPosition( 400, position);
            highscoreScoreString[i].setColor(sf::Color(0, 255, 255));
            highscoreScoreString[i].setFont(Font);
            }

        sortScores();
        fileRead = true;
        readStream.close();
        }
    }




int insertScore () {
    sf::Text Text, Prompt, titlePrompt;

    titlePrompt.setFont(Font);
    titlePrompt.setColor(sf::Color::Red);
    titlePrompt.setString("HIGH SCORE");
    titlePrompt.setCharacterSize(75);
    titlePrompt.setPosition((App.getSize().x/2 - titlePrompt.getGlobalBounds().width/2), 50);

    Prompt.setFont(Font);
    Prompt.setColor(sf::Color::Red);
    Prompt.setString("Enter Your Name :");
    Prompt.setPosition((App.getSize().x/2 - Prompt.getGlobalBounds().width/2), 250);

    Text.setFont(Font);
    Text.setPosition((App.getSize().x/2 - Text.getGlobalBounds().width/2), 300);
    Text.setCharacterSize(40);
    string input;

    bool validInsert = false;

    ofstream writeStream;
    stringstream stream;

    string name;

    if (score < lowestScore) return 0;


    while (App.isOpen() && !validInsert){
        while (App.pollEvent(Event)){
            if (Event.type == Event.Closed) {
                saveSettings();
                App.close();
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) return 0;

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Return) {

                name = input;
                while (name.find(' ') != string::npos) {
                    int pos = name.find(' ');
                    name.replace(pos, 1, "_");
                    }
                name.resize(maxNameSize, ' ');

                input.clear();
                Text.setString(input);
                Text.setPosition(400, 300);
                validInsert = true;
                }

            if (Event.type == Event.TextEntered) {
                //Handle Backspaces
                if (Event.text.unicode == 8) {
                    if (input.length() > 0) {
                        input.resize(input.length() - 1);
                        Text.setString(input);
                        Text.setPosition((App.getSize().x/2 - Text.getGlobalBounds().width/2), 300);
                        }
                    } else if (Event.text.unicode == 13) {
                            //No New Lines
                            } else {
                                input += static_cast <char> (Event.text.unicode);
                                Text.setString(input);
                                Text.move(-10, 0);
                                }
                }
            }

        App.clear();
        App.draw(titlePrompt);
        App.draw(Prompt);
        App.draw(Text);
        App.display();
        }

    if (highscoreTable.find(score) == highscoreTable.end()) highscoreTable.insert(Score(score, name));
    else highscoreTable[score] = name;

    previousScore = score;
    return 0;
    }


void saveScores () {
    ofstream writeStream;
    writeStream.open(HIGHSCORE_FILE);
    int index = 0;

    for (highscoreMap::reverse_iterator i = highscoreTable.rbegin(); i != highscoreTable.rend(); i++){
        if (index >= 10) break;
        writeStream << i->second << "\n";
        writeStream << i->first << "\n";
        index++;
        }
    writeStream.close();
    }
