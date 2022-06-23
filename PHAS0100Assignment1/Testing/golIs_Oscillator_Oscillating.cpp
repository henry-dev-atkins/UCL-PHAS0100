#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Is_Oscillator_Oscillating?", "[Time Step]") {
  gol::GameOfLife base = gol::GameOfLife("../Testing/Data/oscillators.txt");
  gol::GameOfLife board = gol::GameOfLife("../Testing/Data/oscillators.txt");
  board.TakeStep();
  board.TakeStep();

  int error_cells = 0;
  for (int i = 0; i < board.GetSize(true); i++)
    {
    for (int j = 0; j < board.GetSize(false); j++)
      {
      if (board.GetElement(i, j) != base.GetElement(i, j))
        {error_cells++;}
      }
    }
  REQUIRE(error_cells == 0);
}