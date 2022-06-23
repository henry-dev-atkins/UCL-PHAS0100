PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment2)

Exercises and Discussion
------------------------
Exercise 1
--
Creating a Particle class which includes methods to Get+Set Eigen::Vector3d of Position, Velocity and Acceleration, as well as an integrateTimestep method which applied the Velocity vector to the Position and Acceleration vector to velocity; taking each through a specified timestep. There is also a PrintValue function which prints out Velocity and Position. This is exemplified in the nbsimExercise.cpp executable. Unit tests in Group 'Exercise 1' test for time evolution under 0 Acceleration, Constant Acceleration and Centripetal Acceleration. These can be seen by running the unit tests as described below.

Exercise 2
--
 Creating a class called MassiveParticle which inherits Particle (because of the is-a relationship) methods and constructor lets us use many more methods. This has methods including getMu (returns mass * G), add/removeAttractor which adds an instance of MassiveParticle to a vector of particles which are interacting (discussed below). Another member function used is the calculateAcceleration which takes all the attractors in order and calculated the gravitational attraction and rewrites the acceleration for that particle. Tests are used to check that the MassiveParticle moves correctly under constant velocity and 2-body Circular orbit. 

Attractor Discussion - This vector contains objects of type MassiveParticle. A vector containing smart pointers (to MassiveParticle instances) was considered, and discarded because of the specific use of the attractors container and the CPU's utilisation of Hardware Prefetcher. As described in Source [1]; when vectors are stored in adjacent memory locations, calls to memory are much faster if the memory is iterated through in order. As attractors is only iterated through in 0,1,2,3,4... order, subsequent calls are very fast. When our MassiveParticle is larger than the cache line (64 byte) - which it always is (3x3d vectors) - one CPU call can prefetch data rather than recalling on different CPU lines. Pointers call 1 cache line at a time. If our object is 100 bytes (line 1 has 64, line 2 has 36), a CPU calls once while a pointer calls twice (once per line). Because of the fast memory retrieval time, and less cache calls, MassiveParticle objects were used instead of pointers to MassiveParticles. 

Exercise 3
--
The solarSystemSimulator executable simulates the solar system from the supplied data (nbsimSolarSystemData.ipp) for a given period in each step count. To do this, a class called SystemSim was created. It takes a vector of MassiveParticles (called planet_data) and can operate on this. The member functions are: SystemSim (x3), GetPlanetName, AddSystemAttractors, KinetIcEnergy, GravitationalEnergy and Energy. The 3 constructors allow for three types of instantiation: Empty (Testing) Solar System Data (Exercise 3) and Random Data (Exercise 6). The Random constructor is described below in Exercise 6 discussions. The Solar System constructor takes data from the provided solarSystemData.ipp file and parses it into position, velocity , mass and name data. The function is given an empty vector (planet_data) to fill up with MassiveParticle objects, each instantiated with data from the file. GetPlanetName is added so that printing names of planets may be done alongside the vector planet_data. It is necessary for only the end of Exercise 3f, so is not build into any other functions. Add system Attractors takes each planet in turn, loops through the other masses and adds each to the attractors vector with the addAttractor method, from the MassiveParticle class. Kinetic and Gravitational Potential Energy calculations are conducted here as well. They follow the expressions provided in the brief and the final Energy Calculation is a summation of these. This may be executed by running 
-	    ./bin/solarSystemSimulator <Time> <Steps>
where <Time> represents the time you want to execute the calculation over and <Steps> is the number of discrete calculation steps within this time. For example,
-	    ./bin/solarSystemSimulator 1 36500
This is exemplified in the image attached in the Screenshots Folder (3f Exercise) which is a screenshot of the positions of all the planets after 1 year. This can be replicated by running the commands in Exercise 4.


Exercise 4 & 5
-
Adding Energy Conservation with the Member functions described above (Exercise 3) lets us test the accuracy of our simulation. Running the Solar System simulation for 1 year in 36500 steps, with a step size of roughly 0.000274 (1/0.000274 = 3650) outputs:

-	    vscode ➜ /workspaces/PHAS0100Assignment2/build (main ✗) $ ./bin/solarSystemSimulator 0.000274 3650 
                Simulating 1.0001 year in 3650 steps.
                Simulation Calculation Time (s): 0.0035338
                Kinetic Energy - Start - End - Error: 0.187135 0.187037 -0.0526005%
                Gravitational Energy - Start - End - Error: -0.356872 -0.33575 -5.91856%
                Total Energy Error: -12.3858%



Where each energy value is a decimal error from the initial energy (an error of 0.0005 = 0.05% error). The above calculation simulated with 6% error in 0.04s. Does the accuracy increase as the step size is decreased (step count increased)?  

-	           Simulating the Solar System for 100 years and Comparing Calculation Accuracy and Calculation Time 
        | Step_Count(/yr) | Step_Size(yr)  | Calculation Time(s) | Total Error % | Kinetic Error % | Gravitational Error % |
        |       1e3       |    0.100000    |      0.0008749     |   -12.3827%   |   -0.0525808%   |      -5.91708%        |
        |       5e3       |    0.020000    |      0.004116      |   -12.3826%   |   -0.052595%    |      -5.91704%        |
        |       1e4       |    0.010000    |      0.0085116     |   -12.3826%   |   -0.0525968%   |      -5.91703%        |
        |       5e4       |    0.002000    |      0.0441417     |   -12.3826%   |   -0.0525983%   |      -5.91703%        |
        |       1e5       |    0.001000    |      0.0871703     |   -12.3826%   |   -0.0525984%   |      -5.91703%        |
        |       5e5       |    0.000200    |      0.399655      |   -12.3826%   |   -0.0525986%   |      -5.91703%        |
        |       1e6       |    0.000100    |      0.809904      |   -12.3826%   |   -0.0525986%   |      -5.91703%        |
        |       5e6       |    0.000020    |      4.177         |   -12.3826%   |   -0.0525986%   |      -5.91703%        |
        |       1e7       |    0.000010    |      7.9645        |   -12.3826%   |   -0.0525986%   |      -5.91703%        |

Benchmarking this above data means balancing calculation time and accuracy. As you can see, each error (Kinetic and Gravity) decreases as the step size falls. By the end they have both reached constants of -0.0526% for Kinetic and -5.92% for Gravitational. The step size they reach this at is 0.01. therefore, the optimum balance between accuracy and time is at this 0.01-year step size. As well as this, some interesting trends can be seen here. A roughly constant error exists throughout. This is possibly because the error may be linked to the time simulated. if this simulation is incorrect by a constant amount per timestep then it stands to reason that the error will be proportional to the Time simulated, as well as the number of steps (which is proved above to be a weak association). Below, this idea is explored by choosing a constant number of timesteps (1e6) and varying the simulated time.

-	             Simulating the Solar System in 1e6 steps and Comparing Calculation Accuracy and Time Simulated
        | Simulated Time(yr) | Step_Size(yr)  | CalculationTime(s) | Total Error % | Kinetic Error % | Gravitational Error % |
        |         0.0001     |       1e-10    |       1.08755      |  0.00267121%  |  -3.21171e-06%  |      0.00126881%      |
        |         0.0005     |       5e-10    |       0.992967     |  0.0133122%   |  -1.60449e-05%  |      0.00632317%      |
        |         0.001      |       1e-9     |       0.867499     |  0.0265139%   |  -3.21001e-05%  |      0.0125938%       |
        |         0.005      |       5e-9     |       0.840047     |  0.12792%     |  -0.000161104%  |      0.0607573%       |
        |         0.01       |       1e-8     |       0.840394     |  0.242723%    |  -0.000323692%  |      0.115275%        |
        |         0.05       |       5e-8     |       0.839552     |  0.47195%     |  -0.00167633%   |      0.223591%        |
        |         0.1        |       1e-7     |       0.862696     |  0.205721%    |  -0.00348977%   |      0.0960155%       |
        |         0.5        |       5e-7     |       0.832556     | -1.44854%     |  -0.0212358%    |     -0.700093%        |
        |         1.0        |       1e-6     |       0.838749     | -12.3826%     |  -0.0525986%    |     -5.91703%         |
        |         5.0        |       5e-6     |       0.840308     | -123.42%      |  -0.231785%     |     -58.8229%         |

From the above data it can be seen that the error is proportiaonal to the time simulated. This implies that the simulation has some small, compounding error which builds through time. This is possibly due to inaccuracies in the acceleration calculation.

Exercise 6
--

The random generator operates through the SystemSim constructor including the number_of_planets. It works as follows: A 2 random generators are created, one in the range 0.4-40 and the other in 0-360. These generate r and theta and can then be used to make a planet with position and velocity as described in the brief. First a Large (Mu=80) mass is placed at the centre with zero velocity. Then, while the number of added planets is less than the desired input r, theta and the corresponding position/velocities are input to a MassiveParticle object and added to the planet_data vector. This creates a vector of n_planets randomly initialised MassiveParticle objects.  Each of these random objects has a Mu of 1.0.
        
An issue which arises involves the mass at the centre. As it is stationary at the start, its 0 Kinetic Energy contributes nothing to the Energy calculations. After 1 timestep the central mass has an acceleration applied and moves. As it is such a huge mass it does not move much, but it increases the KE by an order of x10^3. This continues and creates large errors in the randomSystemSimulator executable. This may be solved in a few ways:
        
1. Taking the second (not initial) Kinetic Energy calculation as the first, removing the centre-stationary state. This would lead to inaccuracies in the Gravitational Energy calculations, and discrepancies so it was discarded.
2. Another possibility is of ignoring the central mass in the acceleration calculation loop. This would have some benefits in that it would be easy to edit and compare for any users (i=0 ->i=1) however would also mean that the gravity calculation was incorrect, as huge potential exists between the closest planets and the central massive object. 
3. I decided to leave the calculation as it is, as it is important to not bias the KE or GPE calculations, and have true values, and Jim Dobson told me to. This means that any user of this code should not rely on its accuracy, and should also be aware that the existence of this problem may of obscured other bugs which went unnoticed.  

Exercise 7
--
In Parallelizing the randomised system a major problem occurred with respect to the Operating System I am running. In the Windows-Docker installation being ran, the number of CPU threads may only be edited through the .wslconfig file. This meant that the following experiments are for benchmarking only, and actual times may be much faster if adapted to a better machine. When trying to fix this, I corrupted the docker installation 3 times, had to revert this code version in git twice and needed a reinstall of the WSL drivers. Needless to say, I do not recommend attempting to fix this yourself on a windows machine, but the following analysis has been conducted and the necessary code (which should compile) is in the relevant files.    

To implement parallel code in the randomSystemSimulator, the time evolution loop is passed inside an if statement, allowing series and parallel execution, depending on a Boolean 0/1 user input. Then, the calculateacceleration is parallelised by creating a temporary private variable called local_acc. This lets eachthread calculate its own acceleration within the loop. After the loop (but still inside the parallel section) we add all the threads to  the existing acceleration under the omp critical barrier. To parallelise the intergrateTimestep, a simple prallel for loop is used, as each thread takes care of only one planet, no interactions are needed.

To paralellise the Energy calculations, reductions of the Egrav and Ekin variables was needed because they add sequentially. Please see the comments in the nbsimSystemSimulator.cpp file. 

Firstly, a benchmarking with respect to parallel thread count is conducted, yielding disappointing results. As the time to compute should roughly be inversely proportional to the number of used threads, these apparently constant times show no parallelism was occurring. Mentioned above, only 1 CPU was conducting this. Using the Series time as a base, we would expect the 1 Core time the be slightly longer because of the overhead of making a control block for parallel sections, allocating thread memory etc and lack of actual parallelism - there is still only 1 core. This calculation time would be expected to roughly half in the 2-core execution as the threads are now sharing about 50% of the execution each. The 4-core execution would be expected to be fastest, as this machine has 4 CPU-cores so multithreading is maximised. Interestingly, the 5-core execution would likely be the slowest of them all, maybe on par with the Series Time. This is because the code asks the machine to allocate memory and commands across 5 threads while it only has access to 4. This causes undefined behavior and would likely cause a program crash.   


-	                   Simulating a Random 2000 body System in Parallel for 1 years - Comparing Thread Count and Time 
       
        | Step Count (/yr) | Series Time (s)| 1 Core Time (s) | 2 Core Time (s) | 3 Core Time (s) | 4 Core Time(s) | 5 Core Time(s) | 
        |      100         |     5.65468    |     5.74774     |     4.9866      |    4.76599      |    5.78729     |    4.74183     | 
        |      250         |     12.0141    |     15.6321     |     13.7986     |    11.8358      |    11.6978     |    13.2455     | 
        |      500         |     26.4167    |     28.5551     |     26.7004     |    23.6316      |    26.5885     |    23.3576     | 
        |      750         |     39.5869    |     40.4892     |     36.8601     |    35.5172      |    40.9976     |    35.1161     | 
        |      1000        |     55.1185    |     58.2222     |     49.9349     |    47.9961      |    54.64       |                | 
        |      2500        |     141.624    |                 |     125.713     |    122.25       |    136.102     |                |
        |      5000        |     284.331    |                 |     259.218     |    259.218      |    277.183     |                |
        |      7500        |     420.499    |                 |     411.289     |                 |                |                | 



Dependencies
------------
 - Ubuntu 20.04 docker image (recommended)

 - g++ 9.3.0 (enforcing C++17)

 - CMake 3.16.3 

 - OpenMP 5.1


File Index
------------------
Inside CommandLineApps:
-   nbsimExerciseApp - Contains Exercises 1-3.
-   randomSystemSimulator - Contains Simulator for Random System.
-   solarSystemSimulator - Contains Solar System Simulator.

Inside Lib
-   nbsimBasicTypes(.cpp & .h)
-   nbsimException(.cpp & .h)
-   nbsimExceptionMacro(.cpp & .h)    
-   nbsimMassiveParticle(.cpp & .h) - Contains MassiveParticle Class individual to each planet and includes interactions.
-   nbsimMyFunctions(.cpp & .h)
-   nbsimParticle(.cpp & .h) - Contains Particle class, the root class for MassiveParticle, includes parameters individual to 1 particle.
-   nbsimSolarSystemData.ipp - Contains data for the Solar System.
-   nbsimSystemSimulator(.cpp & .h) - Contains the SystemSim class for creating and simulating systems under gravitational interactions.

Build Instructions
------------------
To build, please make sure dependencies (above) have been followed.

Type the following commands in your terminal, after navigating to inside the PHAS0100Assignment2 repository.
-	    mkdir build 
	    cd build
	    cmake ..
	    make


Then to run executables:
-	nbsimExerciseApp

            ./bin/nbsimExerciseApp
-	randomSystemSimulator

                ./bin/randomSystemSimulator <Planet_Count> <Timestep> <Number_of_Steps> <Parallel?>
                ./bin/randomSystemSimulator 2000 0.01 100 1
-       solarSystemSimulator

                ./bin/solarSystemSimulator <Timestep> <Number_of_Steps>
                ./bin/solarSystemSimulator 0.000274 3650

Unit Test
------------------
To run the Unit tests, build as above and execute the following terminal commands. 
-	  ./bin/nbsim <TEST_NAME>

Alternatively, using CTest inside build directory:
-	  cmake -DBUILD_TESTING:BOOL=ON ..
  	  make
  	  ctest .

valgrind --leak-check=yes -s <executable>



Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).

Sources
-------
[1] - https://www.cppstories.com/2014/05/vector-of-objects-vs-vector-of-pointers/

