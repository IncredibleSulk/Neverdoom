#include "includes.hpp"


int game () {
    for (unsigned i = 1; i < activeControllers.size(); i++) {
        PlayerManager.push_back(new Player);
        PlayerManager.back()->Sprite.setPosition(i * 50, 200);
        }
    while (App.isOpen()) {
        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (controllerConnected && Event.type == Event.JoystickButtonPressed) {
                switch (Event.joystickButton.button) {
                    case 0:
                    break;

                    case 7:
                    pauseMenu();
                    break;

                    }
                }

            if (Event.type == Event.JoystickDisconnected) {
                reconnectController();
                }

            if (controllerConnected && Event.type == Event.JoystickMoved) {

                }

            if (Event.type == Event.MouseMoved) {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;
                cursor.setPosition(X, Y);
                cursorActive = true;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
                pauseMenu();
                }
            }

        for (vector<Player*>::iterator i = PlayerManager.begin(); i != PlayerManager.end(); i++) {
            int ID = (*i)->PlayerNumber;
            if ((*i)->ControlScheme == ControlSchemes::Joystick) {
                handlePlayerJoystick(ID);
                } else {
                    handlePlayerKeyboard(ID);
                    }
            }

        if (gameQuit || !gamePlaying) {
            return 0;
            }

        App.clear();
        App.draw(background);

        for (vector<Player*>::iterator i = PlayerManager.begin(); i != PlayerManager.end(); i++) {
            (*i)->handle(), drawHitbox((*i)->Sprite), (*i)->draw();
            }

        handleNotifications();
        App.draw(framerateDisplay);
        drawHitbox(cursor);
        App.draw(cursor);
        App.display();
        updateFramerate();
        }
    return 0;
    }
