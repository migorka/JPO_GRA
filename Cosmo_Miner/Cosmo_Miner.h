// Cosmo_Miner.h: plik dołączany dla standardowych systemowych plików dołączanych,
// lub pliki dołączane specyficzne dla projektu.

#pragma once

#include "raylib.h"
#include <vector>
#include <random>

extern const float scrWidth;
extern const float scrHeight;

extern int screen;

class Player
{
public:
    Vector2 pos{};
    Vector2 speed{};
    float rot{};
    int points{};
    bool alive{};
    int HP{};

    void movement();
    void takeDMG();
    void reset();
};

class Laser
{
public:
    Vector2 pos{};
    Vector2 speed{};
    bool active{};

    Laser(Vector2 playerPos, float speedX, float speedY, bool T);
    ~Laser();
    void movement();
};

class Asteroid
{
public:
    Vector2 pos{};
    Vector2 speed{};
    bool active{};
    int size{};

    Asteroid(Vector2 startingPos, float speedX, float speedY, bool activeConstr, int sizeConstr);
    ~Asteroid();
    void movement();
};

class Game
{
public:
    Texture2D texPlayer{};
    Texture2D texPlayerThru{};
    Texture2D texBackground{};
    Texture2D texHeart{};

    Sound fxLaser{};
    Sound fxExplosion{};

    Music music{};


    Player player;
    std::vector<Laser> lasers;
    std::vector<Asteroid> asteroids;

    double deltaTime{};
    float asteroidCurrentCD{};

    Vector2 startingPos();
    void laserUpdate();
    void shootLaser();       
    void asteroidGen();      
    void asteroidCollisions();
    void reset();             
    void run();               
};