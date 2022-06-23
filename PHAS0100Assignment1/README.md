PHAS0100ASSIGNMENT1
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment1.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment1)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment1)


Purpose
-------

This project serves as a starting point for the PHAS0100 2021/22 Assignment 1 Game of Life Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 


Some general discussion points:
- The decision to use a 2D vector memory container was to avoid working with the more complex dynamically allocated arrays.
- The use of integers instead of Booleans in the grid (2D vector) is because vector<bool> does not behave as expected, as the vector container is not expecting a single bit. 
Integer was used over vector<char> as there may be a minor speed improvement when using direct machine types (Boolean, integer) over interpreted types (char, string). 
-	A major issue throughout the project was the ordering on vector indices. When defining a vector through the - std::vector<std::vector<int>> vector(y_count, std::vector<int> (x_count, 0)); - command, the x_count (throughout the README this is referred to X) and y_count (Y) are the width and height respectively. Despite these in row major ordering, indexing in column major was occurring in the TakeStep function. This meant that when the grid was square, the output was fine. However, when the grid was uneven (case 1 = 30x15) or (case 2 = 15x30) segmentation errors and invalid pointers occurred. This is because Case1: as x headed for X=30 in grid, it reached the 15th (index 14) element of grid2 and sent an invalid pointer error. In case 2: as x headed for 15, it reaches 15 and then loops back around, missing elements 15-30. These were fixed by rewriting the loop in terms of grid.size() and grid[0].size() – ignoring x_count and y_count. Development of this problem may be accessed in the git log. 

This project has 9 parts, each described below. 

By running the executable main:

1. General understanding of the Game of Life. The world is established as a 2D grid of cells. Each is either alive or dead. Dead cells may become alive if they have 3 alive neighbours. Alive cells remain alive if they have 2 or 3 neighbouring alive cells. All others die (or remain dead) in the next time step. 

2. Create the world, a 2D grid. This is found by running the main executable and shows a 5x5 grid of dead (empty or 0) cells. This has functions to retrieve cell contents and change cells values. The example changes cell (2,3) from dead to alive (0->1). A function to print out the grid is also made here called PrintGrid, which works by iterating through rows and columns of the grid, printing 'o' for alive (1) and '-' for dead (0). Get and Set functions are made for acting on individual elements in the grid. These are called SetElements(x,y,value) and GetElement(x,y) where x,y is the grid coordinate and value is the value the element will be set to. If the value is not 0 or 1, the function will return an error. 

3. Randomly create a seed. Using the <random> functions, generating a random assortment of N alive cells on an X, Y size grid, where N, X and Y are user definable inputs. The random elements are created by creating 2 uniform generators in ranges (0,  y_count-1) and (0,  x_count-1). These are used to make a 2D index pair which is passed to grid[random x][random y]. If this position is already 1 (alive) then the iterator for placed elements is decremented by one such that the process repeats with new indices. This avoids repeating indices, which cause the number of alive cells  to be less than expected, even though the correct number of random indices was passed. The probability of generating less than N alive cells is therefore N/(X*Y). Running main shows that repeating the random generator returns different (random) configurations.  For completeness, an alternative (previously used) method is discussed here. Random numbers could also be found by generating vectors of length x_count and y_count and shuffling them. Iterating through them will give a sequence of non-repeating numbers which can be used as indices. These will never be larger than the dimensions of the grid. The issue arises when these are not equal length, and the number of random elements to generate is larger than the vector lengths. Modulo arithmetic may be used where one is larger than the other, however if the alive element target is larger than both, the result is a repeating pattern of indices. For this reason, the writer used the previously outlined method. 

4. Reading a text input. Running main returns an example of reading the 'oscillators.txt' file inside Testing/data. The file may be changed by editing the name - e.g. to 'gliders.txt' - to any text file input. This is done by iterating through the file and parsing by ' ' spaces and newlines to produce a vector of integers from 'o'= 1 and '-'= 0. These integers are 1 or 0 only. 

5. Count the alive neighbours of a given cell. By indexing the 2D vector at 9 configurations (4 corners, 4 sides and the centre) all the possible combinations of surrounding cells are considered in the GetNeighborCount function. Cells beyond the world are considered dead, so are ignored. Running main shows how cells in the oscillators.txt file can be counted.

6. Making the game. Bringing the functions together into a class with a TakeStep function (uses the counted neighbouring cells to apply the rules) which iterates through a generation. Running main shows how this is used on the oscillator.txt file. 
By running the executable gofSimulator:

7. Making a game executable. Using various user input configurations (for these run – gofSimulator - with '-h' or '--help' as an input) allows a user to play this game. Either by making a text file, or by creating a random grid, a user may run the game up to any generation from the command line. The GameOfLife class inherits the functions from the Grid class, including constructors via the - using  - command. This means GameOfLife may be constructed identically and pulls all the functions from Grid while adding the necessary TakeStep function. This function takes the grid through to the next generation by using GetNeighborCount on every cell, then applying the rules from Exercise 1. 

8. Coursework evidence. Access the Coursework_images file for screenshot evidence of working function calls. 

By running executable StillLifes:

9. Equilibrium life/stable life. many configurations of initial alive cells lead to empty grid, devoid of all life. Some reach points where each generation has identical cell outputs. This is when every alive cell has 2-3 alive neighbours, causing each one to continue living, although none are born or killed. This executable finds random initial configurations of cells which end up in this equilibrium state. States I observed, and their names according to - https://conwaylife.com/wiki/List_of_common_still_lifes - : Blocks, Beehives, Loafs.

Dependencies
-------
 - Ubuntu 20.04 docker image (recommended)

 - g++ 9.3.0 (enforcing C++17)

 - CMake 3.16.3 

Used external header files:
iosteream, 
vector, 
iterator, 
algorithm, 
string, 
cstring,
thread, 
chrono, 

File Index
------------------

Inside CommandLineApps:
-	gofSimulator.exe simulates the text/random grid over generations.
-	main.exe showcases functions and fulfils Exercises 2 through 6.
-	StillLifes.exe finds stationary grids.

Inside Lib
-	golGameOfLife.cpp contains the TakeStep function.
-	golGameOfLife.h defines the GameOfLife class, including inheriting all functions from Grid.
-	golMyFunctions contains all functions for the Grid Class, 3 Constructors, PrintGrid, GetSize, GetElement, SetElement, GetNeighborCount.

-	golMyFunctions.h defines Grid Class.
-	Redundant files: golBasicTypes(.cpp & .h), golException(.cpp & .h), golExceptionMacro.h.


Build Instructions
------------------

To build, please make sure dependencies (above) have been followed.

Type the following commands in your terminal, after navigating to inside the PHAS0100Assignment1 repository.
-	    mkdir build 
-	    cd build
-	    cmake ..
-	    make


Then to run executables:
-	Main (Ex2-6): 

            ./bin/main
-	Simulator Text Files: ./bin/gofSimulator textfilename.txt generations

    where textfilename.txt can be oscillators.txt, gliders.txt etc, and generations is the number of times you wish to apply the rules.

            ./bin/gofSimulator oscillators.txt 5
-	Simulator Random:  ./bin/gofSimulator width height random_elements generations

    where width and height are the dimensions of the grid, random_elements is the number of randomly places alive cells at initialisation. 

            ./bin/gofSimulator 12 12 20 15
-	StillLifes: ./bin/StillLifes width height random_elements generations number_stills

    where number_stills is the number of still life images you aim to produce.
    
            ./bin/StillLifes 12 12 20 15 10
    


Unit Test
------------------
To run the Unit tests, build as above and execute the following terminal commands. 
-	  ./bin/gol <TEST_NAME>

Alternatively, using CTest inside build directory:
-	  cmake -DBUILD_TESTING:BOOL=ON ..
-	  make
-	  ctest .

valgrind --leak-check=yes -s ./bin/gofSimulator 5 8 5 1


Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).

This project was developed by Henry Atkins.





