/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golMyFunctions.h"
#include <iostream>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>

namespace gol {

//-----------------------------------------------------------------------------

Grid::Grid(const int &x_count, const int &y_count) : x_count{x_count}, y_count{y_count}, grid(y_count , std::vector<int> (x_count, 0)){};

//-----------------------------------------------------------------------------

Grid::Grid(std::string filename) : grid(0 , std::vector<int> (0, 0))
  {
  std::string file_row;
  std::ifstream readingfile(filename);
  /*
  Here getline is used as it throws errors such as failbit and getbit which are useful.
  It is also not neccesary to call eofbit, making it easier to read/write.
  */
  while (std::getline(readingfile, file_row)) 
    {
    std::vector<int> grid_row;

    for (char &c : file_row) 
      {
      if(c == ' ') {continue;}
      if (c == '-') {grid_row.push_back(0);}
      if (c == 'o') {grid_row.push_back(1);}
      }
    grid.push_back(grid_row);
    }
  x_count = grid[0].size();
  y_count = grid.size();
  }

//-----------------------------------------------------------------------------

Grid::Grid(const int &x_count, const int &y_count, const int &element_count) : x_count{x_count}, y_count{y_count}, grid(y_count , std::vector<int> (x_count, 0))
  {
  if(element_count > x_count*y_count){throw std::invalid_argument("Element count > Available Elements" );}
  else
    {
    /*
    Randomly generate indexes, if that grid index is 1, decrement the iterator so that it repeats. 
    */

    std::random_device random_dev; 
    std::mt19937 generator(random_dev());
    std::uniform_int_distribution<int> x_dist(0,y_count-1);
    std::uniform_int_distribution<int> y_dist(0,x_count-1);

    int added = 0; 
    int x=0; int y=0;
    while (added < element_count)
      {
      x = x_dist(generator);
      y = y_dist(generator);

      if (grid[x][y] != 1)
        {
        grid[x][y] = 1;
        ++added;
        }
      else {continue;}
      } 
    }
  }

//-----------------------------------------------------------------------------

void Grid::PrintGrid() const  //const means no values are changed, it is used throughout.
  {
  /*
  Initially, std::copy(row.begin(), row.end(), std::ostream_iterator<int>(std::cout, " ")); was used per row.
  This returned integers and was faster, however the assignment required o, - outputs. 
  */
  for (const auto &row : grid)
    {
    for (const auto &element : row)
      {
      if (element == 0)
          {std::cout << "-" << " ";}
      if (element == 1)
          {std::cout << "o" << " ";}
      
      }
    std::cout << "\n";
    }
  std::cout << std::endl;
  }

//-----------------------------------------------------------------------------

void Grid::SetElement(const int &x, const int &y, const int &value)
  {
  if (value != 0 & value != 1)  //Here & is acceptable (vs &&) as no editing is occuring on the RHS or LHS - && only evaluates LHS.
    {throw std::invalid_argument( "Error: Received non-boolean like value" );}
  else
    {grid[x][y] = value;}
  }

//-----------------------------------------------------------------------------

int Grid::GetElement(const int &x, const int &y) const
  {
  //if (x > x_count || y > y_count)
  //  {throw std::invalid_argument( "BALLS Error: Received invalid array index" );}
  //else
    {return grid[x][y];}
  }

//-----------------------------------------------------------------------------

int Grid::GetSize(bool inner_vector) const 
  /*
  This returns the size parameters (for non-member functions to use)
  Called with inner==true for internal vectors (X size width) and false for external vectors (Y size height).
  */
  {
  if (inner_vector)
    {return grid[0].size();}
  else 
    {return grid.size();}
  }

//-----------------------------------------------------------------------------

int Grid::GetNeighborCount(const int &x, const int &y) const 

{
  //These if statements test the 9 cases (4 corners, 4 edges and center) and counts accordingly.
  //std::cout << "Neighbors called for " << x << y << " X,Y="<< x_count-1 << y_count-1;
  int count = 0;
  if (x>=grid.size() || y>=grid[0].size()){return count = 5;}

  else if (x == 0 && y == 0){ 
    if(grid[x+1][y] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x+1][y+1] == 1){count++;}
    return count;}

  else if (x == 0 && y == grid[0].size()-1){
    if(grid[x+1][y] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    if(grid[x+1][y-1] == 1){count++;}
    return count;}

  else if (x == grid.size()-1 && y == 0){ 
    if(grid[x-1][y+1] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x-1][y] == 1){count++;}
    return count;}

  else if (x >= grid.size()-1 && y >= grid[0].size()-1){
    if(grid[x-1][y] == 1){count++;}
    if(grid[x-1][y-1] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    return count;}
     
  else if (y == 0){
    if(grid[x+1][y] == 1){count++;} 
    if(grid[x-1][y] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x+1][y+1] == 1){count++;}
    if(grid[x-1][y+1] == 1){count++;}
    return count;}

  else if (x == 0){
    if(grid[x+1][y] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    if(grid[x+1][y+1] == 1){count++;}
    if(grid[x+1][y-1] == 1){count++;}
    return count;}

  else if (x == grid.size()-1){
    if(grid[x-1][y] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    if(grid[x-1][y+1] == 1){count++;}
    if(grid[x-1][y-1] == 1){count++;}
    return count;}

  else if (y == grid[0].size()-1){
    if(grid[x+1][y] == 1){count++;}
    if(grid[x-1][y] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    if(grid[x+1][y-1] == 1){count++;}
    if(grid[x-1][y-1] == 1){count++;}
    return count;}

  else{
    if(grid[x+1][y] == 1){count++;}
    if(grid[x-1][y] == 1){count++;}
    if(grid[x][y+1] == 1){count++;}
    if(grid[x][y-1] == 1){count++;}
    if(grid[x+1][y+1] == 1){count++;}
    if(grid[x-1][y+1] == 1){count++;}
    if(grid[x+1][y-1] == 1){count++;}
    if(grid[x-1][y-1] == 1){count++;}
  return count;}
  }



} // end namespace

//{ ALTERNATE NEIGHBORS
//int x_index;
//int y_index;
//int count = 0;
//for(x_index = x-1; x_index <= x+1; ++x_index)
//  {
//  for (y_index = y-1; y_index <= y+1; ++y_index)
//    {
//    if (x_index == x && y == y_index){continue;}
//    else if (x + x_index >= 0 && x + x_index < x_count && y+y_index >= 0 && y+y_index < y_count)
//      {count += grid[x_index][y_index];}
//    }
//  }
//return count;
//}