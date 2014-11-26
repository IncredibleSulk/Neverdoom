#include "includes.hpp"

int loadScreen () {
    App.setMouseCursorVisible(false);

    sf::Texture logoImage;
    logoImage.loadFromFile("Graphics/Logo.png");

    sf::Sprite Logo;
    Logo.setTexture(logoImage);

    int screenColour = 1;
    sf::Clock opacityTimer;

    bool increasing = true;

    while (App.isOpen()) {
        while (App.pollEvent(Event)) {
            if (Event.type == Event.Closed) {
                saveAndQuit();
                }

            if (Event.type == Event.KeyPressed){
                return 0;
                }

            if (Event.type == Event.MouseButtonPressed){
                return 0;
                }

            if (Event.type == Event.MouseMoved){
                cursor.setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                }
            }

        if (increasing && opacityTimer.getElapsedTime().asSeconds() > 0.01) {
            opacityTimer.restart();
            screenColour += 1;
            } else if (!increasing && opacityTimer.getElapsedTime().asSeconds() > 0.01) {
                opacityTimer.restart();
                screenColour -= 1;
                }


        if (screenColour >= 255) increasing = false;
        if (screenColour <= 0) return 0;

        Logo.setColor(sf::Color(255, 255, 255, screenColour));

        App.clear(sf::Color(screenColour, screenColour, screenColour));
        App.draw(Logo);
        App.draw(cursor);
        App.display();
        Framerate = framerateTimer.restart().asSeconds();
        }
    return 0;
    }
