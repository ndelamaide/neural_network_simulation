#include "excitateur.h"

Excitateur::Excitateur(Network* network,Type type, const double& SD, const bool& extension, const bool& linkevo)
:Neurone(network,type,SD,extension, linkevo)
{
	a = (0.02);
	b= (0.2);
	switch(type)
	{
		default:
		c = (-65+15*r*r);
		d = (2.0+6*(1-r*r));
		break;
		case RS:
		c = -65.0;
		d = 8;
		break;
		case IB:
		c = -55.0;
		d = 4;
		break;
		case CH:
		c = -50.0;
		d = 2;
		break;
	}
	ut=(b * vt);
	m=0.5;
}

Excitateur::~Excitateur(){}
