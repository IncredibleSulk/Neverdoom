#include "includes.hpp"

sf::Sprite loadSpriteData (string Name) {
    ifstream readStream;
    readStream.open("Graphics/" + GAMENAME + ".txt");

    string currentName;
    sf::IntRect IntRect;
    sf::Sprite Sprite;

    while (readStream) {
        string buffer;

        getline (readStream, buffer, ':');

        bool replaced = false;

        string replace = " (front 1)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 1");
            currentName = buffer;

            getline (readStream, buffer, ':');
            IntRect.left = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.top = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.width = stringToInt(buffer);

            getline (readStream, buffer);
            IntRect.height = stringToInt(buffer);
            }

        replace = " (front 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 2");
            currentName = buffer;

            getline (readStream, buffer, ':');
            IntRect.left = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.top = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.width = stringToInt(buffer);

            getline (readStream, buffer);
            IntRect.height = stringToInt(buffer);
            }

        replace = " (back 1)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 3");
            currentName = buffer;

            getline (readStream, buffer, ':');
            IntRect.left = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.top = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.width = stringToInt(buffer);

            getline (readStream, buffer);
            IntRect.height = stringToInt(buffer);
            }

        replace = " (back 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 4");
            currentName = buffer;

            getline (readStream, buffer, ':');
            IntRect.left = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.top = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.width = stringToInt(buffer);

            getline (readStream, buffer);
            IntRect.height = stringToInt(buffer);
            }


        if (!replaced) {
            currentName = buffer;

            getline (readStream, buffer, ':');
            IntRect.left = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.top = stringToInt(buffer);

            getline (readStream, buffer, ':');
            IntRect.width = stringToInt(buffer);

            getline (readStream, buffer);
            IntRect.height = stringToInt(buffer);
            }

        buffer.clear();
        if (currentName == Name) break;
        }

    Sprite.setTexture(Spritesheet);
    Sprite.setTextureRect(IntRect);
    readStream.close();
    return Sprite;
    }

void generateSpriteNames () {
    ifstream readStream;
    ofstream writeStream;
    readStream.open("Graphics/"+ GAMENAME +".txt");
    writeStream.open("Graphics/Names.txt");

    while (readStream) {
        string buffer;

        getline (readStream, buffer, ':');

        bool replaced = false;

        string replace = " (front 1)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;

            buffer.replace(buffer.find(replace), replace.length(), "");

            while (buffer.find(" ") != string::npos) buffer.replace(buffer.find(" "), 1, "_");
            writeStream << buffer << ",\n";

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (front 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 2");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (back 1)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 3");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (back 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 4");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }


        if (!replaced) {
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        buffer.clear();
        }

    readStream.close();
    writeStream.close();
    }

void generateCaseStatements () {
    ifstream readStream;
    ofstream writeStream;
    readStream.open("Graphics/" + GAMENAME +".txt");
    writeStream.open("Graphics/Cases.txt");

    while (readStream) {
        string buffer;

        getline (readStream, buffer, ':');

        bool replaced = false;

        string replace = " (front 1)";
        if (buffer.find(replace) != string::npos) {

            string speed, health;

            if (buffer.find("Icy") != string::npos || buffer.find("Arctic") != string::npos || buffer.find("Snowy") != string::npos) health = "160";
            else if (buffer.find("Red") != string::npos || buffer.find("Fire") != string::npos) health = "150";
            else if (buffer.find("Pink") != string::npos) health = "120";
            else if (buffer.find("Green") != string::npos || buffer.find("Emerald") != string::npos) health = "115";
            else if (buffer.find("Brown") != string::npos) health = "90";
            else if (buffer.find("Blue") != string::npos || buffer.find("Sky") != string::npos) health = "130";
            else if (buffer.find("Yellow") != string::npos) health = "140";
            else if (buffer.find("Purple") != string::npos) health = "125";
            else if (buffer.find("Grey") != string::npos) health = "95";
            else if (buffer.find("Orange") != string::npos) health = "135";
            else  health = "100";

            if (buffer.find("Boar") != string::npos)  speed = "120";
            else if (buffer.find("Sparky") != string::npos)  speed = "110";
            else if (buffer.find("Skeleton") != string::npos)  speed = "80";
            else if (buffer.find("Vampire") != string::npos)  speed = "130";
            else if (buffer.find("Zombie") != string::npos)  speed = "70";
            else if (buffer.find("Scary") != string::npos)  speed = "135";
            else if (buffer.find("Runner") != string::npos)  speed = "140";
            else if (buffer.find("Bat") != string::npos || buffer.find("Probuscbat") != string::npos)  speed = "125";
            else if (buffer.find("Phantmouse") != string::npos)  speed = "115";
            else if (buffer.find("Penduck") != string::npos)  speed = "135";
            else if (buffer.find("Ogre") != string::npos)  speed = "110";
            else if (buffer.find("Mousey") != string::npos)  speed = "106";
            else if (buffer.find("Mosqo") != string::npos)  speed = "98";
            else if (buffer.find("Minotaur") != string::npos)  speed = "135";
            else if (buffer.find("Gremlin") != string::npos)  speed = "105";
            else speed = "100";

            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), "");
            string name = buffer;
            while (buffer.find(" ") != string::npos) buffer.replace(buffer.find(" "), 1, "_");

            writeStream << "case " << buffer << ":\n";
            writeStream << "maxHealth = " << health << ";\n";
            writeStream << "Speed = " << speed << ";\n";
            writeStream << "position = 1;\n";
            writeStream << "Sprite = loadSpriteData(\"" << name << " 1\") ;\n";
            writeStream << "Sprite.setOrigin(Sprite.getGlobalBounds().width/2, Sprite.getGlobalBounds().height/2);\n";
            writeStream << "Name = \"" << name << "\";\n";
            writeStream << "break;\n\n";

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (front 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 2");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (back 1)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 3");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        replace = " (back 2)";
        if (buffer.find(replace) != string::npos) {
            replaced = true;
            buffer.replace(buffer.find(replace), replace.length(), " 4");

            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }


        if (!replaced) {
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer, ':');
            getline (readStream, buffer);
            }

        buffer.clear();
        }

    readStream.close();
    writeStream.close();
    }

void loadSpritesheet () {
    Spritesheet.loadFromFile("Graphics/" + GAMENAME + ".png");
    generateSpriteNames();
    generateCaseStatements();
    }
