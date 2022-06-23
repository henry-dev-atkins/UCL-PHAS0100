#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>

TEST_CASE( "Is_Random_Grid_Initialisation_Correct_Size", "[Random_Grid]") {
  gol::Grid random_board1 = gol::Grid(20, 22, 12);
  int error_count = 0;
  if (random_board1.GetSize(false) != 22){std::cout << "Height is Incorrect" << std::endl; error_count++;}
  if (random_board1.GetSize(true ) != 20){std::cout << "Width is Incorrect" << std::endl; error_count++;}
  REQUIRE(error_count == 0);
}