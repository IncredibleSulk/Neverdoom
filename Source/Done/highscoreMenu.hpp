#include "includes.hpp"

int highscoreMenu() {

    enum buttonNames {
        Title,
        Back,
        ButtonNumber
        };

    sf::Text *textManager;
    textManager = new sf::Text [ButtonNumber];
    int textYPosition = fontYDefault;

    bool buttonActive = false;

    sf::RectangleShape Button;

    int controllerMenuItem = ButtonNumber;
    sf::Clock controllerMenuTimer;

    for (int i = 0; i < buttonNames::ButtonNumber; i++) {
        textManager[i].setFont(Font);
        textManager[i].setPosition(300, textYPosition);
        textManager[i].setCharacterSize(fontSize);

        switch (i) {
            case buttonNames::Title:
            textManager[i].setColor(sf::Color(220, 20, 60));
            textManager[i].setString("Highscores");
            textManager[i].setCharacterSize(80);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::Back:
            textManager[i].setString("Back");
            textManager[i].setColor(sf::Color(255, 255, 255));
            textManager[i].setPosition(15, 518);

            Button.setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 20, textManager[i].getLocalBounds().height + 20));
            Button.setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y);
            Button.setFillColor(sf::Color(0, 0, 0));
            Button.setOutlineThickness(5);
            Button.setOutlineColor(sf::Color(255, 0, 0));
            break;
            }

        textYPosition += fontPadding;
        }

    if (!fileRead) loadScores();
    else sortScores();

    while (App.isOpen()) {
        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 1 && !menuEntered) {
                if (soundEnabled) buttonSound.play();
                menuEntered = true;
                menuTimer.restart();
                saveScores();
                return 0;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
                saveScores();
                return 0;
                }

            if (Event.type == Event.MouseMoved || (controllerConnected && Event.type == Event.JoystickMoved && controllerMenuTimer.getElapsedTime().asSeconds() > controllerMenuTimeout)) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;

                if (Event.joystickMove.axis == sf::Joystick::Y) {
                    controllerMenuTimer.restart();
                    cursorActive = false;
                    if (Event.joystickMove.position > 0) {
                        controllerMenuItem++;
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::Back;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::Back) controllerMenuItem = buttonNames::Back;
                        }
                    } else {
                        cursor.setPosition(X, Y);
                        cursorActive = true;
                        }

                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if (textManager[i].getGlobalBounds().contains(X, Y) || controllerMenuItem == i) {
                        textManager[i].setColor(sf::Color(255, 0, 0));
                        buttonActive = true;
                        } else {
                            textManager[i].setColor(sf::Color(255, 255, 255));
                            buttonActive = false;
                            menuEntered = false;
                            }
                    }
                }

            if (Event.type == Event.MouseButtonPressed || (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 0 && controllerMenuItem != 0)) {
                if (Event.type == Event.MouseButtonPressed) {
                    float X = sf::Mouse::getPosition(App).x;
                    float Y = sf::Mouse::getPosition(App).y;

                    if (textManager[buttonNames::Back].getGlobalBounds().contains(X, Y)  || controllerMenuItem == Back) {
                        textManager[buttonNames::Back].setColor(sf::Color(255, 255, 255));
                        if (soundEnabled) buttonSound.play();
                        buttonActive = false;
                        saveScores();
                        return 0;
                        }
                    }
                }
            }
        if (menuTimer.getElapsedTime().asSeconds() > 0.1) menuEntered = false;
        App.clear();
        App.draw(background);

        if (buttonActive) App.draw(Button);
        for (int i = 0; i < buttonNames::ButtonNumber; i++) App.draw(textManager[i]);

        for (int i = 0; i < 10; i++) {
            App.draw(highscoreNameString[i]);
            App.draw(highscoreScoreString[i]);
            }

        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }

    return 0;
}
