#ifndef nbsimMassiveParticle_h
#define nbsimMassiveParticle_h

#include <Eigen/Dense>
#include <vector>
#include "nbsimParticle.h"


namespace nbsim 
{
class MassiveParticle : public nbsim::Particle { //Allows use of Particle methods.
public:
    using Particle::Particle;
    double getMu() const;
    void addAttractor(nbsim::MassiveParticle adding_attractor);
    std::vector<nbsim::MassiveParticle> getAttractors();
    void removeAttractor(nbsim::MassiveParticle removing_attractor);
    void calculateAcceleration();
    void calculateAcceleration(bool parallel); //Parallel Version of Calculate Acceleration.
protected:
    double Mu;
    std::vector<nbsim::MassiveParticle> attractors;
    Eigen::Vector3d acceleration;
};

}
#endif