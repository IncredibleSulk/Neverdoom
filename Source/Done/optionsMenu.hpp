#include "includes.hpp"


int optionsMenu() {
    enum buttonNames {
        Title,
        Fullscreen,
        Sound,
        ProgressMenu,
        Back,

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
        textManager[i].setCharacterSize(fontSize);
        textManager[i].setPosition(150, textYPosition);
        switch (i) {
            case buttonNames::Title:
            textManager[i].setColor(sf::Color(220, 20, 60));
            textManager[i].setString("Options Menu");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::Fullscreen:
            textManager[i].setString("Fullscreen  Off");  // Longest String
            Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 40, textManager[i].getLocalBounds().height + 20));
            if (fullscreenEnabled) {
                textManager[i].setString("Fullscreen  On");
                } else {
                    textManager[i].setString("Fullscreen  Off");
                    }
            break;

            case buttonNames::Sound:
            textManager[i].setString("Sound  Options");
            break;

            case buttonNames::ProgressMenu:
            textManager[i].setString("Progress Menu");
            break;

            case buttonNames::Back:
            textManager[i].setString("Back");
            textManager[i].setPosition(15, 518);
            break;
            }
        if (i != Fullscreen) Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 20, textManager[i].getLocalBounds().height + 20));
        Button[i].setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y);
        Button[i].setFillColor(sf::Color(0, 0, 0));
        Button[i].setOutlineThickness(5);
        Button[i].setOutlineColor(sf::Color(255, 0, 0));

        textYPosition += fontPadding;
        }


    while (App.isOpen()) {
        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 1 && !menuEntered) {
                if (soundEnabled) buttonSound.play();
                menuEntered = true;
                menuTimer.restart();
                return 0;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
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
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::Fullscreen;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::Fullscreen) controllerMenuItem = buttonNames::Back;
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
                            menuEntered = false;
                            }
                    }
                }

            if (Event.type == Event.MouseButtonPressed || (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 0 && controllerMenuItem != 0)) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if ((textManager[i].getGlobalBounds().contains(X, Y) && !menuEntered) || controllerMenuItem == i) {
                        controllerMenuItem = i;
                        if (soundEnabled) buttonSound.play();
                        if (gamePlaying && i == ProgressMenu) continue;

                        menuEntered = true;
                        menuTimer.restart();
                        if (textManager[i].getGlobalBounds().contains(X, Y)) buttonActive[i] = false, textManager[i].setColor(sf::Color(255, 255, 255));
                        switch (i) {

                            case buttonNames::Fullscreen:
                            fullscreenEnabled = !fullscreenEnabled;
                            App.close();
                            if (fullscreenEnabled) {
                                textManager[i].setString("Fullscreen  On");
                                App.create(VideoMode, GAMENAME, sf::Style::Fullscreen);
                                App.setMouseCursorVisible(false);
                                } else {
                                    textManager[i].setString("Fullscreen  Off");
                                    App.create(VideoMode, GAMENAME);
                                    App.setMouseCursorVisible(false);
                                    }
                            //
                            //App.setIcon(32, 32, Icon.getPixelsPtr());
                            break;

                            case buttonNames::Sound:
                            soundMenu();
                            break;

                            case buttonNames::ProgressMenu:
                            progressMenu();
                            break;

                            case buttonNames::Back:
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
            if (gamePlaying && i == ProgressMenu) continue;

            if (buttonActive[i]) App.draw(Button[i]);
            App.draw(textManager[i]);
            }

        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }

    return 0;
}
