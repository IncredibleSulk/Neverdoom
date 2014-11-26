#include "includes.hpp"

int pauseMenu () {
//    cursor.setPosition(crosshair.getPosition().x, crosshair.getPosition().y);
    enum buttonNames {
        Title,
        ResumeGame,
        Highscores,
        Achievements,
        Controls,
        Options,
        Quit,

        ButtonNumber
        };

    sf::Text *textManager;
    textManager = new sf::Text [ButtonNumber];
    int textYPosition = fontYDefault;

    bool *buttonActive;
    buttonActive = new bool [ButtonNumber];

    sf::RectangleShape *Button;
    Button = new sf::RectangleShape [ButtonNumber];

    int controllerMenuItem = ButtonNumber;
    sf::Clock controllerMenuTimer;

    for (int i = 0; i < buttonNames::ButtonNumber; i++) {
        buttonActive[i] = false;
        textManager[i].setFont(Font);
        textManager[i].setPosition(250, textYPosition);
        textManager[i].setCharacterSize(fontSize);

        switch (i) {
            case buttonNames::Title:
            textManager[i].setColor(sf::Color(220, 20, 60));
            textManager[i].setString("Pause Menu");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::ResumeGame:
            textManager[i].setString("Resume Game");
            break;

            case buttonNames::Highscores:
            textManager[i].setString("Highscores");
            break;

            case buttonNames::Achievements:
            textManager[i].setString("Achievements");
            break;

            case buttonNames::Controls:
            textManager[i].setString("Controls");
            break;

            case buttonNames::Options:
            textManager[i].setString("Options");
            break;

            case buttonNames::Quit:
            if (gamePlaying) textManager[i].setString("Quit");
            break;
            }
        Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 20, textManager[i].getLocalBounds().height + 20));
        Button[i].setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y);
        Button[i].setRotation(textManager[i].getRotation());
        Button[i].setFillColor(sf::Color(0, 0, 0));
        Button[i].setOutlineThickness(5);
        Button[i].setOutlineColor(sf::Color(255, 0, 0));

        textYPosition += fontPadding;
        }

    while (App.isOpen()) {

        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 7) return 0;

            if (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 1 && !menuEntered) {
                if (soundEnabled) buttonSound.play();
                menuEntered = true;
                menuTimer.restart();
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
                        if (controllerMenuItem > buttonNames::Quit) controllerMenuItem = buttonNames::ResumeGame;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::ResumeGame) controllerMenuItem = buttonNames::Quit;
                        }
                    } else {
                        cursor.setPosition(X, Y);
                        cursorActive = true;
                        }

                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if (textManager[i].getGlobalBounds().contains(X, Y) || controllerMenuItem == i) {
                            controllerMenuItem = i;
                            textManager[i].setColor(sf::Color(255, 0, 0));
                            buttonActive[i] = true;
                            } else {
                                textManager[i].setColor(sf::Color(255, 255, 255));
                                buttonActive[i] = false;
                                }
                    }
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
//                crosshair.setPosition(cursor.getPosition().x, cursor.getPosition().y);
//                Player.shotDelayEnded = false;
//                Player.shotRestartTimer.restart();
                return 0;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::P) {
//                crosshair.setPosition(cursor.getPosition().x, cursor.getPosition().y);
//                Player.shotDelayEnded = false;
//                Player.shotRestartTimer.restart();
                return 0;
                }

            if (Event.type == Event.MouseButtonPressed || (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 0 && controllerMenuItem != 0)) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if (textManager[i].getGlobalBounds().contains(X, Y) || controllerMenuItem == i) {
                            if (soundEnabled) buttonSound.play();
                            if (textManager[i].getGlobalBounds().contains(X, Y)) buttonActive[i] = false, textManager[i].setColor(sf::Color(255, 255, 255));
                            switch (i) {

                                case buttonNames::ResumeGame:
//                                crosshair.setPosition(cursor.getPosition().x, cursor.getPosition().y);
//                                Player.shotDelayEnded = false;
//                                Player.shotRestartTimer.restart();
                                return 0;
                                break;

                                case buttonNames::Highscores:
                                highscoreMenu();
                                break;

                                case buttonNames::Achievements:
                                achievementsMenu();
                                break;

                                case buttonNames::Controls:
                                if (Event.type == Event.JoystickButtonPressed) controlsMenu(Event.joystickButton.joystickId);
                                else controlsMenu(0);
                                break;

                                case buttonNames::Options:
                                optionsMenu();
                                break;

                                case buttonNames::Quit:
                                gameQuit = true;
                                return 0;
                                break;
                                }

                            }
                    }
                }
            }
        if (menuTimer.getElapsedTime().asSeconds() > 0.1) menuEntered = false;
        App.clear();
        App.draw(background);

        for (int i = 0; i < buttonNames::ButtonNumber; i++) {
            if (buttonActive[i]) App.draw(Button[i]);
            App.draw(textManager[i]);
            }

        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }

    return 0;
}

