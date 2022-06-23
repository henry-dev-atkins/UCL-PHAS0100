/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include "golMyFunctions.h"
#include "golGameOfLife.h"


int main(int argc, char** argv)
{
  // Each exercise is executed once here. 
  std::cout << "Exercise 2:" << std::endl;
  gol::Grid board2 = gol::Grid(5,5);
  board2.PrintGrid(); 
  std::cout << "The element at 2,3 is: " << board2.GetElement(2,3) << std::endl;
  board2.SetElement(2, 3, 1);
  std::cout << "Then becomes: " << board2.GetElement(2,3) << std::endl;
  board2.PrintGrid(); 


  std::cout << "Exercise 3: \nA random 15 filled 20x20 grid:" << std::endl;
  gol::Grid board3 = gol::Grid(20, 20, 15);
  board3.PrintGrid(); 
  std::cout << "When the same code is repeated we print:" << std::endl;
  gol::Grid board3b = gol::Grid(20, 20, 15);
  board3b.PrintGrid(); 


  std::cout << "Exercise 4:" << std::endl;
  std::cout << "The Oscillator File - to change this, edit the 'oscillators' to 'glider' or 'still_lifes' - is read, stored and printed below: \n";
  gol::Grid board4 = gol::Grid("../Testing/Data/oscillators.txt");
  board4.PrintGrid(); 


  std::cout << "Exercise 5:" << std::endl;
  std::cout << "For Oscillator - from above - the cells (2, 1) and (2, 8) have neighbors: " << std::endl;
  std::cout << "For (2, 1) " << board4.GetNeighborCount(2,1) << std::endl;
  std::cout << "For (2, 8) " << board4.GetNeighborCount(2,8) << "\n" << std::endl;


  std::cout << "Exercise 6:" << std::endl;
  gol::GameOfLife board6 = gol::GameOfLife("../Testing/Data/oscillators.txt");
  std::cout << "Oscillators file starts like this:" << std::endl;
  board6.PrintGrid();
  std::cout << "Oscillators file ends like this after 1 rule iteration:" << std::endl;
  {board6.TakeStep();}
  board6.PrintGrid();
  std::cout << "Oscillators file ends like this after 2 rule iterations:" << std::endl;
  {board6.TakeStep();}
  board6.PrintGrid();


  std::cout << "Exercise 7, 8, 9:" << std::endl;
  std::cout << "Please open and run the gofSimulator and StillLifes executables as described in the README." << std::endl;

  return 0;
}