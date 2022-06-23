#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Empty_Grid_Editing", "[Grid]") {
  int error_count = 0;
  gol::Grid board = gol::Grid(5, 6);
  if (board.GetElement(0,2) != 0){error_count++;}
  board.SetElement(0,2,1);
  if (board.GetElement(0,2) != 1){error_count++;}
  REQUIRE(error_count == 0);
}