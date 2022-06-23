#ifndef nbsimParticle_h
#define nbsimParticle_h

#include <Eigen/Dense>
namespace nbsim 
{
class Particle
    {
    public:
        Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mass);

        Eigen::Vector3d getPosition() const;
        Eigen::Vector3d getVelocity() const;
        Eigen::Vector3d getAcceleration() const;

        void setPosition(const Eigen::Vector3d &position);
        void setVelocity(const Eigen::Vector3d &velocity);
        void setAcceleration(const Eigen::Vector3d &acceleration);
        void intergrateTimestep(const double &timestep);
        
        void PrintValues();
    protected:
        double mass;

        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
    };

}


#endif