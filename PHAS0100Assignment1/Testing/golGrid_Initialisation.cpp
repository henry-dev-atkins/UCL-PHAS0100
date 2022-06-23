/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <golGameOfLife.h>
#include <iostream>
#include <vector>


TEST_CASE( "Grid_Initialisation", "[Grid]") {
  //Cannot use && in REQURE statement as catch does not support it.
  int error_count = 0;
  gol::Grid board = gol::Grid(5, 6);
  std::cout << board.GetSize(false) << board.GetSize(true) << std::endl;
  if (board.GetSize(false) != 6){error_count++;}
  if (board.GetSize(true) != 5){error_count++;} 
  REQUIRE(error_count == 0);
}