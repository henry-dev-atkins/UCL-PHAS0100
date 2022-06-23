#ifndef golGameOfLife_h
#define golGameOfLife_h

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include "golMyFunctions.h"

/**
* \file golMyFunctions.h
* \brief Various Utilities.
* \ingroup utilities
*/
namespace gol{

class GameOfLife : public gol::Grid {
public:
    using Grid::Grid; //Inheriting Constuctors from Grid class.
    void TakeStep();
protected:
    std::vector<std::vector<int>> NextGrid;
};

}

#endif