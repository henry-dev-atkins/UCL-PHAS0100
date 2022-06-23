
#include "nbsimMassiveParticle.h"
#include "nbsimSystemSimulator.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <vector>


#include <Eigen/Dense>
namespace nbsim 
{
//Constructor for testing.
SystemSim::SystemSim(){}; 

 
SystemSim::SystemSim(std::vector<nbsim::MassiveParticle> &planet_data)
  {                                                                                   //Constructor for Solar System.
  GetSolarSystemData(planet_data);
  AddSystemAttractors(planet_data, planet_data.size());
  }


SystemSim::SystemSim(std::vector<nbsim::MassiveParticle> &planet_data, int n_planets)
  {                                                                                   //Constructor fo Random System.
  GetRandomSystemData(planet_data, n_planets);
  AddSystemAttractors(planet_data, planet_data.size());
  }


void SystemSim::GetSolarSystemData(std::vector<nbsim::MassiveParticle> &planet_data)
  {                                                                                   //Adds the dats from nbsimSolarSystemData.ipp to planet_data vector.
  for (int i = 0; i < 9; i++)
    {
    planet_data.push_back(nbsim::MassiveParticle(nbsim::solarSystemData.at(i).position, nbsim::solarSystemData.at(i).velocity , (nbsim::solarSystemData.at(i).mu)/(6.6743e-11)));
    }
  }


void SystemSim::GetRandomSystemData(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets)
  {
  
  //random generator 2x (r, theta);
  std::random_device random_dev; 
  std::mt19937 generator(random_dev());
  std::uniform_real_distribution<double> r_distruibution(0.4, 40);
  std::uniform_real_distribution<double> theta_distruibution(0, 360);

  double theta;
  double sin_theta;
  double cos_theta;
  double r;
  double inv_sqrt_r;
  
  //Make central Sun type object
  nbsim::MassiveParticle planet_i = nbsim::MassiveParticle(Eigen::Vector3d(0.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0), 6e11);
  planet_data.push_back(planet_i);

  int added = 1;
  double prev;
  while (added < n_planets)
    {
    r = r_distruibution(generator);                                                     //Generate random r & theta.
    inv_sqrt_r = 1/sqrt(r);
    theta = theta_distruibution(generator);

    if (prev == r)                                                                      //Test for repeats, incase r/theta isnt updated.
      {std::cout << "DOUBLES \n";}

    sin_theta = sin(theta);
    cos_theta = cos(theta);

    Eigen::Vector3d pos((r*sin_theta), (r*cos_theta), 0.0);                              //Generate Position and Velocity.
    Eigen::Vector3d vel((-inv_sqrt_r*cos_theta), (inv_sqrt_r*sin_theta), 0.0);
  
    nbsim::MassiveParticle planet_i = nbsim::MassiveParticle(pos, vel, 1.4983e10);       //Add the new planet to planet_data.

    planet_data.push_back(planet_i);
    prev = r; 
    added += 1;
    }
  }
  
void SystemSim::AddSystemAttractors(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets)
  {
  /*
  -Originally, this was planned as folows: at i, j -> j would be added to i and i to j. This means that the loop can go:
        for (int i = 0; i < n_planets; i++)
          {
          for (int j = i+1; j < n_planets; j++)
            {
            if (j <= i) {continue;}
            else {add i to j and j to i}
  -This would be much faster (less loop iterations) however a speedup faster than this was found instead. See README Exercise 2's discussion of CPU calls. 
  */
  for (int i = 0; i < n_planets; i++)
    {
    for (int j = 0; j < n_planets; j++)
      {
      if (j == i)
        {
        continue;
        }
      else
        {
        planet_data[i].addAttractor(planet_data[j]);
        }
      }
    }
  }

double SystemSim::KineticEnergy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets)
  {
  double Ekin = 0;

  //Entering parallel section.
  #pragma omp parallel                        
    {
    //Reduce Ekin within the for loop.
    #pragma omp for reduction(+:Ekin)
    for (int i = 1; i < n_planets; i++)
      {
      Ekin += planet_data[i].getMu() * std::pow(planet_data[i].getVelocity().norm(), 2);
      }
    }
  return 0.5 * Ekin;
  }

double SystemSim::GravatationalEnergy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets)
  {
  double Egrav = 0;
  //Parallel reduction of Egrav.
  #pragma omp parallel for reduction(+:Egrav)
  for (int i = 0; i < n_planets; i++)
    {
    for (int j = 0; j < n_planets; j++)
      {
      /*
      Barrier before the condition. Continue cannot be udes inside a thread, so by incrementing j instead we 'in essence' skip to the next iteration.
      At the end of the loop we then ++j again, bringing us along as expected, simply skipping the j==i iteration as there is no Gravitational self iteration.
      */
      #pragma omp critical
      if (i == j) {j++;}
        
      Egrav += (planet_data[i].getMu() * planet_data[j].getMu()) / ((planet_data[i].getPosition() - planet_data[j].getPosition()).norm());
        
      }
    }
  
  return -0.5 * Egrav;
  }

double SystemSim::Energy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets)
  {
  return KineticEnergy(planet_data, n_planets) + GravatationalEnergy(planet_data, n_planets);
  }

void SystemSim::PrintErrors(const double end_KE, const double start_KE, const double end_GE, const double start_GE, const double start_E, const double end_E)
  {
  std::cout << "Kinetic Energy - Start - End - Error: " << start_KE << " " << end_KE << " " << 100*(end_KE - start_KE)/start_KE << "%" << std::endl;
  std::cout << "Gravitational Energy - Start - End - Error: " << start_GE << " " << end_GE << " " << 100*(end_GE - start_GE)/start_GE << "%" <<std::endl;
  std::cout << "Total Energy Error: " << 100*(end_E - start_E)/start_E << "%" <<std::endl;
  }

void SystemSim::PrintSolarSystemData(std::vector<nbsim::MassiveParticle> &planet_data)
  {
  for (int i = 0; i < planet_data.size(); i++)
    {
    std::cout << "Planet: " << GetPlanetName(i) << "\n";
    planet_data[i].PrintValues();
    std::cout << "\n";
    }  
  }

std::string SystemSim::GetPlanetName(const int i)
  {
  return nbsim::solarSystemData.at(i).name;
  }



}