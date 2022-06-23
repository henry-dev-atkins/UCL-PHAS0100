#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <cstring>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "golMyFunctions.h"
#include "golGameOfLife.h"

int main(int argc, char** argv)
{
if (argc == 1){std::cout << "\n" << "Give arguments in following format: \nFOR TEXT-FILE READ DATA: \nname generations \neg: ./bin/gofSimulator oscillators.txt 3 \nFOR RANDOM GENERATED DATA: \nx_count y_count number_of_alive generations \neg : ./bin/gofSimulator 10 10 2 2 \n" << std::endl;}
if (std::strcmp(argv[1], "--help")==0 || std::strcmp(argv[1], "-h")==0){std::cout << 
    "Help: \n \nThis Game of Life simulation prints game of life grids to the terminal. You may choose pre-made text files by passing the .txt filename as a parameter, or choose a random grid by passing sizes and number of expected alive cells, you also pass the number of generations (time steps) you would like to progress through, this applys the rules as described in the README file.\n \nText File:\n \nTo give a text file, please input the name of the file to the program as a parameter like this - ./bin/gofSimulator oscillators.txt 2 - where the 2 here represents the generations which you want to progress through. In this case, the function takes the oscillators.txt, appends the path - ../Testing/Data/ - to the front and progresses the input file through 2 steps. \n \nRandom Alive States \n \nThe second option is to run the program with randomised alive cells. To do this, the user must specify the size of the grid (x and y sizes) the number of alive cells within that grid, and again the number of generations, like this - ./bin/gofSimulator 10 11 12 13 - which creates a 10x11 grid and fills it with 12 alive cells. Using this as a starting grid, the program progesses through 13 generations and returns the final one." 
    << std::endl;}

else if (argc == 3)     //FROM FILE
    {
    std::string path = "../Testing/Data/";                     //Command line passing user inputs.
    std::string name = argv[1];        
    int generations = std::stoi(argv[2]);                      // stoi throws failure exception while atoi does not.
    std::string filename = path.append(name);                  // append is faster than string + string.

    gol::GameOfLife board = gol::GameOfLife(filename);
    std::cout << "Initialised as: " << std::endl;
    board.PrintGrid();

    for (int i = 0; i <= generations; i++)
        {
        board.TakeStep();                 //CHANGE T HIS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::cout << i+1 << "th Iteration: " << std::endl; 
        board.PrintGrid();
        std::this_thread::sleep_for (std::chrono::seconds(1));   //Sleep for 1s per iteration.
        }
    }

else if (argc == 5)     //FROM RANDOM
    {
    int x_count = std::stoi(argv[1]);       
    int y_count = std::stoi(argv[2]);
    int number_place = std::stoi(argv[3]);
    int generations = std::stoi(argv[4]);

    gol::GameOfLife board = gol::GameOfLife(x_count, y_count, number_place);
    std::cout << "Initialised as: " << std::endl;
    board.PrintGrid();

    for (int i = 0; i <= generations; i++)
        {
        board.TakeStep(); 
        std::cout << i+1 << "th Iteration: " <<std::endl;
        board.PrintGrid();
        std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    }

//Error messege for incorrect number of command line arguments.
else {std::cout << "Please ensure param:" << "\n" <<  "Filename" << "\n" << "x_count " << " y_count " <<  " number_of_random "; return 0;} 

}