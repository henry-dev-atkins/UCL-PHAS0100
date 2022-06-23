
#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Is_Count_Correct_Boundary_Condition_Corners?", "[Neighbor Count]") {
  gol::GameOfLife board = gol::GameOfLife("../Testing/Data/count_test_file.txt");

  int error_count = 0;

  if(board.GetNeighborCount(0, 0) == 1){++error_count;}
  if(board.GetNeighborCount(0, 11) == 2){++error_count;}
  if(board.GetNeighborCount(11, 0) == 0){++error_count;}
  if(board.GetNeighborCount(11, 11) == 3){++error_count;}

  REQUIRE(error_count == 0);
}