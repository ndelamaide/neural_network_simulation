#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <map>
#include "neurone.h"
#include "excitateur.h"
#include "inhibiteur.h"

/*!
 * @class Network
 *
 * @brief Represents a network of neurons with unidirectional links
 *
 */
class Network{
public:
 /*!
	* @brief Default constructor
	*/
	Network();

 /*!
	* @brief Constructor of the class
	*
	* @param NN : Number of neurons in the Network
	* @param p : proportion of excitatory neurons
	* @param connectivity : average connectivity of the neurons
	* @param rs : proportion of RS neurons
	* @param ch : proportion of CH neurons
	* @param fs : proportion of FS neurons
	* @param SDe : standard deviation of the normal distribution of the thalamic input for excitators
	* @param SDi : standard deviation of the normal distribution of the thalamic input for inhibitors
	* @param ext : boolean for activation of the extension of links' weight (true = activated)
	*/
	Network(const size_t& NN, const double& p , const double& connectivity, const double& rs, const double& ch, const double& fs,
	 const double& SDe=1, const double& SDi=1, const bool& ext=false, const bool& evo=false);

	/*!
	 * @brief Default destructor
	 */
	~Network();

	/*!
 	* @brief Constructor of the class
 	*
 	* @param NN : Number of neurons in the Network
 	* @param p : proportion of excitatory neurons
 	* @param connectivity_ : average connectivity of the neurons
 	* @param rs : proportion of RS neurons
 	* @param ch : proportion of CH neurons
 	* @param fs : proportion of FS neurons
 	*/
	bool initialize(const size_t& NN,const double& p,const double& connectivity_, const double& rs =0.33, const double& ch = 0.33, const double& fs=0.5);

	/*!
	 * @brief Adds a unidirectional link between two neurons
	 *
	 * @param a : the index of the neuron to connect
	 * @param b : the index of the target neuron
	 *
	 * @return Success the link was succesfully inserted (true if both neurones exist and the link did not exist yet)
	 */
	bool add_link(const size_t& a, const size_t& b);

	/*!
	 * @brief Boolean to know if a link between two neurons already exist
	 *
	 * @param a : the index of the first neuron
	 * @param b : the index of the second neuron
	 *
	 * @return True if the link between a and b already exist, false otherwise
	 */
	bool exist_link(const size_t& a, const size_t& b);

  /*!
   * @brief Updates the state of the network
	 *
	 * @param time : current simulation time
   */
	void update(const double& time);

	/*!
	 * @brief Creates random connections between neurons: each neurons *n* will be linked with *degree(n)* to
	 * other neurons (randomly chosen),
	 * where *degree(n)* is Poisson-distributed.
	 * All previous links are erased first
	 *
	 * @param mean : the average of the Poisson distribution
	 *
	 * @return Number of links created
	 */
	size_t connect(const double& mean);

	/*!
	 * @brief Calculates the synaptic courant of a neuron
	 *
	 * @param index : index of the neuron
	 *
	 * @return Courant of the neuron
	 */
	double courant(const size_t& index);

	/*!
	 * @brief Test if a given neuron exists
	 *
	 * @param index : index of the neuron
	 *
	 * @return True if the neuron exists, false otherwise
	 */
	bool neurone_existant(const size_t& index) const;

	/*!
	 * @brief All linked neurons of a given neuron
	 *
	 * @param index : index of the neuron
	 *
	 * @return neighbors : a vector containing all the neurons linked to neuron n
	 */
	std::vector<size_t> neighbors(const size_t& index) const;

	/*!
	 * @brief Gives the total number of links
	 *
	 * @return Number of links
	 */
	size_t count_links() const;

	/*!
	 * @brief Gives the number of neurons of a specified type
	 *
	 * @param type : type of the neurons
	 *
	 * @return Number of neurons
	 */
	size_t count_type(Type type) const;

	/*!
	 * @brief Number of neurons in the network
	 *
	 * @return Number of neurons in the network
	 */
	size_t size() const;

	/*!
	 * @brief Gives the pointer on a given neuron
	 *
	 * @param index : index of the neuron
	 *
	 * @return The pointer
	 */
	Neurone* getNeurone(const size_t& index);

	/*!
	 * @brief Gives all the neurons composing the network
	 *
	 * @return Vector of all neurons
	 */
	std::vector<Neurone*> getNeurones() const;

	/*!
	 * @brief Gives all the neurons tracked for the phase plot
	 *
	 * @return Vector of tracked neurons
	 */
	std::vector<Neurone*> getTrack() const;
	/*!
	 * @brief Gives of the connectivity of neurons
	 *
	 * @return Connectivity
	 */
	double getConnectivity() const;

	/*!
	 * @brief Gives the proportion of excitatory neurons in the network
	 *
	 * @return Proportion of excitatory neurons
	 */
	double getpE() const;

	/*!
	 * @brief Gives the number of excitatory neurons in the network
	 *
	 * @return Number of excitatory neurons
	 */
	double getnE() const;

	/*!
	 * @brief Gives the number of inhibitory neurons in the network
	 *
	 * @return Number of inhibitory neurons
	 */
	double getnI() const;

	/*!
	 * @brief Gives the standard deviation of the normal distribution of the thalamic
	 * input for excitatory neurons
	 *
	 * @return Standard deviation
	 */
	double getSDe() const;

	/*!
	 * @brief Gives the standard deviation of the normal distribution of the thalamic
	 * input for inhibitory neurons
	 *
	 * @return Standard deviation
	 */
	double getSDi() const;

	/*!
	 * @brief display a message of the start of the program
	 */
	void start_co() const;
	/*!
	 * @brief It enables to known the loading of the program
	 */
	void loading_co(size_t k, size_t n) const;

	/*!
	 * @brief It enables to known the loading of the program
	 */
	void end_co() const;

private:


	double SDe; /*!Standard deviation of the normal distribution for the thalamic input for exitators*/
	double SDi; /*!Standard deviation of normal distribution for the thalamic input for inhibitors*/

	double connectivity; 				/*! Connectivity */

	double pE; 							/*! Proportion of excitatory neurons */

	size_t nRS;							/*! Number of RS neurons */
	size_t nCH; 						/*! Number of CH neurons */
	size_t nIB; 						/*! Number of IB neurons */
	size_t nFS; 						/*! Number of FS neurons */
	size_t nLTS;						/*! Number of LTS neurons */

	std::vector<Neurone*> neurones; 	/*! All neurons of the network */
	std::multimap<size_t,size_t> liens; /*! All connection between neurons */
	std::vector<Neurone*> track; 		/*! Neurons tracked for the phase plot */

	bool ext;							/*! Store the value that indicate if the user choose to use the link extension. */
	bool evo_l;						/*! Store the value that indicate the display of the neurons links in function of time*/
};
#endif
