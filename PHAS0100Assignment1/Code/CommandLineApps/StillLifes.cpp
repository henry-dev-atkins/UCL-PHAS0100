#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
//#include <cstring>
#include <thread>    
#include <chrono>    
#include "golMyFunctions.h"
#include "golGameOfLife.h"

int main(int argc, char** argv)
{
if (argc == 6)
    {
    int x_count = std::stoi(argv[1]);
    int y_count = std::stoi(argv[2]);
    int number_to_place = std::stoi(argv[3]);
    int generations = std::stoi(argv[4]);
    int target_stills = std::stoi(argv[5]);
    int stills = 0;

    while (stills <= target_stills)
        {
        gol::GameOfLife board = gol::GameOfLife(x_count, y_count, number_to_place);
        std::vector<std::vector<int>> base(y_count, std::vector<int> (x_count, 0));
        
        //The variable tot_elements is the size of the grid. it is not just X*Y because iterate to (x_count - 1) - not 0 centerd, its 1 centered.
        int tot_elements = ((y_count*x_count) - y_count);
        
        for (int gen = 0; gen != generations; gen++)
            {
            board.TakeStep();
            int identical_cell_count = 0;
            int number_identical_zeros = 0;

            /*
            The variable tot_elements is the size of the grid. 
            It is looping over elements to test identicallity. If the number of identical cells in the two grids are the same, a stil has almost been found.
            We also need to test for all 0 grids, which are identical but are not stills. 
            If number_identical_zeros is NOT tot_elements, and identical_cell_count is tot_elements,  it is a still.  
            */
            for (int y = 0; y < y_count-1; y++)             
                {
                for (int x = 0; x <= x_count-1; x++)
                    {
                    if (base[x][y] == board.GetElement(x, y))
                        {
                        ++identical_cell_count;

                        if (board.GetElement(x, y) == 0) 
                            {++number_identical_zeros;}
                        }
                    }
                }
            //Identicallity tests:
            if (identical_cell_count == tot_elements & number_identical_zeros != tot_elements)
                {
                ++stills;
                std::cout << "The " << stills << "th found grid " << " after " << gen << " Generations becomes:" << std::endl;
                board.PrintGrid();
                break;
                }

            /*
            If it is not a still, move board into base in preperation for TakeStep on board in next iteration.
            board.swap(base); would preferably be used below, however board variable is protected in GameOfLife and must be accesed element-wise with the GetElement function.
            */
            else 
                {
                for (int y = 0; y < y_count-1; y++)
                    {
                    for (int x = 0; x <= x_count-1; x++)
                        {base[x][y] = board.GetElement(x, y);}
                    }
                
                }
            }
        }    
    return 0;   
    }

else {std::cout << "Please ensure param: x_length y_length number_of_random generations number_stills"; return 1;}

}