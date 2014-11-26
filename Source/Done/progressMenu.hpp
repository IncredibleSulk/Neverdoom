#include "includes.hpp"


int progressMenu() {
    enum buttonNames {
        Title,
        ResetHighscores,
        ResetAchievements,
        RestoreDefaults,
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
            textManager[i].setString("Restore Menu");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::ResetHighscores:
            textManager[i].setString("Reset Highscores");
            break;

            case buttonNames::ResetAchievements:
            textManager[i].setString("Reset Achievements");
            break;

            case buttonNames::RestoreDefaults:
            textManager[i].setString("Restore Defaults");
            break;

            case buttonNames::Back:
            textManager[i].setString("Back");
            textManager[i].setPosition(15, 518);
            break;
            }
        Button[i].setSize(sf::Vector2f(textManager[i].getLocalBounds().width + 20, textManager[i].getLocalBounds().height + 20));
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
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::ResetHighscores;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::ResetHighscores) controllerMenuItem = buttonNames::Back;
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
                        if (soundEnabled) buttonSound.play();
                        menuEntered = true;
                        menuTimer.restart();
                        if (textManager[i].getGlobalBounds().contains(X, Y)) buttonActive[i] = false, textManager[i].setColor(sf::Color(255, 255, 255));
                        switch (i) {

                            case buttonNames::ResetHighscores:
                            remove(HIGHSCORE_FILE);
                            highscoreTable.clear();
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
                            sortScores();
                            break;

                            case buttonNames::ResetAchievements:
                            remove(ACHIEVEMENT_FILE);
                            for (int a = 0; a < ACHIEVEMENTNUMBER; a++) achievementManager[a].Achieved = false;
                            break;

                            case buttonNames::RestoreDefaults:
                            fullscreenEnabled = false;
                            soundEnabled = true;
                            Volume = 100;
                            setGlobalVolume();
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

