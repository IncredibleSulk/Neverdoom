#include "includes.hpp"

int soundMenu() {
    enum buttonNames {
        Title,
        Sound,
        VolumeButton,
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
            textManager[i].setString("Sound Menu");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::Sound:
            textManager[i].setString("Sound  Off"); // Longest String
            Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 40, textManager[i].getLocalBounds().height + 20));
            if (soundEnabled) {
                textManager[i].setString("Sound  On");
                } else {
                    textManager[i].setString("Sound  Off");
                    }
            break;

            case buttonNames::VolumeButton:
            textManager[i].setString("Volume"); // Longest String
            Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 40, textManager[i].getLocalBounds().height + 20));
            break;

            case buttonNames::Back:
            textManager[i].setString("Back");
            textManager[i].setPosition(15, 518);
            break;
            }

        Button[i].setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y);
        Button[i].setFillColor(sf::Color(0, 0, 0));
        Button[i].setOutlineThickness(5);
        Button[i].setOutlineColor(sf::Color(255, 0, 0));

        textYPosition += fontPadding;
        }

    sf::RectangleShape volumeBar;
    sf::RectangleShape volumeSlider;

    bool playSample = false;
    sf::Clock sampleDelay;

    volumeBar.setSize(sf::Vector2f(494, 20));
    volumeBar.setOutlineThickness(3);
    volumeBar.setPosition((App.getSize().x/2) - (volumeBar.getGlobalBounds().width/2), (textManager[VolumeButton].getGlobalBounds().top + textManager[VolumeButton].getGlobalBounds().height) + 20);
    volumeBar.setFillColor(sf::Color::Black);
    volumeBar.setOutlineColor(sf::Color::Red);

    volumeSlider.setSize(sf::Vector2f(20, 40));
    volumeSlider.setOutlineThickness(3);
    volumeSlider.setOrigin(sf::Vector2f(volumeSlider.getGlobalBounds().width/2, volumeSlider.getGlobalBounds().height/2));

    volumeSlider.setPosition(volumeBar.getGlobalBounds().left + (Volume * 5), (volumeBar.getGlobalBounds().top + (volumeBar.getGlobalBounds().height/2)));

    volumeSlider.setFillColor(sf::Color::Black);
    volumeSlider.setOutlineColor(sf::Color::Green);

    while (App.isOpen()) {
        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 1  && !menuEntered) {
                if (soundEnabled) buttonSound.play();
                menuEntered = true;
                menuTimer.restart();
                return 0;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
                return 0;
                }

            if (Event.type == Event.MouseMoved || (controllerConnected && Event.type == Event.JoystickMoved)) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                if (Event.joystickMove.axis == sf::Joystick::X && controllerMenuItem == buttonNames::VolumeButton) {
                    controllerMenuTimer.restart();
                    cursorActive = false;
                    double volumeAdjustment = 2;
                    if (Event.joystickMove.position > 0) {
                        if (Volume <= 100 - volumeAdjustment) {
                            Volume += volumeAdjustment;
                            volumeSlider.setPosition(volumeBar.getGlobalBounds().left + (Volume * 5), (volumeBar.getGlobalBounds().top + (volumeBar.getGlobalBounds().height/2)));
                        } else Volume = 100;

                        setGlobalVolume();
                        playSample = true;
                        }
                    if (Event.joystickMove.position < 0) {
                        if (Volume >= 0 + volumeAdjustment) {
                            Volume -= volumeAdjustment;
                            volumeSlider.setPosition(volumeBar.getGlobalBounds().left + (Volume * 5), (volumeBar.getGlobalBounds().top + (volumeBar.getGlobalBounds().height/2)));
                        } else Volume = 0;

                        setGlobalVolume();
                        playSample = true;
                        }
                        } else volumeSlider.setOutlineColor(sf::Color::Green);

                if (Event.joystickMove.axis == sf::Joystick::Y && controllerMenuTimer.getElapsedTime().asSeconds() > controllerMenuTimeout) {
                    controllerMenuTimer.restart();
                    cursorActive = false;
                    if (Event.joystickMove.position > 0) {
                        controllerMenuItem++;
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::Sound;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::Sound) controllerMenuItem = buttonNames::Back;
                        }
                    } else {
                        cursor.setPosition(X, Y);
                        cursorActive = true;
                        }

                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if (textManager[i].getGlobalBounds().contains(X, Y) || i == controllerMenuItem) {
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
                        if (textManager[i].getGlobalBounds().contains(X, Y)) buttonActive[i] = false, textManager[i].setColor(sf::Color(255, 255, 255));
                        switch (i) {

                            case buttonNames::Sound:
                            soundEnabled = !soundEnabled;
                            if (soundEnabled) {
                                textManager[i].setString("Sound  On");
                                } else {
                                    textManager[i].setString("Sound  Off");
                                    }
                            break;

                            case buttonNames::VolumeButton:
                            if (Volume < 100) Volume = 100;
                            else Volume = 0;
                            volumeSlider.setPosition(volumeBar.getGlobalBounds().left + (Volume * 5), (volumeBar.getGlobalBounds().top + (volumeBar.getGlobalBounds().height/2)));
                            setGlobalVolume();
                            playSample = true;
                            break;

                            case buttonNames::Back:
                            menuEntered = true;
                            menuTimer.restart();
                            return 0;
                            break;
                            }
                        }
                    }
                }
            }

        //Reduce Scope
        if (true) {
            float X = sf::Mouse::getPosition(App).x;
            float Y = sf::Mouse::getPosition(App).y;

            volumeSlider.setOutlineColor(sf::Color::Green);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && volumeBar.getGlobalBounds().contains(X, Y)) {
                volumeSlider.setPosition(X, volumeSlider.getPosition().y);
                volumeSlider.setOutlineColor(sf::Color::Cyan);

                float maxVolume = volumeBar.getGlobalBounds().width;
                float differenceVolume = ((volumeBar.getGlobalBounds().left + volumeBar.getGlobalBounds().width) - volumeSlider.getPosition().x);

                Volume = (maxVolume - differenceVolume)/5;

                setGlobalVolume();
                playSample = true;
                }
            }

        if (playSample && sampleDelay.getElapsedTime().asSeconds() > 0.1) sampleDelay.restart(), playSample = false, laserSound.play();
        if (menuTimer.getElapsedTime().asSeconds() > 0.1) menuEntered = false;
        App.clear();
        App.draw(background);

        for (int i = 0; i < buttonNames::ButtonNumber; i++) {
            if (buttonActive[i]) App.draw(Button[i]);
            App.draw(textManager[i]);
            }

        App.draw(volumeBar);
        App.draw(volumeSlider);

        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }

    return 0;
}

