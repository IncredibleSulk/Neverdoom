#include "includes.hpp"

int reconnectController () {

    sf::Text Text;
    Text.setFont(Font);
    Text.setCharacterSize(fontSize / 2);
    Text.setColor(sf::Color::Red);
    Text.setString("Controller Disconnected!\nPlease Reconnect \nyour controller");
    Text.setPosition((App.getSize().x/2 - Text.getGlobalBounds().width/2), (App.getSize().y/2 - Text.getGlobalBounds().height/2));

    while (App.isOpen()) {
        while (App.pollEvent(Event)) {

            checkGlobalEvents();

            if (Event.type == Event.JoystickConnected)  return 0;

            if (Event.type == Event.MouseMoved)  {
                float X = sf::Mouse::getPosition(App).x;
                float Y = sf::Mouse::getPosition(App).y;

                cursor.setPosition(X, Y);
                cursorActive = true;
                }

            // App doesn't close until next loop logic, unless we break it here
            if (!App.isOpen()) return 0;
            }

        App.clear();
        App.draw(background);
        drawStaticObjects();
        App.draw(Text);
        App.draw(framerateDisplay);
        if (cursorActive) App.draw(cursor);
        App.display();
        updateFramerate();
        }
    return 0;
    }
