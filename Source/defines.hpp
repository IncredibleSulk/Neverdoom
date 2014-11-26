#include "includes.hpp"

string GAMENAME = "Neverdoom";

sf::RenderWindow App;
sf::VideoMode VideoMode (800, 600, 32);
sf::Event Event;

sf::Clock framerateTimer;
sf::Clock menuTimer;
sf::Text framerateDisplay;

sf::Font Font;
int headerFontSize = 80;
int headerPadding = 40;
int fontSize = 65;
int fontPadding = 70;

int fontYDefault = 10;

sf::Texture Spritesheet;
sf::Texture backgroundTexture;
sf::Sprite cursor;
sf::Sprite background;
int backgroundNumber;

double Framerate;
double gameSpeed;
double Volume;

int score;
int previousScore;

bool gamePlaying = false;
bool gameQuit = false;
bool menuEntered = false;

double controllerSensitivity = 45;
double controllerMenuTimeout = 0.2;
bool controllerConnected = false;
bool cursorActive = true;
vector <int> activeControllers;

bool fullscreenEnabled;
bool soundEnabled;

sf::SoundBuffer notificationBuffer;
sf::SoundBuffer connectedBuffer;
sf::SoundBuffer disconnectedBuffer;
sf::SoundBuffer buttonBuffer;
sf::SoundBuffer laserBuffer;

sf::Sound notificationSound;
sf::Sound connectedSound;
sf::Sound disconnectedSound;
sf::Sound buttonSound;
sf::Sound laserSound;
