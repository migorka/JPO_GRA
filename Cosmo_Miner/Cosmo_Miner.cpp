// Cosmo_Miner.cpp: definiuje punkt wejścia dla aplikacji.
//


#include "Cosmo_Miner.h"
#include "raylib.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>

// Ustawienie zmiennych rozmiaru okna
const float scrWidth{ 1920 };
const float scrHeight{ 1080 };

int screen = 1;

float getLength(Vector2 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

class Player
{
public:
	Vector2 pos{};
	Vector2 speed{};
	float rot{};
	int points{};
	bool alive{};
	int HP{};

	void movement()
	{
		//Przenoszenie gracza na przeciwległą krawędź ekranu
		if (pos.x < 0)
			pos.x = scrWidth;
		if (pos.x > scrWidth)
			pos.x = 0;
		if (pos.y < 0)
			pos.y = scrHeight;
		if (pos.y > scrHeight)
			pos.y = 0;

		//Obrót w lewo
		if (IsKeyDown(KEY_A))
			rot -= 5;
		//Obrót w prawo
		if (IsKeyDown(KEY_D))
			rot += 5;
		if (IsKeyDown(KEY_W))
		{
			//Obliczanie wektora ruchu na bazie kąta obrotu gracza
			speed.x += cos((rot - 90) * PI / 180) * 0.2;
			speed.y += sin((rot - 90) * PI / 180) * 0.2;
		}
		//Zmiana pozycji gracza o jego prędkość
		pos.x += speed.x;
		pos.y += speed.y;
	}

	void takeDMG()
	{
		HP -= 1;
		if (HP <= 0)
		{
			alive = 0;
			screen = 2;
		}
	}
};

class Laser
{
public:
	Vector2 pos;
	Vector2 speed;
	bool active;

	Laser(Vector2 playerPos, float speedX, float speedY, bool T)
	{
		pos = playerPos;
		speed = { speedX, speedY };
		active = T;
	}

	~Laser()
	{

	}

	void movement()
	{
		pos.x += speed.x;
		pos.y += speed.y;
	}
};

class Asteroid
{
public:
	Vector2 pos;
	Vector2 speed;
	bool active;
	int size;

	Asteroid(Vector2 startingPos, float speedX, float speedY, bool activeConstr, int sizeConstr)
	{
		pos = startingPos;
		speed = { speedX, speedY };
		active = activeConstr;
		size = sizeConstr;
	}

	~Asteroid()
	{

	}

	void movement()
	{
		if (pos.x < 0)
			pos.x = scrWidth;
		if (pos.x > scrWidth)
			pos.x = 0;
		if (pos.y < 0)
			pos.y = scrHeight;
		if (pos.y > scrHeight)
			pos.y = 0;

		pos.x += speed.x;
		pos.y += speed.y;
	}
};

Vector2 startingPos()
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> wallGen(1, 4);
	std::uniform_int_distribution<> widthGen(0, 1920);
	std::uniform_int_distribution<> heightGen(0, 1080);

	int wall = wallGen(gen);

	if (wall == 1)
		return { 0, (float)heightGen(gen) };
	if (wall == 2)
		return { scrWidth, (float)heightGen(gen) };
	if (wall == 3)
		return { (float)widthGen(gen), 0 };
	if (wall == 4)
		return { (float)widthGen(gen), scrHeight };
}

void Game()
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> asteroidNumberGen(2, 5);
	std::uniform_int_distribution<> asteroidNewCDGen(3, 10);
	std::uniform_int_distribution<> asteroidRotGen(0, 360);
	std::uniform_int_distribution<> asteroidSizeGen(1, 3);

	InitWindow(scrWidth, scrHeight, "Cosmo Miner");
	SetTargetFPS(60);

	Texture2D texPlayer = LoadTexture("rsc/Main Ship - Base - Full health.png");
	Texture2D texPlayerThru = LoadTexture("rsc/Main Ship - Base - Thruster.png");
	Texture2D texBackground = LoadTexture("rsc/background.png");
	Texture2D texHeart = LoadTexture("rsc/heart.png");

	Player player;
	player.rot = 0;
	player.pos = { scrWidth / 2, scrHeight / 2 };
	player.points = 0;
	player.alive = true;
	player.HP = 3;

	std::vector<Laser> lasers;
	std::vector<Asteroid> asteroids;

	float asteroidCurrentCD{ 3 };

	while (!WindowShouldClose())
	{
		double deltaTime = GetFrameTime();
		player.movement();

		for (auto& laser : lasers)
		{
			if (laser.pos.x < 0 || laser.pos.x > scrWidth || laser.pos.y < 0 || laser.pos.y > scrHeight)
			{
				laser.active = false;
				laser.~Laser();
			}

			if (laser.active)
				laser.movement();
		}

		//Strzelanie
		if (IsKeyPressed(KEY_SPACE))
		{
			float speedX = cos((player.rot - 90) * PI / 180) * 10;
			float speedY = sin((player.rot - 90) * PI / 180) * 10;
			lasers.emplace_back(player.pos, speedX, speedY, true);
		}

		//Generowanie nowych asteroid
		asteroidCurrentCD -= deltaTime;
		if (asteroidCurrentCD <= 0)
		{
			for (int i = 0; i < asteroidNumberGen(gen); i++)
			{
				float speedX = cos((asteroidRotGen(gen) - 90) * PI / 180) * 2;
				float speedY = sin((asteroidRotGen(gen) - 90) * PI / 180) * 2;
				asteroids.emplace_back(startingPos(), speedX, speedY, true, asteroidSizeGen(gen));
			}
			asteroidCurrentCD = asteroidNewCDGen(gen);
		}

		//RUCH I SPRAWDZANIE KOLIZJI ASTEROID
		for (auto& asteroid : asteroids)
		{
			if (asteroid.active)
			{
				asteroid.movement();

				if (asteroid.size == 1 && CheckCollisionCircles(asteroid.pos, 20, player.pos, 20))
				{
					player.takeDMG();
					asteroid.active = false;
					asteroid.~Asteroid();
				}

				if (asteroid.size == 2 && CheckCollisionCircles(asteroid.pos, 50, player.pos, 20))
				{
					player.takeDMG();
					asteroid.active = false;
					asteroid.~Asteroid();
				}

				if (asteroid.size == 3 && CheckCollisionCircles(asteroid.pos, 100, player.pos, 20))
				{
					player.takeDMG();
					asteroid.active = false;
					asteroid.~Asteroid();
				}

				for (auto& laser : lasers)
				{
					if (laser.active)
					{
						if (asteroid.size == 1)
						{
							if (CheckCollisionCircles(asteroid.pos, 20, laser.pos, 5))
							{
								if (player.alive)
									player.points += 10;
								asteroid.active = false;
								asteroid.~Asteroid();
								laser.active = false;
								laser.~Laser();
							}
						}
						if (asteroid.size == 2)
						{
							if (CheckCollisionCircles(asteroid.pos, 50, laser.pos, 5))
							{
								if (player.alive)
									player.points += 20;
								float speedX = cos((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								float speedY = sin((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								asteroids.emplace_back(asteroid.pos, speedX, speedY, true, 1);
								asteroid.active = false;
								asteroid.~Asteroid();
								laser.active = false;
								laser.~Laser();
							}
						}
						if (asteroid.size == 3)
						{
							if (CheckCollisionCircles(asteroid.pos, 100, laser.pos, 5))
							{
								if (player.alive)
									player.points += 30;
								float speedX = cos((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								float speedY = sin((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								asteroids.emplace_back(asteroid.pos, speedX, speedY, true, 2);
								speedX = cos((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								speedY = sin((asteroidRotGen(gen) - 90) * PI / 180) * 2;
								asteroids.emplace_back(asteroid.pos, speedX, speedY, true, 2);
								asteroid.active = false;
								asteroid.~Asteroid();
								laser.active = false;
								laser.~Laser();
							}
						}
					}
				}
			}
		}

		if (screen == 2 && IsKeyPressed(KEY_ENTER))
		{
			player.rot = 0;
			player.pos = { scrWidth / 2, scrHeight / 2 };
			player.points = 0;
			player.speed = { 0, 0 };
			player.HP = 3;
			player.alive = 1;
			asteroids.clear();
			lasers.clear();
			screen = 1;
		}

		//RYSOWANIE ----------------------------------------------------------------------------------------------

		BeginDrawing();

		switch (screen)
		{

		case 1:
			DrawTexture(texBackground, 0, 0, WHITE);

			for (auto& laser : lasers)
			{
				if (laser.active)
					DrawCircle(laser.pos.x, laser.pos.y, 5, RED);
			}

			if (IsKeyDown(KEY_W))
			{
				DrawTexturePro(texPlayerThru, { 0, 0, (float)texPlayer.width, (float)texPlayer.height }, { player.pos.x, player.pos.y, 100, 100 }, { 50, 50 }, player.rot, WHITE);
			}
			else
			{
				DrawTexturePro(texPlayer, { 0, 0, (float)texPlayer.width, (float)texPlayer.height }, { player.pos.x, player.pos.y, 100, 100 }, { 50, 50 }, player.rot, WHITE);
			}

			for (auto& asteroid : asteroids)
			{
				if (asteroid.active)
				{
					if (asteroid.size == 3)
					{
						DrawCircle(asteroid.pos.x, asteroid.pos.y, 100, BROWN);
						DrawCircleLines(asteroid.pos.x, asteroid.pos.y, 100, WHITE);
					}
					if (asteroid.size == 2)
					{
						DrawCircle(asteroid.pos.x, asteroid.pos.y, 50, BROWN);
						DrawCircleLines(asteroid.pos.x, asteroid.pos.y, 50, WHITE);
					}
					if (asteroid.size == 1)
					{
						DrawCircle(asteroid.pos.x, asteroid.pos.y, 20, BROWN);
						DrawCircleLines(asteroid.pos.x, asteroid.pos.y, 20, WHITE);
					}
				}
			}

			//DrawCircle(960, 540, 5, RED);

			DrawText(TextFormat("POINTS: %.d", player.points), 50, 50, 20, WHITE);

			for (float i = 1; i <= player.HP; i++)
			{
				DrawTexturePro(texHeart, { 0, 0, (float)texHeart.width, (float)texHeart.height }, { 70 * i, 100, 50, 50 }, { 25, 25 }, 0, WHITE);
			}

			break;

		case 2:
			DrawTexture(texBackground, 0, 0, WHITE);
			DrawText("GAME OVER", (scrWidth - MeasureText("GAME OVER", 100)) / 2, scrHeight / 2, 100, RED);
			DrawText(TextFormat("POINTS: %.d", player.points), (scrWidth - MeasureText("GAME OVER", 100)) / 2, scrHeight / 2 + 150, 50, WHITE);
			break;
		}

		EndDrawing();
	}

	CloseWindow();
}

int main(int argc, char** argv)
{
	Game();
	return 0;
}