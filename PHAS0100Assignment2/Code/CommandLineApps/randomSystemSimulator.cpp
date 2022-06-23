/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include <nbsimExceptionMacro.h>
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include "nbsimSystemSimulator.h"


#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>
#include <random>

#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>


#define THREAD_NUM 5 //CHANGE THIS TO REFLECT VARYING THREAD COUNTS, AS IN EXERCISE 7.

typedef std::chrono::high_resolution_clock myClock;

int main(int argc, char** argv)
{ 
  int returnStatus = EXIT_FAILURE;
  if (argc != 5 || argc == 1 || std::strcmp(argv[1], "--help")==0 || std::strcmp(argv[1], "-h")==0)
    {
    std::cout << "Help: \n execute as follows: \n ./bin/randomSystemSimulator <Mass Number> <Timestep Size> <Number of Steps> <Boolean Parallel?> \n For Example: \n ./bin/randomSystemSimulator 2000 0.00274 3650 1 \n";
    return returnStatus;
    }

  else 
    {
    int planet_count = std::atoi(argv[1]);
    double timestep = std::atof(argv[2]);
    int count = std::atoi(argv[3]);
    int parallel = std::atoi(argv[4]);
    omp_set_num_threads(THREAD_NUM);                  //Setting the numbe rof parallel threads.

    try
      {
        //Setup
        std::vector<nbsim::MassiveParticle> planet_data;

        nbsim::SystemSim simulate = nbsim::SystemSim(planet_data, planet_count);  //Calling the random constructor.

        double start_KE = simulate.KineticEnergy(planet_data, planet_count);
        double start_GE = simulate.GravatationalEnergy(planet_data, planet_count);
        double start_E = simulate.Energy(planet_data, planet_count);
       
        auto start = myClock::now();
        //Time Evolution
        if (parallel == 0)  //Series Evolution
          {
          for (int step = 0; step < count; step++)
            {
            for (int i = 0; i < planet_count; i++)
              {
              planet_data[i].calculateAcceleration();
              }
            for (int i = 0; i < planet_count; i++)
              {
              planet_data[i].intergrateTimestep(timestep);
              }
            }
          }

        if(parallel == 1) //Parallel Evolution
          {
           for (int step = 0; step < count; step++)
            {
            for (int i = 0; i < planet_count; i++)
              {
              planet_data[i].calculateAcceleration(true); //Calling the parallel acceleration.
              }
            #pragma omp for schedule (static, 1)          //Parallelise the for loop with threads taking ordered iterations. 
            for (int i = 0; i < planet_count; i++)
              {
              planet_data[i].intergrateTimestep(timestep);
              }
            } 
          }
        auto end = myClock::now();

        double end_KE = simulate.KineticEnergy(planet_data, planet_count);
        double end_GE = simulate.GravatationalEnergy(planet_data, planet_count);
        double end_E = simulate.Energy(planet_data, planet_count);

        //Results
        std::cout << "Simulating " << timestep*count << " year in " << count << " steps." << std::endl;
        std::cout << "Simulation Calculation Time (s): " << (end - start).count() / 1e9 << std::endl;
        simulate.PrintErrors(end_KE, start_KE, end_GE, start_GE, start_E, end_E);
        returnStatus = EXIT_SUCCESS;
      }
    catch (nbsim::Exception& e)
      {
        std::cerr << "Caught nbsim::Exception: " << e.GetDescription() << std::endl;
      }
    catch (std::exception& e)
      {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
      }
  }
  return returnStatus;
}

