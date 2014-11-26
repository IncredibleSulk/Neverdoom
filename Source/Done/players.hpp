#include "includes.hpp"

string controlsFile = "Data/Controls.txt";

enum ControlSchemes {
    KeyboardMouse,
    Joystick,
    };

enum Input {
    KeyboardInput,
    MouseInput,
    JoystickMovedPos,
    JoystickMovedNeg,
    JoystickButton,
    };

struct Key {
    int InputType;
    int KeyCode;
    };

//std::map<std::string, Key> Bindings;
Key keys;

int totalPlayers = 0;
int PlayerSpeed = 150;


//TODO Make Weapons
//TODO Individual Weapon Sprites
//TODO Smoke animations - ie for bazooka
//TODO Akimbo
//TODO Enemies
//TODO Waves - Tactical stuff like turrets/traps
//TODO Supply Drops / Powerups
//TODO Powers - import Orbit

struct Player {
    private:
        float CharacterWidth;
        float nameSpacing;
        float healthBarSpacing;

    public:
        int PlayerNumber;

        //TODO Health Regeneration
        int MaxHealth;
        int Health;
        int ControlScheme;

        int HealthBarSize;
        sf::RectangleShape HealthBarRed;
        sf::RectangleShape HealthBarGreen;

        sf::RectangleShape NameOutline;
        sf::Text PlayerName;
        sf::Sprite Sprite;

        //Player Specific Controls
        map<string, Key> Bindings;

        Player () {
            PlayerNumber = totalPlayers;
            Sprite = loadSpriteData("Player " + intToString(PlayerNumber + 1));
            //Get Global width, seperate to rotation
            CharacterWidth = Sprite.getGlobalBounds().width;
            nameSpacing = 30;
            healthBarSpacing = nameSpacing + 15;

            Sprite.setOrigin(Sprite.getGlobalBounds().width/2, Sprite.getGlobalBounds().height/2);
            Sprite.setPosition((App.getSize().x/2) - (Sprite.getGlobalBounds().width/2), (App.getSize().y/2) - (Sprite.getGlobalBounds().height/2));

            //PlayerName.setFont(sf::Font::getDefaultFont());
            PlayerName.setCharacterSize(15);
            PlayerName.setString("Player: " + intToString(PlayerNumber + 1));
            PlayerName.setOrigin(PlayerName.getGlobalBounds().width/2, PlayerName.getGlobalBounds().height/2);
            PlayerName.setPosition(Sprite.getPosition().x, Sprite.getPosition().y + nameSpacing);

            NameOutline.setSize(sf::Vector2f(PlayerName.getGlobalBounds().width, PlayerName.getGlobalBounds().height));
            NameOutline.setOutlineThickness(2);
            NameOutline.setFillColor(sf::Color(0, 0, 0, 120));
            NameOutline.setOutlineColor(sf::Color::Black);
            NameOutline.setOrigin(NameOutline.getGlobalBounds().width/2, NameOutline.getGlobalBounds().height/2);
            NameOutline.setPosition(Sprite.getPosition().x + 1.5, Sprite.getPosition().y + nameSpacing + 4);

            MaxHealth = Health = 100;
            HealthBarSize = 50;

            HealthBarRed.setSize(sf::Vector2f(HealthBarSize, 5));
            HealthBarRed.setOutlineThickness(1);
            HealthBarRed.setFillColor(sf::Color::Red);
            HealthBarRed.setOutlineColor(sf::Color::Black);
            HealthBarRed.setPosition(Sprite.getPosition().x - (CharacterWidth/2) - 5, Sprite.getPosition().y + healthBarSpacing);

            HealthBarGreen.setSize(sf::Vector2f(HealthBarSize, 5));
            HealthBarGreen.setOutlineThickness(1);
            HealthBarGreen.setFillColor(sf::Color::Green);
            HealthBarGreen.setOutlineColor(sf::Color::Black);
            HealthBarGreen.setPosition(Sprite.getPosition().x - (CharacterWidth/2) - 5, Sprite.getPosition().y + healthBarSpacing);

            if (controllerConnected) {
                ControlScheme = ControlSchemes::Joystick;
                Key k;
                k.InputType = Input::JoystickMovedNeg;
                k.KeyCode = sf::Joystick::Axis::Y;
                Bindings["Up"] = k;

                k.InputType = Input::JoystickMovedPos;
                k.KeyCode = sf::Joystick::Axis::Y;
                Bindings["Down"] = k;

                k.InputType = Input::JoystickMovedNeg;
                k.KeyCode = sf::Joystick::Axis::X;
                Bindings["Left"] = k;

                k.InputType = Input::JoystickMovedPos;
                k.KeyCode = sf::Joystick::Axis::X;
                Bindings["Right"] = k;
                } else {
                    ControlScheme = ControlSchemes::KeyboardMouse;
                    Key k;
                    k.InputType = Input::KeyboardInput;
                    k.KeyCode = sf::Keyboard::W;
                    Bindings["Up"] = k;

                    k.InputType = Input::KeyboardInput;
                    k.KeyCode = sf::Keyboard::S;
                    Bindings["Down"] = k;

                    k.InputType = Input::KeyboardInput;
                    k.KeyCode = sf::Keyboard::A;
                    Bindings["Left"] = k;

                    k.InputType = Input::KeyboardInput;
                    k.KeyCode = sf::Keyboard::D;
                    Bindings["Right"] = k;
                    }

            totalPlayers++;
            }

        void rotate () {
            if (ControlScheme == Joystick) {
                float X, Y, X2, Y2, xDif, yDif;
                X = Sprite.getPosition().x;
                Y = Sprite.getPosition().y;
                X2 = X + sf::Joystick::getAxisPosition(PlayerNumber, sf::Joystick::X);
                Y2 = Y + sf::Joystick::getAxisPosition(PlayerNumber, sf::Joystick::Y);

                xDif = X - X2;
                yDif = Y - Y2;

                float R, U, RA, UA, R2, U2, rDif, uDif;
                R = Sprite.getPosition().x;
                U = Sprite.getPosition().y;
                RA = sf::Joystick::getAxisPosition(PlayerNumber, sf::Joystick::R);
                UA = sf::Joystick::getAxisPosition(PlayerNumber, sf::Joystick::U);

                R2 = R + RA;
                U2 = U + UA;

                rDif = R - R2;
                uDif = U - U2;

                double RUAngle = atan2(rDif, uDif);
                RUAngle *= (180/3.1415);
                RUAngle -= 90;

                double angle = atan2(yDif, xDif);
                angle *= (180/3.1415);
                angle -= 90;
                if (RA > 20 || RA < -20 || UA > 20 || UA < -20) Sprite.setRotation(RUAngle);
                else Sprite.setRotation(angle);
                angle -= 90;
                angle *= (3.1415/180);
                } else {
                    float X, Y, X2, Y2, xDif, yDif;
                    X = Sprite.getPosition().x;
                    Y = Sprite.getPosition().y;
                    X2 = sf::Mouse::getPosition(App).x;
                    Y2 = sf::Mouse::getPosition(App).y;

                    xDif = X - X2;
                    yDif = Y - Y2;

                    double angle = atan2(yDif, xDif);
                    angle *= (180/3.1415);
                    angle -= 90;
                    Sprite.setRotation(angle);
                    angle -= 90;
                    angle *= (3.1415/180);
                    }
            }

        void handle () {
            rotate();
            float percentageHealth = float((Health/MaxHealth) * 100);
            HealthBarGreen.setSize(sf::Vector2f(percentageHealth * (HealthBarSize / percentageHealth), 5));

            NameOutline.setPosition(Sprite.getPosition().x + 1.5, Sprite.getPosition().y + nameSpacing + 4);
            PlayerName.setPosition(Sprite.getPosition().x, Sprite.getPosition().y + nameSpacing);
            HealthBarRed.setPosition(Sprite.getPosition().x - (CharacterWidth/2) - 5, Sprite.getPosition().y + healthBarSpacing);
            HealthBarGreen.setPosition(Sprite.getPosition().x - (CharacterWidth/2) - 5, Sprite.getPosition().y + healthBarSpacing);
            }

        void draw () {
            App.draw(Sprite);
            App.draw(NameOutline);
            App.draw(PlayerName);
            App.draw(HealthBarRed);
            App.draw(HealthBarGreen);
            }
    };

vector <Player*> PlayerManager;

//TODO Default Bindings save/load

bool CheckBinding(string Action, int Player) {
    Key k = PlayerManager[Player]->Bindings[Action];

    // Mouse event
//    if (k.InputType == Input::MouseInput && k.EventType == e.type && k.KeyCode == e.mouseButton.button) {
    if (k.InputType == Input::MouseInput) {
        if (sf::Mouse::isButtonPressed((sf::Mouse::Button) k.KeyCode)) return true;
        }

    // Keyboard event
    if (k.InputType == KeyboardInput) {
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)k.KeyCode)) return true;
        }

    // Joystick Button event
    if (k.InputType == JoystickButton) {
        if (sf::Joystick::isButtonPressed(Player, k.KeyCode)) return true;
        }

    // Joystick Axis > 0 event
    if (k.InputType == JoystickMovedPos) {
        if (sf::Joystick::getAxisPosition(Player, (sf::Joystick::Axis)k.KeyCode) > controllerSensitivity) return true;
        }

    // Joystick Axis < 0 event
    if (k.InputType == JoystickMovedNeg) {
        if (sf::Joystick::getAxisPosition(Player, (sf::Joystick::Axis)k.KeyCode) < (-controllerSensitivity)) return true;
        }

    return false;
    }

void getDefaultKeyboardBindings (map<string, Key>& pBindings) {
    Key k;
    k.InputType = Input::KeyboardInput;
    k.KeyCode = sf::Keyboard::W;
    pBindings["Up"] = k;

    k.InputType = Input::KeyboardInput;
    k.KeyCode = sf::Keyboard::S;
    pBindings["Down"] = k;

    k.InputType = Input::KeyboardInput;
    k.KeyCode = sf::Keyboard::A;
    pBindings["Left"] = k;

    k.InputType = Input::KeyboardInput;
    k.KeyCode = sf::Keyboard::D;
    pBindings["Right"] = k;
    }

void getDefaultJoystickBindings (map<string, Key>& pBindings) {
    Key k;
    k.InputType = Input::JoystickMovedNeg;
    k.KeyCode = sf::Joystick::Axis::Y;
    pBindings["Up"] = k;

    k.InputType = Input::JoystickMovedPos;
    k.KeyCode = sf::Joystick::Axis::Y;
    pBindings["Down"] = k;

    k.InputType = Input::JoystickMovedNeg;
    k.KeyCode = sf::Joystick::Axis::X;
    pBindings["Left"] = k;

    k.InputType = Input::JoystickMovedPos;
    k.KeyCode = sf::Joystick::Axis::X;
    pBindings["Right"] = k;
    }

void handlePlayerKeyboard (int ID) {
    if (CheckBinding("Up"       , ID) || CheckBinding("Down"     , ID) || CheckBinding("Right"    , ID) || CheckBinding("Left"     , ID)) {
        if (PlayerManager[ID]->Sprite.getGlobalBounds().top < 0) PlayerManager[ID]->Sprite.move(0, (PlayerSpeed * Framerate));
        if ((PlayerManager[ID]->Sprite.getGlobalBounds().top + PlayerManager[ID]->Sprite.getGlobalBounds().height) > App.getSize().y) PlayerManager[ID]->Sprite.move(0, -(PlayerSpeed * Framerate));
        if (PlayerManager[ID]->Sprite.getGlobalBounds().left < 0) PlayerManager[ID]->Sprite.move((PlayerSpeed * Framerate), 0);
        if ((PlayerManager[ID]->Sprite.getGlobalBounds().left + PlayerManager[ID]->Sprite.getGlobalBounds().width) > App.getSize().x) PlayerManager[ID]->Sprite.move(-(PlayerSpeed * Framerate), 0);

        // If Not out of Bounds, Move
        if (CheckBinding("Up"       , ID) &&  (PlayerManager[ID]->Sprite.getGlobalBounds().top > 0)) PlayerManager[ID]->Sprite.move(0, -(PlayerSpeed * Framerate));
        if (CheckBinding("Down"     , ID) && ((PlayerManager[ID]->Sprite.getGlobalBounds().top + PlayerManager[ID]->Sprite.getGlobalBounds().height) < App.getSize().y)) PlayerManager[ID]->Sprite.move(0, (PlayerSpeed * Framerate));
        if (CheckBinding("Left"     , ID) &&  (PlayerManager[ID]->Sprite.getGlobalBounds().left > 0)) PlayerManager[ID]->Sprite.move(-(PlayerSpeed * Framerate), 0);
        if (CheckBinding("Right"    , ID) && ((PlayerManager[ID]->Sprite.getGlobalBounds().left + PlayerManager[ID]->Sprite.getGlobalBounds().width) < App.getSize().x)) PlayerManager[ID]->Sprite.move((PlayerSpeed * Framerate), 0);
        }
    }

void handlePlayerJoystick (int ID) {
    if (CheckBinding("Up"       , ID) || CheckBinding("Down"     , ID) || CheckBinding("Right"    , ID) || CheckBinding("Left"     , ID)) {
        float X, Y, X2, Y2, xDif, yDif;
        X = PlayerManager[ID]->Sprite.getPosition().x;
        Y = PlayerManager[ID]->Sprite.getPosition().y;

        X2 = X + sf::Joystick::getAxisPosition(ID, (sf::Joystick::Axis)PlayerManager[ID]->Bindings["Left"].KeyCode);
        Y2 = Y + sf::Joystick::getAxisPosition(ID, (sf::Joystick::Axis)PlayerManager[ID]->Bindings["Up"].KeyCode);

        xDif = X - X2;
        yDif = Y - Y2;

        double angle = atan2(yDif, xDif);
        angle *= (180/3.1415);
        angle -= 180;
        angle *= (3.1415/180);

        sf::FloatRect Boundary (0, 0, App.getSize().x, App.getSize().y);
        float newX, newY;
        newX = X + (cos(angle) * (PlayerSpeed * Framerate));
        newY = Y + (sin(angle) * (PlayerSpeed * Framerate));

        if (Boundary.contains(newX, newY)) PlayerManager[ID]->Sprite.setPosition(newX, newY);
        }
    }
