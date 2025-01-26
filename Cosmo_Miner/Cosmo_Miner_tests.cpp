#include <gtest/gtest.h>
#include "Cosmo_Miner.h"

TEST(PlayerMovementTest, PlayerSimpleMovement)
{
    Player player;
    player.pos = { 10 , 10 };
    player.speed = { 100, 100 };
    player.movement();
    EXPECT_EQ(player.pos.x, 110);
    EXPECT_EQ(player.pos.y, 110);
}

TEST(PlayerMovementTest, PlayerMovementBesidesBorder)
{
    Player player;
    player.pos = { 0, 0 };
    player.speed.x = -10;
    player.movement();
    EXPECT_EQ(player.pos.x, 1920);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}