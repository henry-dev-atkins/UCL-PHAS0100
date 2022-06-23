#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Is_Random_Grid_Creating_Correct_Alive_Number", "[Random_Grid]") {
  gol::Grid random_board1 = gol::Grid(20, 20, 12);

  int alive_count = 0;
  for (int i = 0; i < 20; i++)
    {
    for (int j = 0; j < 20; j++)
      {
      if (random_board1.GetElement(i, j) == 1)
        {alive_count++;}
      }
    }
  REQUIRE(alive_count == 12);
}