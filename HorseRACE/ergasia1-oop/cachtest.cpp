#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "horse.hpp"

TEST_CASE("horse racing","move_forward")
{
  horse h(1,"horse_1",55,55,87);
  REQUIRE(h.move_forward(1,50.0)==true);
  REQUIRE(h.move_forward(4,52.6)==true);
  REQUIRE(h.move_forward(10,60.34)==true);
  REQUIRE(h.move_forward(5,67.45)==false);
  REQUIRE(h.move_forward(1,67.45)==false);
  REQUIRE(h.move_forward(11,97.12)==false);
}

//horse h(id, name, startup_speed, power, stamina)
//h.move_forward(step, r)

TEST_CASE("horse racing 2", "move_forward 2")
{
    horse h(2, "horse_2", 80, 52, 76);
    REQUIRE(h.move_forward(2, 61.34) == false);
    REQUIRE(h.move_forward(1, 78.23) == true);
    REQUIRE(h.move_forward(6, 99.9) == false);
    REQUIRE(h.move_forward(5, 51.99) == true);
    REQUIRE(h.move_forward(9, 60.1) == true);
    REQUIRE(h.move_forward(9, 64.01) == false);
}

TEST_CASE("horse racing 3", "move_forward 3")
{
    horse h1(4, "horse_4", 78, 90, 69);
    horse h2(5, "horse_5", 59, 68, 87);
    REQUIRE(h1.move_forward(3, 89.07) == true);
    REQUIRE(h1.move_forward(5, 58.3) == true);
    REQUIRE(h1.move_forward(8, 91.7) == false);
    REQUIRE(h2.move_forward(1, 89.07) == false);
    REQUIRE(h2.move_forward(1, 56.5) == true);
    REQUIRE(h2.move_forward(9, 77.4) == true);
    REQUIRE(h2.move_forward(7, 99.07) == false);
}