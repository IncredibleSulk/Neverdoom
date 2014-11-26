#include "includes.hpp"


void setBackground () {
    int noOfBackgrounds = 4;

    backgroundNumber++;
    if (backgroundNumber >= noOfBackgrounds) backgroundNumber = 1;
    if (backgroundNumber <= 0) backgroundNumber = noOfBackgrounds;

    stringstream directory;

    directory.str("");
    directory << "Graphics/Backgrounds/";
    directory << backgroundNumber << ".PNG";

    backgroundTexture.loadFromFile(directory.str());
    background.setTexture(backgroundTexture);
    }

