#ifndef SIMULATION_H
#define SIMULATION_H
#include <tclap/CmdLine.h>
#include <fstream>
#include "network.h"
#include <iostream>

/*!
 * @class Simulation
 *
 * @brief Controls the simulation of the neural network
 *
 */
class Simulation{
public:

	/*!
	 * @brief Default constructor
	 *
	 * @param NN : Number of neurons in the network
	 * @param p : proportion of excitatory neurons
	 * @param c : average connectivity of the neurons
	 * @param time : duration of the simulation
	 * @param rs : proportion of RS neurons
	 * @param ch : proportion of CH neurons
	 * @param fs : proportion of FS neurons
	 * @param SDe : standard deviation of the normal distribution of the thalamic input for excitators
	 * @param SDi : standard deviation of the normal distribution of the thalamic input for inhibitors
	 * @param ext : boolean for activation of the extension of links' weight (true = activated)
	 */
	 Simulation(const size_t& NN, const double& p , const double& c,const unsigned int& time, const double& rs,
	  const double& ch, const double& fs, const double& SDe, const double& SDi, const bool& ext, const bool& evo);

	/*!
	 * @brief Default destructor
	 */
	~Simulation();

	/*!
	 * @brief Updates every element of the simulation at each timestep
	 */
	void run();

	/*! @brief Write in a fichier at wich time neurons are firing */
	void after_spike() const;

	/*!
	 * @brief Resets the content of each output file
	 */
	void files() const;
	
	/*!
	 * @brief display the beginning of the simulation
	 */
	 void start() const;

	/*!
	 * @brief display the loading of the simulation in the terminal
	 */
	void loading(double t) const;

	/*!
	 * @brief display the end of the simulation
	 */
	void end() const;

private:
	/*!
	 * @brief Writes for all neurons, in the raster_data text file,
	 * if they are firing or not at each time step
	 *
	 * @param timestep : current timestep
	 * @param file : output flow
	 */
	void print(const int& timestep, std::ofstream& file);

	/*!
	 * @brief Writes for all neurons, in the neuron_potential text file,
	 * their values of vt, ut and intensity at each time step
	 *
	 * @param timestep : current timestep
	 */
	void printPhases(const int& timestep);


	Network* _network;		/*! network network we are simulating */
	unsigned int timemax;		/*! number of steps until the end of the simulation */
};

#endif
