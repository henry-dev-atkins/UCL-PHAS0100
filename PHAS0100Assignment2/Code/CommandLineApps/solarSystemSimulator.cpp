/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <nbsimMyFunctions.h>
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
#include <omp.h>


// Example, header-only library, included in project for simplicity's sake.
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

/**
 * \brief Demo file to check that includes and library linkage is correct.
 */

typedef std::chrono::high_resolution_clock myClock;

int main(int argc, char** argv)
{ 
  int returnStatus = EXIT_FAILURE;
  if (argc != 3 || argc == 1 || std::strcmp(argv[1], "--help")==0 || std::strcmp(argv[1], "-h")==0)
    {
    std::cout << "Help: \n  Please write the following arguments after calling the app: \n Timestep Time. \n This means you need to type: \n ./bin/solarSystemSimulator 0.01 300 \n for a simulation of 300 steps each of size 0.01."<< std::endl;
    return returnStatus;
    }

  else 
    {
    double timestep = std::atof(argv[1]);
    int count = std::atoi(argv[2]);

    try
      {
        //Setup
        int planet_count = 9;
        std::vector<nbsim::MassiveParticle> planet_data;


        nbsim::SystemSim simulate = nbsim::SystemSim(planet_data); //Construct the system with the Solar System Data.

        double start_KE = simulate.KineticEnergy(planet_data, planet_count);
        double start_GE = simulate.GravatationalEnergy(planet_data, planet_count);
        double start_E = simulate.Energy(planet_data, planet_count);

        //Exercise 3f
        std::cout << "Starting Values: " << "\n";
        simulate.PrintSolarSystemData(planet_data);
        
        auto start = myClock::now();
        //Time Evolution
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
        auto end = myClock::now();

        double end_KE = simulate.KineticEnergy(planet_data, planet_count);
        double end_GE = simulate.GravatationalEnergy(planet_data, planet_count);
        double end_E = simulate.Energy(planet_data, planet_count);
        
        //Exercise 3f
        std::cout << "Ending Values: " << "\n";
        simulate.PrintSolarSystemData(planet_data);

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