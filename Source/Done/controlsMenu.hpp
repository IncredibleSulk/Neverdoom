#include "includes.hpp"

int controlChange (int PlayerID, string Keybind) {
    string KKeyNames [] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", "BackSlash",                    "Tilde", "Equal", "Dash", "Space", "Return", "Back", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down",                    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15"};
    string MKeyNames [] = {"Left", "Right", "Middle", "XButton1", "XButton2"};
    string JAxisNames [] = {"X", "Y", "Z", "R", "U", "V", "PovX", "PovY"};

     enum buttonNames {
        Title,

        AssignButton,
        BindingButton,

        ButtonNumber
        };

    sf::Text *textManager;
    sf::RectangleShape *Button;
    bool *buttonActive;

    textManager = new sf::Text [ButtonNumber];
    Button = new sf::RectangleShape[ButtonNumber];
    buttonActive = new bool [ButtonNumber];

    int textYPosition = fontYDefault;

    sf::Clock controllerMenuTimer;
    sf::Clock flashTimer;

    for (int i = 0; i < buttonNames::ButtonNumber; i++) {
        buttonActive[i] = false;
        textManager[i].setFont(Font);
        textManager[i].setCharacterSize(fontSize);
        textManager[i].setPosition(150, textYPosition);

        switch (i) {
            case buttonNames::Title:
            textManager[i].setColor(sf::Color(220, 20, 60));
            textManager[i].setString("Controls");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding + 20;
            break;

            case buttonNames::AssignButton:
            textManager[i].setString("Action : " + Keybind);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textManager[i].setCharacterSize(60);
            textYPosition += 50;
            break;

            case buttonNames::BindingButton:
            textManager[i].setString("Key : ");
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textManager[i].setColor(sf::Color::Red);
            textManager[i].setCharacterSize(50);
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

            if (Event.type == Event.MouseMoved) {
                cursor.setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                cursorActive = true;
                }

            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) {
                return 0;
                }

            if (Event.type == Event.MouseButtonPressed) {
                PlayerManager[PlayerID]->Bindings[Keybind].InputType = Input::MouseInput;
                PlayerManager[PlayerID]->Bindings[Keybind].KeyCode = Event.mouseButton.button;
                return 0;
                }

            if (Event.type == Event.KeyPressed) {
                PlayerManager[PlayerID]->Bindings[Keybind].InputType = Input::KeyboardInput;
                PlayerManager[PlayerID]->Bindings[Keybind].KeyCode = Event.key.code;
                return 0;
                }

            if (Event.type == Event.JoystickButtonPressed) {
                PlayerManager[PlayerID]->Bindings[Keybind].InputType = Input::JoystickButton;
                PlayerManager[PlayerID]->Bindings[Keybind].KeyCode = Event.joystickButton.button;
                return 0;
                }

            if (Event.type == Event.JoystickMoved) {
                if (Event.joystickMove.position >  20) PlayerManager[PlayerID]->Bindings[Keybind].InputType = Input::JoystickMovedPos;
                if (Event.joystickMove.position < -20) PlayerManager[PlayerID]->Bindings[Keybind].InputType = Input::JoystickMovedNeg;
                PlayerManager[PlayerID]->Bindings[Keybind].KeyCode = Event.joystickMove.axis;
                return 0;
                }
            }


        if (true) {
            Player P = *PlayerManager[PlayerID];
            string keyName;

            if (P.Bindings[Keybind].InputType == Input::KeyboardInput) keyName = KKeyNames[P.Bindings[Keybind].KeyCode];
            else if (P.Bindings[Keybind].InputType == Input::MouseInput) keyName = "MButton " + MKeyNames[P.Bindings["Keybind"].KeyCode];
            else if (P.Bindings[Keybind].InputType == Input::JoystickButton) keyName = "Joystick Button " + intToString(P.Bindings[Keybind].KeyCode);
            else if (P.Bindings[Keybind].InputType == Input::JoystickMovedPos || P.Bindings[Keybind].InputType == Input::JoystickMovedNeg) keyName = "Joystick Axis " + JAxisNames[P.Bindings[Keybind].KeyCode];

            textManager[buttonNames::BindingButton].setString("Key : " + keyName);
            textManager[buttonNames::BindingButton].setPosition((App.getSize().x/2 - textManager[buttonNames::BindingButton].getGlobalBounds().width/2), textYPosition);
            Button[buttonNames::BindingButton].setSize(sf::Vector2f(textManager[buttonNames::BindingButton].getLocalBounds().width + 20, textManager[buttonNames::BindingButton].getLocalBounds().height + 20));
            }


        if (menuTimer.getElapsedTime().asSeconds() > 0.1) menuEntered = false;
        App.clear();
        App.draw(background);

        for (int i = 0; i < buttonNames::ButtonNumber; i++) {
            if (buttonActive[i]) App.draw(Button[i]);

            if (i == buttonNames::BindingButton && flashTimer.getElapsedTime().asSeconds() < 0.4) App.draw(textManager[i]);
            else if (i == buttonNames::BindingButton && flashTimer.getElapsedTime().asSeconds() > 0.8) flashTimer.restart();
            else if (i != buttonNames::BindingButton) App.draw(textManager[i]);
            }

        if (cursorActive) App.draw(cursor);
        App.draw(framerateDisplay);
        App.display();
        updateFramerate();
        }

    return 0;
    }


int controlsMenu (int PlayerID) {
    string controlSchemeNames [] = {"Keyboard and Mouse", "Controller"};
    string KKeyNames [] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", "BackSlash",                    "Tilde", "Equal", "Dash", "Space", "Return", "Back", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down",                    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15"};
    string MKeyNames [] = {"Left", "Right", "Middle", "XButton1", "XButton2"};
    string JAxisNames [] = {"X", "Y", "Z", "R", "U", "V", "PovX", "PovY"};

    enum buttonNames {
        Title,

        ControlScheme,
        Up,
        Down,
        Left,
        Right,
        Reset,

        Back,

        ButtonNumber
        };

    sf::Text *textManager;
    sf::RectangleShape *Button;
    bool *buttonActive;

    textManager = new sf::Text [ButtonNumber];
    Button = new sf::RectangleShape[ButtonNumber];
    buttonActive = new bool [ButtonNumber];

    int textYPosition = fontYDefault;

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
            textManager[i].setString("P" + intToString(PlayerID + 1) + "'s Controls");
            textManager[i].setCharacterSize(headerFontSize);
            textManager[i].setPosition((App.getSize().x/2 - textManager[i].getGlobalBounds().width/2), textYPosition);
            textYPosition += headerPadding;
            break;

            case buttonNames::ControlScheme:
            textManager[i].setString("Input : " + controlSchemeNames[PlayerManager[PlayerID]->ControlScheme]);
            textManager[i].setPosition(150, textYPosition);
            textManager[i].setCharacterSize(45);
            break;

            case buttonNames::Up:
            textManager[i].setString("Up : ");
            textManager[i].setPosition(150, textYPosition);
            textManager[i].setCharacterSize(45);
            break;

            case buttonNames::Down:
            textManager[i].setString("Down : ");
            textManager[i].setPosition(150, textYPosition);
            textManager[i].setCharacterSize(45);
            break;

            case buttonNames::Left:
            textManager[i].setString("Left : ");
            textManager[i].setPosition(150, textYPosition);
            textManager[i].setCharacterSize(45);
            break;

            case buttonNames::Right:
            textManager[i].setString("Right : ");
            textManager[i].setPosition(150, textYPosition);
            textManager[i].setCharacterSize(45);
            break;

            case buttonNames::Reset:
            textManager[i].setString("Reset");
            textManager[i].setPosition(612, 518);
            break;

            case buttonNames::Back:
            textManager[i].setString("Back");
            textManager[i].setColor(sf::Color(255, 255, 255));
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
                menuEntered = true;
                menuTimer.restart();
                if (soundEnabled) buttonSound.play();
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
                        if (controllerMenuItem > buttonNames::Back) controllerMenuItem = buttonNames::ControlScheme;
                        }
                    if (Event.joystickMove.position < 0) {
                        controllerMenuItem--;
                        if (controllerMenuItem < buttonNames::ControlScheme) controllerMenuItem = buttonNames::Back;
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

                            menuEntered = true;
                            menuTimer.restart();
                            if (textManager[i].getGlobalBounds().contains(X, Y)) buttonActive[i] = false, textManager[i].setColor(sf::Color(255, 255, 255));
                            switch (i) {
                                case buttonNames::ControlScheme:
                                if (PlayerManager[PlayerID]->ControlScheme == ControlSchemes::Joystick) {
                                    PlayerManager[PlayerID]->ControlScheme = ControlSchemes::KeyboardMouse;
                                    getDefaultKeyboardBindings(PlayerManager[PlayerID]->Bindings);
                                    } else if (controllerConnected) {
                                        PlayerManager[PlayerID]->ControlScheme = ControlSchemes::Joystick;
                                        getDefaultJoystickBindings(PlayerManager[PlayerID]->Bindings);
                                        }
                                break;

                                case buttonNames::Reset:
                                if (PlayerManager[PlayerID]->ControlScheme == ControlSchemes::Joystick) {
                                    getDefaultJoystickBindings(PlayerManager[PlayerID]->Bindings);
                                    } else if (controllerConnected) {
                                        getDefaultKeyboardBindings(PlayerManager[PlayerID]->Bindings);
                                        }
                                break;

                                case Up:
                                controlChange(0, "Up");
                                break;

                                case Down:
                                controlChange(0, "Down");
                                break;

                                case Left:
                                controlChange(0, "Left");
                                break;

                                case Right:
                                controlChange(0, "Right");
                                break;

                                case buttonNames::Back:
                                return 0;
                                break;
                                }
                            }
                        }
                }
            }


        if (true) {
            Player P = *PlayerManager[PlayerID];
            string keyName;

            textManager[buttonNames::ControlScheme].setString("Input : " + controlSchemeNames[P.ControlScheme]);
            Button[buttonNames::ControlScheme].setSize(sf::Vector2f(textManager[buttonNames::ControlScheme].getLocalBounds().width + 20, textManager[buttonNames::ControlScheme].getLocalBounds().height + 20));

            if (P.Bindings["Up"].InputType == Input::KeyboardInput) keyName = KKeyNames[P.Bindings["Up"].KeyCode];
            else if (P.Bindings["Up"].InputType == Input::MouseInput) keyName = "MButton " + MKeyNames[P.Bindings["Up"].KeyCode];
            else if (P.Bindings["Up"].InputType == Input::JoystickButton) keyName = "Joystick Button " + intToString(P.Bindings["Up"].KeyCode);
            else if (P.Bindings["Up"].InputType == Input::JoystickMovedPos || P.Bindings["Up"].InputType == Input::JoystickMovedNeg) keyName = "Joystick Axis " + JAxisNames[P.Bindings["Up"].KeyCode];
            textManager[buttonNames::Up].setString("Up : " + keyName);

            if (P.Bindings["Down"].InputType == Input::KeyboardInput) keyName = KKeyNames[P.Bindings["Down"].KeyCode];
            else if (P.Bindings["Down"].InputType == Input::MouseInput) keyName = "MButton " + MKeyNames[P.Bindings["Down"].KeyCode];
            else if (P.Bindings["Down"].InputType == Input::JoystickButton) keyName = "Joystick Button " + intToString(P.Bindings["Down"].KeyCode);
            else if (P.Bindings["Down"].InputType == Input::JoystickMovedPos || P.Bindings["Down"].InputType == Input::JoystickMovedNeg) keyName = "Joystick Axis " + JAxisNames[P.Bindings["Down"].KeyCode];
            textManager[buttonNames::Down].setString("Down : " + keyName);

            if (P.Bindings["Left"].InputType == Input::KeyboardInput) keyName = KKeyNames[P.Bindings["Left"].KeyCode];
            else if (P.Bindings["Left"].InputType == Input::MouseInput) keyName = "MButton " + MKeyNames[P.Bindings["Left"].KeyCode];
            else if (P.Bindings["Left"].InputType == Input::JoystickButton) keyName = "Joystick Button " + intToString(P.Bindings["Left"].KeyCode);
            else if (P.Bindings["Left"].InputType == Input::JoystickMovedPos || P.Bindings["Left"].InputType == Input::JoystickMovedNeg) keyName = "Joystick Axis " + JAxisNames[P.Bindings["Left"].KeyCode];
            textManager[buttonNames::Left].setString("Left : " + keyName);

            if (P.Bindings["Right"].InputType == Input::KeyboardInput) keyName = KKeyNames[P.Bindings["Right"].KeyCode];
            else if (P.Bindings["Right"].InputType == Input::MouseInput) keyName = "MButton " + MKeyNames[P.Bindings["Right"].KeyCode];
            else if (P.Bindings["Right"].InputType == Input::JoystickButton) keyName = "Joystick Button " + intToString(P.Bindings["Right"].KeyCode);
            else if (P.Bindings["Right"].InputType == Input::JoystickMovedPos || P.Bindings["Right"].InputType == Input::JoystickMovedNeg) keyName = "Joystick Axis " + JAxisNames[P.Bindings["Right"].KeyCode];
            textManager[buttonNames::Right].setString("Right : " + keyName);

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
