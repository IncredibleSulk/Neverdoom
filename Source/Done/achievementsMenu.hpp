#include "includes.hpp"

int achievementsMenu() {
    enum buttonNames {
        Title,
        Achievement1,
        Achievement2,
        Achievement3,
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

    int centerAchievement = 1;
    string displayText;

    int controllerMenuItem = ButtonNumber;
    sf::Clock controllerMenuTimer;


    for (int i = 0; i < buttonNames::ButtonNumber; i++) {
        buttonActive[i] = false;
        textManager[i].setFont(Font);
        textManager[i].setCharacterSize(fontSize);
        textManager[i].setPosition(50, textYPosition);
        switch (i) {
            case buttonNames::Title:
            textManager[i].setFont(Font);
            textManager[i].setColor(sf::Color(220, 20, 60));
            textManager[i].setString("Achievements");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2) - (textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += 20;
            break;


            case buttonNames::Achievement1:
            displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
            if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
            else textManager[Achievement1].setColor(sf::Color::White);
            textManager[i].setCharacterSize(40);
            textManager[i].setString(displayText);
            break;

            case buttonNames::Achievement2:
            displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
            if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
            else textManager[Achievement2].setColor(sf::Color::White);
            textManager[i].setCharacterSize(25);
            textManager[i].setString(displayText);
            break;

            case buttonNames::Achievement3:
            displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
            if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
            else textManager[Achievement3].setColor(sf::Color::White);
            textManager[i].setCharacterSize(25);
            textManager[i].setString(displayText);
            break;


            case buttonNames::Back:
            textManager[i].setFont(Font);
            textManager[i].setString("Back");
            textManager[i].setPosition(15, 518);
            textManager[i].setCharacterSize(65);
            break;
            }

        Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 20, textManager[i].getLocalBounds().height + 20));
        Button[i].setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y);
        //if (i == buttonNames::Back) Button[i].setPosition(textManager[i].getPosition().x - 10, textManager[i].getPosition().y + 18);
        Button[i].setFillColor(sf::Color(0, 0, 0));
        Button[i].setOutlineThickness(5);
        Button[i].setOutlineColor(sf::Color(255, 0, 0));

        textYPosition += 120;
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

            if ((Event.type == Event.MouseMoved) || (controllerConnected && Event.type == Event.JoystickMoved && controllerMenuTimer.getElapsedTime().asSeconds() > controllerMenuTimeout))  {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                if (Event.joystickMove.axis == sf::Joystick::Y) {
                    controllerMenuTimer.restart();
                    cursorActive = false;
                    if (Event.joystickMove.position > 0) {
                        controllerMenuItem++;
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::Achievement1;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::Achievement1) controllerMenuItem = buttonNames::Back;
                        }
                    } else {
                        cursor.setPosition(X, Y);
                        cursorActive = true;
                        }
                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if (textManager[i].getGlobalBounds().contains(X, Y) || i == controllerMenuItem) {
                            controllerMenuItem = i;
                            if (i == buttonNames::Back) textManager[i].setColor(sf::Color(255, 0, 0));
                            buttonActive[i] = true;
                            } else {
                                if (i == buttonNames::Back)textManager[i].setColor(sf::Color(255, 255, 255));
                                buttonActive[i] = false;
                                }
                    }
                }

            if (Event.type == Event.MouseWheelMoved) {
                //Scrolled Up
                if (Event.mouseWheel.delta > 0) {
                    if (centerAchievement > 1) centerAchievement--;

                    displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
                    if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
                    else textManager[Achievement1].setColor(sf::Color::White);
                    if (centerAchievement == 1) textManager[Achievement1].setCharacterSize(40);
                    else textManager[Achievement1].setCharacterSize(25);
                    textManager[Achievement1].setString(displayText);
                    Button[Achievement1].setSize(sf::Vector2f(textManager[Achievement1].getLocalBounds().width + 20, textManager[Achievement1].getLocalBounds().height + 20));
                    // Ach 2
                    displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
                    if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
                    else textManager[Achievement2].setColor(sf::Color::White);
                    if (centerAchievement > 1) textManager[Achievement2].setCharacterSize(40);
                    else textManager[Achievement2].setCharacterSize(25);
                    textManager[Achievement2].setString(displayText);
                    Button[Achievement2].setSize(sf::Vector2f(textManager[Achievement2].getLocalBounds().width + 20, textManager[Achievement2].getLocalBounds().height + 20));
                    // Ach 3
                    displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
                    if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
                    else textManager[Achievement3].setColor(sf::Color::White);
                    textManager[Achievement3].setCharacterSize(25);
                    textManager[Achievement3].setString(displayText);
                    Button[Achievement3].setSize(sf::Vector2f(textManager[Achievement3].getLocalBounds().width + 20, textManager[Achievement3].getLocalBounds().height + 20));
                    }
                //Scrolled Down
                if (Event.mouseWheel.delta < 0) {
                    if (centerAchievement < ACHIEVEMENTNUMBER - 2) centerAchievement++;

                    displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
                    if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
                    else textManager[Achievement1].setColor(sf::Color::White);
                    textManager[Achievement1].setCharacterSize(25);
                    textManager[Achievement1].setString(displayText);
                    Button[Achievement1].setSize(sf::Vector2f(textManager[Achievement1].getLocalBounds().width + 20, textManager[Achievement1].getLocalBounds().height + 20));

                    // Ach 2
                    displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
                    if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
                    else textManager[Achievement2].setColor(sf::Color::White);
                    if (centerAchievement < ACHIEVEMENTNUMBER - 2) textManager[Achievement2].setCharacterSize(40);
                    else textManager[Achievement2].setCharacterSize(25);
                    textManager[Achievement2].setString(displayText);
                    Button[Achievement2].setSize(sf::Vector2f(textManager[Achievement2].getLocalBounds().width + 20, textManager[Achievement2].getLocalBounds().height + 20));

                    // Ach 3
                    displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
                    if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
                    else textManager[Achievement3].setColor(sf::Color::White);
                    if (centerAchievement == ACHIEVEMENTNUMBER - 2) textManager[Achievement3].setCharacterSize(40);
                    else textManager[Achievement3].setCharacterSize(25);
                    textManager[Achievement3].setString(displayText);
                    Button[Achievement3].setSize(sf::Vector2f(textManager[Achievement3].getLocalBounds().width + 20, textManager[Achievement3].getLocalBounds().height + 20));
                    break;
                    }
                }

            if ((Event.type == Event.MouseButtonPressed) || (Event.type == Event.JoystickButtonPressed && Event.joystickButton.button == 0 && controllerMenuItem != 0)) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                for (int i = 1; i < buttonNames::ButtonNumber; i++) {
                    if ((textManager[i].getGlobalBounds().contains(X, Y) && !menuEntered) || i == controllerMenuItem) {
                            controllerMenuItem = i;
                            if (soundEnabled) buttonSound.play();
                            if (i == buttonNames::Back) menuEntered = true, menuTimer.restart();
                            if (i == buttonNames::Back) buttonActive[i] = false;
                            if (i == buttonNames::Back) textManager[i].setColor(sf::Color(255, 255, 255));
                            switch (i) {

                                case buttonNames::Achievement1:
                                if (centerAchievement > 1) centerAchievement--;

                                // Ach 1
                                displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
                                if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
                                else textManager[Achievement1].setColor(sf::Color::White);
                                if (centerAchievement == 1) textManager[Achievement1].setCharacterSize(40);
                                else textManager[Achievement1].setCharacterSize(25);
                                textManager[Achievement1].setString(displayText);
                                Button[Achievement1].setSize(sf::Vector2f(textManager[Achievement1].getLocalBounds().width + 20, textManager[Achievement1].getLocalBounds().height + 20));
                                // Ach 2
                                displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
                                if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
                                else textManager[Achievement2].setColor(sf::Color::White);
                                if (centerAchievement > 1) textManager[Achievement2].setCharacterSize(40);
                                else textManager[Achievement2].setCharacterSize(25);
                                textManager[Achievement2].setString(displayText);
                                Button[Achievement2].setSize(sf::Vector2f(textManager[Achievement2].getLocalBounds().width + 20, textManager[Achievement2].getLocalBounds().height + 20));
                                // Ach 3
                                displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
                                if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
                                else textManager[Achievement3].setColor(sf::Color::White);
                                textManager[Achievement3].setCharacterSize(25);
                                textManager[Achievement3].setString(displayText);
                                Button[Achievement3].setSize(sf::Vector2f(textManager[Achievement3].getLocalBounds().width + 20, textManager[Achievement3].getLocalBounds().height + 20));
                                break;




                                case buttonNames::Achievement2:
                                // Ach 1
                                displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
                                if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
                                else textManager[Achievement1].setColor(sf::Color::White);
                                textManager[Achievement1].setCharacterSize(25);
                                textManager[Achievement1].setString(displayText);
                                Button[Achievement1].setSize(sf::Vector2f(textManager[Achievement1].getLocalBounds().width + 20, textManager[Achievement1].getLocalBounds().height + 20));

                                // Ach 2
                                displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
                                if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
                                else textManager[Achievement2].setColor(sf::Color::White);
                                textManager[Achievement2].setCharacterSize(40);
                                textManager[Achievement2].setString(displayText);
                                Button[Achievement2].setSize(sf::Vector2f(textManager[Achievement2].getLocalBounds().width + 20, textManager[Achievement2].getLocalBounds().height + 20));

                                // Ach 3
                                displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
                                if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
                                else textManager[Achievement3].setColor(sf::Color::White);
                                textManager[Achievement3].setCharacterSize(25);
                                textManager[Achievement3].setString(displayText);
                                Button[Achievement3].setSize(sf::Vector2f(textManager[Achievement3].getLocalBounds().width + 20, textManager[Achievement3].getLocalBounds().height + 20));
                                break;





                                case buttonNames::Achievement3:
                                if (centerAchievement < ACHIEVEMENTNUMBER - 2) centerAchievement++;

                                displayText = achievementManager[centerAchievement - 1].Name + "\n" + achievementManager[centerAchievement - 1].Message;
                                if(achievementManager[centerAchievement - 1].Achieved) textManager[Achievement1].setColor(sf::Color::Green);
                                else textManager[Achievement1].setColor(sf::Color::White);
                                textManager[Achievement1].setCharacterSize(25);
                                textManager[Achievement1].setString(displayText);
                                Button[Achievement1].setSize(sf::Vector2f(textManager[Achievement1].getLocalBounds().width + 20, textManager[Achievement1].getLocalBounds().height + 20));

                                // Ach 2
                                displayText = achievementManager[centerAchievement].Name + "\n" + achievementManager[centerAchievement].Message;
                                if(achievementManager[centerAchievement].Achieved) textManager[Achievement2].setColor(sf::Color::Green);
                                else textManager[Achievement2].setColor(sf::Color::White);
                                if (centerAchievement < ACHIEVEMENTNUMBER - 2) textManager[Achievement2].setCharacterSize(40);
                                else textManager[Achievement2].setCharacterSize(25);
                                textManager[Achievement2].setString(displayText);
                                Button[Achievement2].setSize(sf::Vector2f(textManager[Achievement2].getLocalBounds().width + 20, textManager[Achievement2].getLocalBounds().height + 20));

                                // Ach 3
                                displayText = achievementManager[centerAchievement + 1].Name + "\n" + achievementManager[centerAchievement + 1].Message;
                                if(achievementManager[centerAchievement + 1].Achieved) textManager[Achievement3].setColor(sf::Color::Green);
                                else textManager[Achievement3].setColor(sf::Color::White);
                                if (centerAchievement == ACHIEVEMENTNUMBER - 2) textManager[Achievement3].setCharacterSize(40);
                                else textManager[Achievement3].setCharacterSize(25);
                                textManager[Achievement3].setString(displayText);
                                Button[Achievement3].setSize(sf::Vector2f(textManager[Achievement3].getLocalBounds().width + 20, textManager[Achievement3].getLocalBounds().height + 20));
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
            if (buttonActive[i]) App.draw(Button[i]);
            App.draw(textManager[i]);
            }

        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }

    return 0;
}

