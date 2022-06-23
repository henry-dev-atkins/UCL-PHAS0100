#ifndef nbsimSystemSimulator_h
#define nbsimSystemSimulator_h


#include <Eigen/Dense>

namespace nbsim 
{
class SystemSim
    {
    public:
        //Contructors for
        SystemSim();                                                                        //Testing.
        SystemSim(std::vector<nbsim::MassiveParticle> &planet_data);                        //SolarSystem.
        SystemSim(std::vector<nbsim::MassiveParticle> &planet_data, int n_planets);         //randomSytem.

        //Used in constructors to construct the planet_data vector, and add attractors.
        void GetRandomSystemData(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets);
        void GetSolarSystemData(std::vector<nbsim::MassiveParticle> &planet_data);
        void AddSystemAttractors(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets);
        
        //Energy calculations.
        double KineticEnergy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets);
        double GravatationalEnergy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets);
        double Energy(std::vector<nbsim::MassiveParticle> &planet_data, const int n_planets);

        //Output functions.
        std::string GetPlanetName(const int i);                                             //String of planet name.
        void PrintSolarSystemData(std::vector<nbsim::MassiveParticle> &planet_data);        //Prints pos/vel of each planet.
        void PrintErrors(const double end_KE, const double start_KE, const double end_GE, const double start_GE, const double start_E, const double end_E);
    };
}

#endif