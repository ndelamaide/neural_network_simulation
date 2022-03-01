#ifndef INHIBITEUR_H
#define INHIBITEUR_H
#include "neurone.h"

/*!
 * @class Inhibiteur
 *
 * @brief Represents an inhibitory neuron
 *
 */
class Inhibiteur: public Neurone{
public:

  /*!
     * @brief Constructor
     *
     * @param network : network the neuron belongs to
     * @param type : type of neuron
     * @param standard deviation of normal distribution of thalamic input
     *
     */

  Inhibiteur(Network* network, Type type=FS, const double& SD=1, const bool& extension=false, const bool& linkevo=false);


  /*!
   * @brief Default destructor
   */
  ~Inhibiteur();
};


#endif
