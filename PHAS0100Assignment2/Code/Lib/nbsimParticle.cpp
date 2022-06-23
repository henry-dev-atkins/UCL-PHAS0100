#include <iostream>
#include <Eigen/Dense>

#include "nbsimParticle.h"

namespace nbsim 
{

Particle::Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mass) : position{position}, velocity{velocity}, mass{mass}{}


Eigen::Vector3d Particle::getPosition() const 
{
    return position;
}

Eigen::Vector3d Particle::getVelocity() const 
{
    return velocity;
}

Eigen::Vector3d Particle::getAcceleration() const 
{
    return acceleration;
}

void Particle::setPosition(const Eigen::Vector3d &input_position)
{
    position = input_position;
}

void Particle::setVelocity(const Eigen::Vector3d &input_velocity)
{
    velocity = input_velocity;
}

void Particle::setAcceleration(const Eigen::Vector3d &input_acceleration)
{
    acceleration = input_acceleration;
}

void Particle::intergrateTimestep(const double &timestep)
{   
    position += velocity*timestep;
    setPosition(position);
    acceleration = getAcceleration();
    velocity += acceleration*timestep;
    setVelocity(velocity);
}

void Particle::PrintValues()
{
  std::cout << "Position:" << std::endl;
  Eigen::Vector3d output_pos = getPosition();
  for(int i=0; i<3; i++)
    {std::cout << output_pos[i] << " ";}
  std::cout << std::endl;
  std::cout << "Velocity:" << std::endl;
  Eigen::Vector3d output_vel = getVelocity();
  for(int i=0; i<3; i++)
    {std::cout << output_vel[i] << " ";}
  std::cout << std::endl;
}
}