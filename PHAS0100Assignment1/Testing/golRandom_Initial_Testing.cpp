#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Is_Random_Grid_Initialisation_Unique", "[Random_Grid]") {
  gol::Grid random_board1 = gol::Grid(20, 22, 12); 
  gol::Grid random_board2 = gol::Grid(20, 22, 12);

  int identical_cells = 0;
  for (int i = 0; i < 20; i++)
    {
    for (int j = 0; j < 22; j++)
      {
      if (random_board1.GetElement(i, j) == random_board2.GetElement(i, j))
        {identical_cells++;}
      }
    }
  REQUIRE(identical_cells != (20*22));
}