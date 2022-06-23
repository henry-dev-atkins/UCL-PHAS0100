/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include "nbsimSystemSimulator.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

TEST_CASE( "No Acceleration", "[Exercise 1]" ) 
  {
  Eigen::Vector3d pos(1.0, 1.0, 1.0);
  Eigen::Vector3d vel(0.0, 0.0, 1.0);
  
  Eigen::Vector3d expected_pos(1.0, 1.0, 11.0);
  nbsim::Particle mass = nbsim::Particle(pos, vel, 10);
  
  for (int i=0; i<10; i++)
    {mass.intergrateTimestep(1);}

  REQUIRE(expected_pos.isApprox(mass.getPosition()));
  }

TEST_CASE( "Constant Acceleration", "[Exercise 1]" ) 
  {
  Eigen::Vector3d pos(1.0, 1.0, 1.0);
  Eigen::Vector3d vel(0.0, 0.0, 1.0);
  Eigen::Vector3d acc(1.0, 0.0, 0.0);
  Eigen::Vector3d expected_pos(46.0, 1.0, 11.0);
  nbsim::Particle mass = nbsim::Particle(pos, vel, 10);
  mass.setAcceleration(acc);
  for (int i=0; i<10; i++)
    {mass.intergrateTimestep(1);}

  REQUIRE(expected_pos.isApprox(mass.getPosition()));
  }

TEST_CASE( "Centripetal Acceleration", "[Exercise 1]" ) 
  {
  Eigen::Vector3d pos(1.0, 0.0, 0.0);
  Eigen::Vector3d vel(0.0, 1.0, 0.0);
  Eigen::Vector3d acc;
  
  nbsim::Particle mass = nbsim::Particle(pos, vel, 10);

  for (int i=0; i<628; i++)
    {
    acc = -1 * mass.getPosition();
    mass.setAcceleration(acc);  
    mass.intergrateTimestep(0.01);
    //std::cout << i << "\n" << mass.getPosition() << "\n" << std::endl;
    }
  Eigen::Vector3d expected_pos(1.0, 0.0, 0.0);
  //std::cout << mass.getPosition() << "\n" << expected_pos << "\n" << std::endl;
  REQUIRE(expected_pos.isApprox(mass.getPosition(), 0.1));
  }

TEST_CASE( "Circular, Symetric, 2 Body Orbit ", "[Exercise 2]" ) 
  {
  nbsim::MassiveParticle mass3 = nbsim::MassiveParticle(Eigen::Vector3d(1.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.5, 0.0), 1.49828e10);
  nbsim::MassiveParticle mass4 = nbsim::MassiveParticle(Eigen::Vector3d(-1.0, 0.0, 0.0), Eigen::Vector3d(0.0, -0.5, 0.0), 1.49828e10);
  mass3.addAttractor(mass4);
  mass4.addAttractor(mass3);

  int iteration = 0;
  Eigen::Vector3d acc3;
  Eigen::Vector3d acc4;
  double distance = 0;

  for (int i=0; i<628318; i++)
    {
    mass3.calculateAcceleration();
    mass3.intergrateTimestep(0.00001);
    mass4.calculateAcceleration();
    mass4.intergrateTimestep(0.00001);
    
    distance = (mass3.getPosition() - mass4.getPosition()).norm();
    }

  REQUIRE(distance == Approx(2.0).margin(0.01));
  }

TEST_CASE( "Massive Particle Linear Motion", "[Exercise 2]" ) 
  {
  nbsim::MassiveParticle mass3 = nbsim::MassiveParticle(Eigen::Vector3d(1.0, 1.0, 1.0), Eigen::Vector3d(7.0, 0.5, 3.0), 1.49828e10);

  for(int i=0; i<100000; i++)
    {
    mass3.calculateAcceleration();
    mass3.intergrateTimestep(0.0001);
    }
  Eigen::Vector3d expected(71.0, 6, 31.0);
  REQUIRE(mass3.getPosition() == expected);
  }

TEST_CASE( "Energy Calculation", "[Exercise 6]" ) 
  {
  std::vector<nbsim::MassiveParticle> planet_data;
  Eigen::Vector3d pos0(1.0, 0.0, 0.0);
  Eigen::Vector3d vel0(1.0, 0.0, 0.0);

  Eigen::Vector3d pos1(0.0, 1.0, 0.0);
  Eigen::Vector3d vel1(0.0, 1.0, 0.0);

  Eigen::Vector3d pos2(-1.0, 0.0, 0.0);
  Eigen::Vector3d vel2(-1.0, 0.0, 0.0);

  Eigen::Vector3d pos3(0.0, -1.0, 0.0);
  Eigen::Vector3d vel3(0.0, -1.0, 0.0);

  planet_data.push_back(nbsim::MassiveParticle(pos0, vel0 , 1.4983e10));
  planet_data.push_back(nbsim::MassiveParticle(pos1, vel1 , 1.4983e10));
  planet_data.push_back(nbsim::MassiveParticle(pos2, vel2 , 1.4983e10));
  planet_data.push_back(nbsim::MassiveParticle(pos3, vel3 , 1.4983e10));

  nbsim::SystemSim simulate = nbsim::SystemSim();

  simulate.AddSystemAttractors(planet_data, 4);
  double grav_E = simulate.GravatationalEnergy(planet_data, 4);
  double kin_E = simulate.KineticEnergy(planet_data, 4);

  bool pass = false;
  if (grav_E == Approx(-2.5).margin(0.01) & kin_E == Approx(2.0).margin(0.01))
    {pass = true;}

  REQUIRE(pass);
  }