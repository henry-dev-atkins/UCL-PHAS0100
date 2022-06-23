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

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

int main(int argc, char** argv)
{

  int returnStatus = EXIT_FAILURE;

  try
  {
    //EXERCISE 1
    std::cout << "  Exercise 1:" << "\n";
    //Eigen::Vector3d pos(std::stol(argv[1]), std::stol(argv[2]), std::stol(argv[3]));
    //Eigen::Vector3d vel(std::stol(argv[4]), std::stol(argv[5]), std::stol(argv[6]));
    //Eigen::Vector3d acc(std::stol(argv[7]), std::stol(argv[8]), std::stol(argv[9]));
    Eigen::Vector3d pos(1.0, 0.0, 0.0);
    Eigen::Vector3d vel(0.0, 0.0, 0.0);
    Eigen::Vector3d acc(0.0, 0.0, 0.0);

    nbsim::Particle mass1 = nbsim::Particle(pos, vel, 10);

    mass1.PrintValues();
    for (int i=0; i<10; i++)
      {
      mass1.intergrateTimestep(1);
      }

    mass1.PrintValues();
    std::cout << std::endl;
    

    //Exercise 2
    std::cout << "  Exercise 2:" << "\n";
    nbsim::MassiveParticle mass2 = nbsim::MassiveParticle(pos, vel, 1.49828e10);
    std::cout << "Mu = " << mass2.getMu() << "\n";

    nbsim::MassiveParticle mass3 = nbsim::MassiveParticle(Eigen::Vector3d(-1.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0), 1.49828e10);
    nbsim::MassiveParticle mass4 = nbsim::MassiveParticle(Eigen::Vector3d(0.0, 3.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0), 1.49828e10);
    mass2.addAttractor(mass3); mass2.addAttractor(mass4);
    mass3.addAttractor(mass2); mass3.addAttractor(mass4);
    mass4.addAttractor(mass2); mass4.addAttractor(mass3);

    std::cout << "Attractors Added: \n";
    mass2.removeAttractor(mass3);

    std::cout << "Attractor Removed: \n";
    mass2.addAttractor(mass3); //Adding removed mass back into attractors for a complete calculation.

    std::cout << "After 30s(300x0.1), mass 2 moves - under influence from mass 3 - from: \n";
    mass2.PrintValues();
    for (int i=0; i<2; i++)
      {
      mass2.calculateAcceleration();
      mass3.calculateAcceleration();
      mass4.calculateAcceleration();
      
      mass2.intergrateTimestep(0.1);
      mass3.intergrateTimestep(0.1);
      mass4.intergrateTimestep(0.1);
      }
    std::cout << "to: \n";
    mass2.PrintValues();
    
    std::cout << std::endl;
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

  return returnStatus;
}