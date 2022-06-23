#include <iostream>
#include <algorithm>
#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include "nbsimMassiveParticle.h"

namespace nbsim 
{

double MassiveParticle::getMu() const
    {   
    return mass * (6.6743e-11);
    };

void MassiveParticle::addAttractor(nbsim::MassiveParticle adding_attractor)
    {
    attractors.push_back(adding_attractor);
    };

std::vector<nbsim::MassiveParticle> MassiveParticle::getAttractors()
    {
    return attractors;
    }

void MassiveParticle::removeAttractor(nbsim::MassiveParticle removing_attractor)
    {
    for (int i = 0; i<attractors.size(); i++) //Search attracttors for the removing_attractor element. 
        {
        if (attractors[i].getPosition() == removing_attractor.getPosition())
            {
            attractors.erase(attractors.begin() + i);
            }
        else {continue;}
        }
    };

void MassiveParticle::calculateAcceleration()   //Serial calculate acceleration.
    {   
    Eigen::Vector3d X_position = getPosition();
    Eigen::Vector3d acceleration(0,0,0);
    Eigen::Vector3d ri;
    double Mu;
    double scaler;

    for (auto attractor : attractors)   //Loop through attractors and take the needed parameters from each mass.
        {   
        ri = X_position - attractor.getPosition();
        
        double Mu = attractor.getMu();

        double scaler = -Mu * 1/(ri.dot(ri));

        acceleration += scaler*ri;
        }
    setAcceleration(acceleration);
    }

void MassiveParticle::calculateAcceleration(bool parallel)  //Parallel acceleration calculation.
    {   
    Eigen::Vector3d X_position = getPosition();
    Eigen::Vector3d acceleration(0.0, 0.0, 0.0);
    Eigen::Vector3d local_acc(0.0, 0.0, 0.0);   //Introduce intermediary variable.
    Eigen::Vector3d ri;
    double Mu;
    double scaler;
    
    //Reduce acceleration so it can be summed at the end.
    #pragma omp parallel private(local_acc)
        {
        
        //Prallel for loop with each thread taking ordered iterations.
        #pragma omp for schedule (static, 1)
        for (auto attractor : attractors)
            {   
            ri = X_position - attractor.getPosition();
            Mu = attractor.getMu();
            scaler = -Mu * 1/(ri.dot(ri));
            local_acc += scaler*ri;
            }
        
        //Wait until all threads are complete to here, and allow through one-at-a-time.
        #pragma omp critical
        acceleration += local_acc;
        }
    setAcceleration(acceleration);
    }
}