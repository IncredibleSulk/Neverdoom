#include "includes.hpp"


sf::Text notificationText;
sf::RectangleShape notificationBox;

sf::Font notifyFont;

int notifyTextSize = 20;
int notifyStartXPos = -30;

int notifyYOffset = 10;

sf::Clock notificationTimer;

queue <string> notificationQueue;

bool notifyEnabled = false;

enum NOTIFY_ANIM {
    N_OPENING,
    N_DISPLAYING,
    N_CLOSING
    } NOTIFY_STATE;


bool initNotificationEngine () {
    notifyFont.loadFromFile("Fonts/Olort.ttf");

    notificationText.setColor(sf::Color(0, 0, 0, 200));
    notificationText.setCharacterSize(notifyTextSize);
    notificationText.setFont(notifyFont);
    notificationText.setString("Just to notify you \nthat we are notifying you");

    notificationBox.setFillColor(sf::Color(255, 255, 255, 200));
    notificationBox.setOutlineColor(sf::Color(0, 0, 0, 200));
    notificationBox.setSize(sf::Vector2f(notificationText.getGlobalBounds().width + 20, notificationText.getGlobalBounds().height + 20));
    notificationBox.setOutlineThickness(5);

    return true;
    }


void notify (string Message) {
    if (!notifyEnabled) {
        notifyEnabled = true;
        NOTIFY_STATE = N_OPENING;

        notificationTimer.restart();

        notificationText.setString(Message);
        notificationText.setOrigin(notificationText.getGlobalBounds().width/2, notificationText.getGlobalBounds().height/2);
        notificationText.setPosition((App.getSize().x/2), notifyStartXPos);
        notificationText.setColor(sf::Color(0, 0, 0, 200));
        if (soundEnabled) notificationSound.play();

        notificationBox.setSize(sf::Vector2f(notificationText.getGlobalBounds().width + 20, notificationText.getGlobalBounds().height + 20));
        notificationBox.setOrigin(notificationBox.getGlobalBounds().width/2, notificationBox.getGlobalBounds().height/2);
        notificationBox.setPosition(notificationText.getPosition().x + 3, notificationText.getPosition().y + notifyYOffset);
        notificationBox.setFillColor(sf::Color(255, 255, 255, 200));
        notificationBox.setOutlineColor(sf::Color(0, 0, 0, 200));
        } else {
            notificationQueue.push(Message);
            }
    }


void handleNotifications () {
    if (!notifyEnabled && !notificationQueue.empty()){
        string Message = notificationQueue.front();
        notify(Message);
        notificationQueue.pop();
        }

     if (notifyEnabled && NOTIFY_STATE == NOTIFY_ANIM::N_OPENING && notificationTimer.getElapsedTime().asSeconds() > 0.001) {
        notificationTimer.restart();
        notificationText.move(0, 180 * Framerate);
        notificationBox.setPosition(notificationText.getPosition().x + 3, notificationText.getPosition().y + notifyYOffset);

        if (notificationBox.getPosition().y + notificationBox.getOrigin().y > (0 + notificationBox.getGlobalBounds().height)) NOTIFY_STATE = NOTIFY_ANIM::N_DISPLAYING, notificationTimer.restart();
        }

    if (notifyEnabled && NOTIFY_STATE == NOTIFY_ANIM::N_DISPLAYING && notificationTimer.getElapsedTime().asSeconds() > 2) {
        notificationTimer.restart();
        NOTIFY_STATE = N_CLOSING;
        }

    if (notifyEnabled && NOTIFY_STATE == NOTIFY_ANIM::N_CLOSING && notificationTimer.getElapsedTime().asSeconds() > 0.001) {
        notificationTimer.restart();
        notificationText.move(0, -180 * Framerate);
        notificationBox.setPosition(notificationText.getPosition().x + 3, notificationText.getPosition().y + notifyYOffset);

        if (notificationText.getPosition().y < notifyStartXPos) {
            notifyEnabled = false;
            }
        }


    if (notifyEnabled) App.draw(notificationBox);
    if (notifyEnabled) App.draw(notificationText);
    }
