#include "includes.hpp"

void initialise ();
void saveAndQuit ();
void drawStaticObjects ();
void checkGlobalEvents ();

void updateFramerate () {
    Framerate = framerateTimer.restart().asSeconds();

    stringstream s;
    s.str("");
    s << 1.0 / Framerate << " FPS";
    framerateDisplay.setString(s.str());
    framerateDisplay.setPosition(App.getSize().x - (framerateDisplay.getGlobalBounds().width + 10), 10);
    }

//TODO Add all sounds to Volumed Control
void setGlobalVolume () {
    notificationSound.setVolume(Volume);
    connectedSound.setVolume(Volume);
    disconnectedSound.setVolume(Volume);
    buttonSound.setVolume(Volume);
    laserSound.setVolume(Volume);
    }

void drawHitbox (sf::Sprite &Sprite) {
    sf::RectangleShape Hitbox;
    Hitbox.setSize(sf::Vector2f(Sprite.getLocalBounds().width, Sprite.getLocalBounds().height));
    Hitbox.setOutlineThickness(2);
    Hitbox.setFillColor(sf::Color::Transparent);
    Hitbox.setOutlineColor(sf::Color::Red);
    Hitbox.setOrigin(Hitbox.getGlobalBounds().width/2, Hitbox.getGlobalBounds().height/2);
    Hitbox.setRotation(Sprite.getRotation());
    Hitbox.setPosition(Sprite.getPosition());
    App.draw(Hitbox);
    }

