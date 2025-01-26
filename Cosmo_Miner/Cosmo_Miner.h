// Cosmo_Miner.h: plik dołączany dla standardowych systemowych plików dołączanych,
// lub pliki dołączane specyficzne dla projektu.

#pragma once

#include <iostream>

#ifndef COSMO_MINER_H
#define COSMO_MINER_H

#include "raylib.h"
#include <vector>

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
    uint8_t invTime{};
    Color tint{};

    void movement();
    void takeDMG();
    void changeColor();
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

// Funkcja główna gry
void Game();

#endif // COSMO_MINER_H

