#include "inhibiteur.h"

Inhibiteur::Inhibiteur(Network* network,Type type,const double& SD, const bool& extension, const bool& linkevo)
: Neurone(network,type,SD,extension, linkevo)


{
	switch(type) {
		default:
		a = (0.02+0.08*r);
		b = (0.2+0.05*(1-r));
		break;
		case FS:
		a = 0.1;
		b=(0.2+0.05*(1-r));
		break;
		case LTS:
		a=(0.02+0.08*r);
		b = 0.25;
		break;
	}
	c=(-65.0);
	d=(2.0);
	ut=(b * vt);
	m=-1;
}

Inhibiteur::~Inhibiteur(){}
