#include <gtest/gtest.h>
#include "Cosmo_Miner.h"

// Ogólne przyk³ady jak przeprowadzaæ testy zosta³y wziête z chatuGPT ale ponie¿sze testy zosta³y napisane przeze mnie

TEST(CosmoMinerTests, PlayerSimpleMovement)
{
    Player player;
    player.pos = { 10 , 10 };
    player.speed = { 100, 100 };
    player.movement();
    EXPECT_EQ(player.pos.x, 110);
    EXPECT_EQ(player.pos.y, 110);
}

TEST(CosmoMinerTests, PlayerMovementBesidesBorder)
{
    Player player;
    player.pos = { 0, 0 };
    player.speed.x = -10;
    player.movement();
    EXPECT_EQ(player.pos.x, 1920);
}

TEST(CosmoMinerTests, PlayerDMGTest)
{
    Player player;
    player.HP = 3;
    player.takeDMG();
    EXPECT_EQ(player.HP, 2);
}

TEST(CosmoMinerTests, PlayerDeathTest)
{
    screen = 1;
    Player player;
    player.HP = 1;
    player.alive = true;
    player.takeDMG();
    EXPECT_EQ(player.HP, 0);
    EXPECT_FALSE(player.alive);
    EXPECT_EQ(screen, 2);
}

TEST(CosmoMinerTests, AsteroidGen)
{
    Game game;
    game.asteroidCurrentCD = 0;
    game.asteroidGen();
    EXPECT_TRUE(game.asteroids[1].active);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}