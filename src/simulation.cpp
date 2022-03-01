#include "simulation.h"
#include <exception>
#include "math.h"

using namespace std;

Simulation::Simulation(const size_t& NN, const double& p , const double& c,const unsigned int& time, const double& rs, const double& ch,
 const double& fs, const double& SDe, const double& SDi, const bool& ext, const bool& evo)
:_network(new Network(NN,p,c,rs,ch,fs, SDe, SDi,ext,evo))
,timemax(time)
{}

Simulation::~Simulation()
{
	delete _network;
	_network=nullptr;
}

void Simulation::run()
{

	files();
	if (_network != nullptr)
	{
		std::ofstream file;
		file.open("../results/1-raster_data.txt",ios::out|ios::app);
		int timestep(1);
		start();
		try{
			for (double time(0); time<timemax; time+=0.5, ++timestep)
			{
				_network->update(time);
				loading(time);
				print(timestep,file);
				printPhases(timestep);
			}
		}catch(std::runtime_error &chaine){ std::cerr << chaine.what() << std::endl; }
		file.close();
		end();
	} else throw string("Network does not exist");
	after_spike();
}

void Simulation::print(const int& timestep, ofstream& file)
{
	file << timestep << "  ";

	for (auto* element : _network->getNeurones())
	{
		if(element!=nullptr)
		{
			if(element->isFiring()) file << 1 << " ";
			else file << 0 << " ";
		}
	}
	file << endl;
}


void Simulation::after_spike() const
{
	ofstream fichier("../results/2-Spike.txt");
	fichier.close();
	fichier.open("../results/2-Spike.txt",ios::out|ios::app);
	for (size_t i(0); i<_network->size(); ++i)
	{
		fichier<< "neurone[" << i <<"] :";
		_network->getNeurone(i)->after_spike(fichier);
		fichier<< endl;
	}
	fichier.close();
}


void Simulation::printPhases(const int& timestep)
{
  try{
		ofstream file;
		file.open("../results/3-neuron_potential.txt",ios::out|ios::app);
		if(file.fail()) throw std::runtime_error("Invalid output file");
    file << timestep;
    for(auto* neuron : _network->getTrack())
  	{
  		if(neuron!=nullptr)
  		{
  			neuron->printOut(file);
  		}
  	}
    file << endl;
		file.close();
	}catch(std::runtime_error &chaine){ std::cerr << chaine.what()<< std::endl; }
}


void Simulation::files() const
{
	ofstream file("../results/1-raster_data.txt");
	file.close();
	ofstream file1("../results/3-neuron_potential.txt");
    if(_network->getTrack()[0]!=nullptr) file1 << "	RS.v 	RS.u	RS.I	";
    if(_network->getTrack()[1]!=nullptr) file1 << "CH.v"<< "	" << "CH.u"<< "	" << "CH.I";
	if(_network->getTrack()[2]!=nullptr) file1 << "	" << "IB.v"<< "	" << "IB.u"<< "	" <<"IB.I";
    if(_network->getTrack()[3]!=nullptr) file1 << "	" << "FS.v" << "	"<< "FS.u" << "	"<< "FS.I";
	if(_network->getTrack()[4]!=nullptr) file1 << "	" << "LTS.v"<< "	" << "LTS.u" << "	"<< "LTS.I";
	file1 << endl;
	file1.close();
}

void Simulation::start() const
{
	cout << "START OF THE SIMULATION" << endl;
	cout << "[0%]" << flush;
}
void Simulation::loading(double t) const
{
	if(t<floor(timemax*0.5))
	{
		int q=ceil(timemax*0.1);
		int k=round(2*t);
		if(k==floor(timemax*0.5)) cout << "[50%]"<<flush;
		else if(round(k%q)==0.0) cout << "=" <<flush;
	}
}

void Simulation::end() const
{
	cout << "[100%]" << endl;
	cout << "END OF THE SIMULATION" << endl;
	cout << "Data are available in the results file" << endl;
}
