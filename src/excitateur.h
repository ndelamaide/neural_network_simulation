#ifndef EXCITATEUR_H
#define EXCITATEUR_H
#include "neurone.h"

/*!
 * @class Excitateur
 *
 * @brief Represents an excitatory neuron
 *
 */
class Excitateur: public Neurone
{
public:

	/*!
	 * @brief Constructor
	 *
	 * @param network : network the neuron belongs to
	 * @param type: type of neuron
	 * @param SD : standard deviation of the normal distribution of thalamic input
	 *
	 */
	Excitateur(Network* network, Type type=RS,const double& SD=1, const bool& extension=false, const bool& linkevo=false);

	/*!
     * @brief Default destructor
     */
	~Excitateur();

};

#endif
