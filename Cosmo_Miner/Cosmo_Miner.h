// Cosmo_Miner.h: plik dołączany dla standardowych systemowych plików dołączanych,
// lub pliki dołączane specyficzne dla projektu.

#pragma once

#include <iostream>
#include "raylib.h"
#include <vector>
#include <random>

// Stałe rozmiarów ekranu
extern const float scrWidth;
extern const float scrHeight;

// Globalna zmienna do zmiany ekranu gry
extern int screen;

// Klasa reprezentująca gracza
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

// Klasa reprezentująca laser
class Laser
{
public:
    Vector2 pos;
    Vector2 speed;
    bool active;

    Laser(Vector2 playerPos, float speedX, float speedY, bool T);
    ~Laser();
    void movement();
};

// Klasa reprezentująca asteroidę
class Asteroid
{
public:
    Vector2 pos;
    Vector2 speed;
    bool active;
    int size;

    Asteroid(Vector2 startingPos, float speedX, float speedY, bool activeConstr, int sizeConstr);
    ~Asteroid();
    void movement();
};

// Funkcja generująca pozycję początkową
Vector2 startingPos();

class Game
{
public:
    Texture2D texPlayer;
    Texture2D texPlayerThru;
    Texture2D texBackground;
    Texture2D texHeart;

    Sound fxLaser;
    Sound fxExplosion;

    Music music;


    Player player;
    std::vector<Laser> lasers;
    std::vector<Asteroid> asteroids;

    double deltaTime;
    float asteroidCurrentCD;

    void loadRSC();
    void laserUpdate();       // Aktualizacja stanu laserów
    void shootLaser();        // Wystrzeliwanie laserów
    void asteroidGen();       // Generowanie asteroid
    void asteroidCollisions();// Obsługa kolizji asteroid
    void reset();             // Reset gry

    void run();               // Uruchomienie gry
};