#include "includes.hpp"

void initialise() {
    loadSettings();
    if (fullscreenEnabled) App.create(VideoMode, GAMENAME, sf::Style::Fullscreen);
    else App.create(VideoMode, GAMENAME);

    App.setFramerateLimit(60);
    App.setVerticalSyncEnabled(true);
    App.setJoystickThreshold(18);

    cursor = loadSpriteData("Cursor");
    App.setMouseCursorVisible(false);
    setBackground();

    Font.loadFromFile("Fonts/MAKISUPA.ttf");

    notificationBuffer.loadFromFile("Audio/notify.wav");
    connectedBuffer.loadFromFile("Audio/connected.wav");
    disconnectedBuffer.loadFromFile("Audio/disconnected.wav");
    buttonBuffer.loadFromFile("Audio/button.wav");
    laserBuffer.loadFromFile("Audio/laser.wav");

    notificationSound.setBuffer(notificationBuffer);
    connectedSound.setBuffer(connectedBuffer);
    disconnectedSound.setBuffer(disconnectedBuffer);
    buttonSound.setBuffer(buttonBuffer);
    laserSound.setBuffer(laserBuffer);

    framerateDisplay.setColor(sf::Color::Red);
    framerateDisplay.setCharacterSize(18);

    initAchievements();
    initNotificationEngine();

    activeControllers.clear();
    for (int i = 0; i < sf::Joystick::Count; i++) {
        if (sf::Joystick::isConnected(i)) {
            controllerConnected = true; cursorActive = false;
            cursorActive = false;
            connectedSound.play();
            activeControllers.push_back(i);
            }
        }
    PlayerManager.push_back(new Player);
    loadStatistics();
    loadSpritesheet();
    loadScores();
    }

void saveAndQuit () {
    saveSettings();
    saveStatistics();
    saveAchievements();
    saveScores();
    App.close();
    };

void drawStaticObjects () {
    for (vector<Player*>::iterator i = PlayerManager.begin(); i != PlayerManager.end(); i++) {
            (*i)->handle(), drawHitbox((*i)->Sprite), (*i)->draw();
            }
    }

void checkGlobalEvents () {
    if (Event.type == Event.Closed) saveAndQuit();

    if (Event.type == Event.JoystickConnected && !controllerConnected) {
        connectedSound.play();
        controllerConnected = true;
        cursorActive = false;
        activeControllers.clear();
        for (int i = 0; i < sf::Joystick::Count; i++) {
            if (sf::Joystick::isConnected(i)) {
                activeControllers.push_back(i);
                }
            }
        }

    if (Event.type == Event.JoystickDisconnected) {
        disconnectedSound.play();
        activeControllers.clear();
        for (int i = 0; i < sf::Joystick::Count; i++) {
            if (sf::Joystick::isConnected(i)) {
                activeControllers.push_back(i);
                }
            }
        if (activeControllers.size() < 1) controllerConnected = false, cursorActive = true;
        }

    if (controllerConnected && (Event.type == Event.JoystickMoved || Event.type == Event.JoystickButtonPressed) && !gamePlaying) sf::Mouse::setPosition(App.getPosition());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

        }

    }
