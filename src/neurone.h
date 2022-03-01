#ifndef NEURONE_H
#define NEURONE_H
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>

/*! Possible neuron types */
enum Type{RS, IB, CH, FS, LTS};

constexpr int T(30);

/*!
 * @struct parameters
 *
 * @brief Structure of parameters a,b,c and d of neurons
 */
struct parameters
{
	double param_a;
	double param_b;
	double param_c;
	double param_d;
};

class Network;
/*!
 * @class Neurone
 *
 * @brief Represents a neuron
 *
 */
class Neurone{
public:

	/*!
	 * @brief Constructor
	 *
	 * @param network : network the neuron belongs to
	 * @param type : type of neuron
	 * @param SD : standard deviation of the normal distribution of thalamic input
	 * @param ext : boolean for extension of link's weight (true to activate extension)
	 * @param evo : boolean to display new link's weight in function of time (true to activate)
	 *
	 */
	Neurone(Network* network, Type type, const double& SD, const bool& ext=false, const bool& evo=false);

	/*!
	 * @brief Default destructor
	 */
	virtual ~Neurone();

	/*!
	 * @brief Indicates if the neuron was firing at T-1
	 *
	 * @return True if the neuron was firing, false otherwise
	 */
	bool isFiring() const;

	/*!
	 * @brief Indicates if the neuron is firing at T
	 *
	 * @return True if the neuron is firing, false otherwise
	 */
	bool isFiring_1() const;

	/*!
	 * @brief Calculates the neuron's membrane potential
	 *
	 * @param I : synaptic courant
	 */
	void v(const double& I);

	/*!
	 * @brief Calculates the membrane potential increment for time t+1
	 *
	 * @param I : synaptic courant
	 *
	 * @return Increment for membrane potential at time t+1
	 */
	double dv(const double& I) const;

	/*!
	 * @brief Calculates the neuron's recovery variable
	 */
	void u();

	/*!
	 * @brief Calculates the recovery variable increment for time t+1
	 *
	 * @return Increment for recovery variable at time t+1
	 */
	double du() const;

	/*!
	 * @brief Updates the state of the neuron
	 *
	 * @param I : synaptic courant
	 * @param time : current simulation time
	 */
	void update(const double& I, const double& time);

	/*!
	 * @brief Updates the firing state of time T to now be that of T-1
	 */
	void set_firing();

	/*!
	 * @brief Calculate the neuron's current
	 *
	 * @return The current
	 */
	double courant();

	/*!
	 * @brief Computes the total intensity received from its neighbors
	 *
	 * @return The intensity
	 */
	double intensity() const;

	/*!
	 * @brief Computes the thalamic input on the neuron
	 *
	 * @return The thalamic intput
	 */
	double inputthalamique() const;

	/*!
	 * @brief Searches if a link exists with a given neuron
	 *
	 * @param index : the index of the other neuron
	 *
	 * @return True if the link exists, false otherwise
	 */
	bool link_exist(const size_t& n) const;
	/*!
	 * @brief Searches if a link exists for a given neuron
	 *
	 * @param the pointer of a given neuron
	 *
	 * @return True if the link exists, false otherwise
	 */
	bool link_exist(Neurone* n) const;

	/*!
	 * @brief Adds a pair neighboring neuron - link strenght
	 *
	 * @param neuron : the neuron to add
	 * @param strenght : link strenght
	 *
	 * @return True if the neuron was added, false otherwise
	 */
	bool add_neurone(Neurone* neuron, const double& strenght);

	/*!
	 * @brief Writes the number of steps between each spike
	 *
	 * @param file : output stream
	 */
	void after_spike(std::ofstream& file);

  /*!
	 * @brief evolution of the link strengh
	 */
	void link_Evo(const double& dt);

	/*!
	 * @brief Prints the values of vt,ut and I for the phase plot in an output stream
	 *
	 * @param file : output stream
	 */
	void printOut(std::ofstream& file);

	/*!
	 * @brief Gives the index of each neighboring neuron paired with the link's strenght
	 *
	 * @return Multimap of index - strenght pairs
	 */
	std::multimap<size_t,double> getLinks() const;

	/*!
	 * @brief Gives the neighboring neurons with their link's strenght
	 *
	 * @return A multimap of neuron - link strenght pairs
	 */
	std::multimap<Neurone*,double> neu_vois();

	/*!
	 * @brief Gives the number of links of the neuron
	 *
	 * @return The number of links
	 */
	size_t getNumberLinks() const;

	/*!
	 * @brief Give the neighbors of the neuron
		 */
	std::vector<size_t> getVoisins() const;

	/*!
	 * @brief Simple getter for the a,b,c and d attributes
	 *
	 * @return Structure of paramates with the attributes
	 */
	parameters getparam() const;

	/*!
	 * @brief Gives the value of the m attribute
	 *
	 * @return The value of the attribute
	 */
	double getM() const;

	/*!
	 * @brief Gives the value of the r attribute
	 *
	 * @return The value of the attribute
	 */
	double getr() const;

	/*!
	 * @brief Gives the value of the ut attribute
	 *
	 * @return The value of the attribute
	 */
	double getut() const;

	/*!
	 * @brief Gives the value of the ut_1 attribute
	 *
	 * @return The value of the attribute
	 */
	 double getut_1() const;

	/*!
	 * @brief Gives the value of the vt attribute
	 *
	 * @return The value of the attribute
	 */
	double getvt() const;

	/*!
	 * @brief Gives the value of the vt_1 attribute
	 *
	 * @return The value of the attribute
	 */
	double getvt_1() const;

	/*!
	 * @brief Gives the index of the neuron in the network
	 *
	 * @return The index
	 */
	size_t get_num() const;

	/*!
	 * @brief Gives the last time at wich the neuron was firing
	 *
	 * @return The time
	 */
	double get_tlast() const;

	/*!
	 * @brief Gives the type of the neuron
	 */
	Type getType() const;

	/*!
	 * @brief Sets the value of the vt attribute
	 *
	 * @param new_vt : the new value of the attribute
	 */
	void setvt(const double& new_vt);

	/*!
	 * @brief Sets the value of the ut attribute
	 *
	 * @param new_ut : the new value of the attribute
	 */
	 void setut(const double& new_ut);

	/*!
	 * @brief Sets the value of the w attribute
	 *
	 * @param new_w : the new value of the attribute
	 */
	void set_w(const double& new_w);

	/*!
	 * @brief Activates the project extension if specified by the user
	 *
	 * @param extension : boolean specified by user, if true activates extension
	 */
	void set_ext(const bool& extension);

	/*!
	 * @brief Sets the value of the num attribute and open the associatied file if extension is on
	 *
	 * @param new_num : new value of the attribute
	 */
    void set_num(const size_t& new_num);

	/*!
	 * @brief Display the evolution of the link's force in function of time
	 */
	void poids(double dt) const;

	/*!
	 * @brief Enables to open the necessary files to display the force of the links for the extension
	 */
	 void files() const;


protected:

	Network* network; /*! network the neuron belongs to */

	std::multimap<Neurone*,double> neurones_voisins; /*! neighboring neurons linked with their link strenght */

	size_t num; /*! index of the neuron in the network */

	double a;	/*! recovery time */
	double b;   /*! sensitivity */
	double c;	/*! after spike value of membrane potential */
	double d;	/*! after spike value of recovery variable */
	double r;   /*! uniformly distributed random variable */
	double m;	/*! multiplicative factor of the current */
	double w;   /*! multiplicative factor of noise */
	double SD;  /*! standard deviation of the normal distribution */

	double f;		/*! strenght of link at time t */
	double f_1; 	/*! strenght of link at time t+1 */
	bool firing_T; 	/*! if the neuron is firing at time t-1 */
	bool firing_T1; /*! if the neuron is firng at time t */

	double vt; 		/*! potential at time t-1 */
	double vt_1;	/*! potentital at time t */
	double ut; 		/*! recovery variable at time t-1 */
	double ut_1; 	/*! recovery variable at time t */
	double I; 		/*! current */
	Type type; 		/*! neuron type */

  size_t compteur;
  std::vector<double> time_spikes;

  double a1; /*! link evolution parameter */
  double a2; /*! link evolution parameter */
  double b1; /*! link evolution parameter */
  double b2;	/*! link evolution parameter */
  int t1;	/*! link evolution parameter */
  int t2;	/*! link evolution parameter */

  bool ext; /*! boolean for extension of link's weight */
  bool evo; /*! boolean to display new link's weight */

};
#endif
