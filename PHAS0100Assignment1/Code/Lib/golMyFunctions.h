/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golMyFunctions_h
#define golMyFunctions_h

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

/**
* \file golMyFunctions.h
* \brief Various Utilities.
* \ingroup utilities
*/
namespace gol{

class Grid{
  public:
    Grid(const int &x_count, const int &y_count);
    Grid(const int &x_count, const int &y_count, const int &element_count);
    Grid(std::string filename);
    void PrintGrid() const;
    void SetElement(const int &x, const int &y, const int &value);
    int GetSize(bool inner_vector) const;
    int GetElement(const int &x, const int &y) const;
    int GetNeighborCount(const int &x, const int &y) const;
  protected: //Lets derived classes access.
    int x_count;
    int y_count;
    std::vector<std::vector<int>> grid;
};



} // end namespace

#endif
