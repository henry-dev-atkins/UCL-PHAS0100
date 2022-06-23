#include "golGameOfLife.h"
#include <iostream>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>

namespace gol {

void GameOfLife::TakeStep()
    {
    std::vector<std::vector<int>> NextGrid(y_count, std::vector<int> (x_count, 0));
    int neighborcount = 0;
    for (int y = 0; y < grid[0].size(); ++y)
        {
        for (int x = 0; x < grid.size(); ++x)
            {
            
            neighborcount = Grid::GetNeighborCount(x ,y);

            if (grid[x][y] == 1)
                {
                if(neighborcount == 2 || neighborcount == 3){NextGrid[x][y] = 1;}
                else{continue;}
                }
            else if (grid[x][y] == 0 && neighborcount == 3){NextGrid[x][y] = 1;}
            else {NextGrid[x][y] = 0;}
            }
        } 
    NextGrid.swap(grid);
    }

}