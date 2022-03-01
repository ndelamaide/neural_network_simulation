#include "network.h"
#include <iterator>
#include <algorithm>
#include <exception>
#include <iostream>
#include "random.h"
#include "math.h"
#include <fstream>

using namespace std;

Network::Network(const size_t& NN, const double& p , const double& connectivity, const double& rs,
 const double& ch, const double& fs,const double& SDe, const double& SDi, const bool& ext, const bool& evo)
: SDe(SDe),SDi(SDi),connectivity(connectivity),ext(ext),evo_l(evo)
{
	if(initialize(NN,p,connectivity,rs,ch,fs)) connect(connectivity);
}

Network::Network()
:SDe(1), SDi(1) , ext(false), evo_l(false)
{}

Network::~Network(){

	for(auto element:neurones){
		delete element;
		element=nullptr;
	}
	neurones.clear();
}

bool Network::initialize(const size_t& NN, const double& p, const double& connectivity_, const double& rs, const double& ch, const double& fs)
{

	if(p>1 || p<0 || connectivity_<0 || connectivity_>NN ) return false;

	for(auto* element :neurones)
	{
		delete element;
		element=nullptr;
	}

	neurones.clear();
	liens.clear();
	pE=p;
	connectivity=connectivity_;

	size_t n_e((p*NN));
	size_t n_i((NN-n_e));

	nRS=(rs*n_e);
	nCH=(ch*n_e);
	nIB=(n_e-nRS-nCH);
	nFS=(fs*n_i);
	nLTS=(n_i-nFS);

	for(size_t i(0); i< nRS ;++i) neurones.push_back(new Excitateur(this,RS,SDe,ext,evo_l));
	for(size_t i(0); i< nCH ;++i) neurones.push_back(new Excitateur(this,CH,SDe,ext,evo_l));
	for(size_t i(0); i< nIB ;++i) neurones.push_back(new Excitateur(this,IB,SDi,ext,evo_l));
	for(size_t i(0); i< nFS ;++i) neurones.push_back(new Inhibiteur(this,FS,SDi,ext,evo_l));
	for(size_t i(0); i< nLTS;++i) neurones.push_back(new Inhibiteur(this,LTS,SDi,ext,evo_l));
	for(size_t i(0); i< size();++i)
	{
		 neurones[i]->set_num(i);
	}
	if(nRS!=0){
		 track.push_back(neurones[0]);
	 }else { track.push_back(nullptr); }
	if(nCH!=0){
			track.push_back(neurones[nRS]);
		}else { track.push_back(nullptr); }
	if(nIB!=0){
			track.push_back(neurones[nRS+nCH]);
		}else { track.push_back(nullptr); }
	if(nFS!=0){
			track.push_back(neurones[nRS+nCH+nIB]);
		}else { track.push_back(nullptr); }
	if(nLTS!=0){
			track.push_back(neurones[nRS+nCH+nIB+nFS]);
		}else { track.push_back(nullptr); }
	return true;
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	if(a==b || (exist_link(a,b)) || (a>neurones.size()) || (b>neurones.size())) return false;
	else liens.insert(make_pair(a,b)); return true;
}


bool Network::exist_link(const size_t& a, const size_t& b)
{
  if(!(a==b || a>neurones.size() || b>neurones.size() || a>neurones.size()))
	{
		multimap<Neurone*, double> l(neurones[a]->neu_vois());
		if(l.find(neurones[b])!=l.end()) return true;
	}
	return false;
}

void Network::update(const double& time)
{
	for(size_t i(0); i< neurones.size(); ++i)
	{
		if(neurones[i]!=nullptr)
		{
			 neurones[i]->update(courant(i),time);
			 neurones[i]->set_firing();
		}
		else throw string("Neurone does not exist");
	}
}

size_t Network::connect(const double& mean)
{
	liens.clear();
	vector<size_t> tab(neurones.size());
	for(size_t i(0); i< neurones.size(); ++i) tab[i]=i;

	size_t somme=0;
	start_co();
	for (size_t l(0); l<neurones.size() ; ++l)
	{
		loading_co(l,neurones.size());
		size_t deg=RNG.poisson(mean);
		RNG.shuffle(tab);
		for(size_t k(0); k<deg ;++k)
		{
			if(add_link(l,tab[k]))
			{
				++somme;
				neurones[l]->add_neurone(neurones[tab[k]],RNG.uniform_double(0,1));
			}
			else if(deg<tab.size()) ++deg;
		}
	}
	end_co();
	return somme;
}

double Network::courant(const size_t& index)
{
	if(neurones[index]!=nullptr) return neurones[index]->courant();
	return 0;
}

bool Network::neurone_existant(const size_t& index) const
{	return (index<neurones.size()); }


vector<size_t> Network::neighbors(const size_t& index) const
{
	vector<size_t> neig;
	for (auto at(liens.begin()); at!= liens.end(); ++at)
	{
		if(at->first==index){
		neig.push_back(at->second);
		}
	}
	return neig;
}

size_t Network::count_links() const
{ 	return liens.size(); }

size_t Network::count_type(Type type) const
{
	switch (type) {
    case RS: return nRS; break;
    case CH: return nCH; break;
    case IB: return nIB; break;
    case FS: return nFS; break;
    case LTS: return nLTS; break;
    default: return 0; break;
  }
}

size_t Network::size() const
{ 	return neurones.size(); }

Neurone* Network::getNeurone(const size_t& index)
{
	if(index>size()) return nullptr;
	return neurones[index];
}

vector<Neurone*> Network::getNeurones() const
{ 	return neurones; }

vector<Neurone*> Network::getTrack() const
{ 	return track; }

double Network::getConnectivity() const
{ 	return connectivity; }

double Network::getpE() const
{ 	return pE; }

double Network::getnE() const
{	return nRS+nCH+nIB; }

double Network::getnI() const
{ 	return nFS+nLTS; }

double Network::getSDe() const
{	return SDe; }

double Network::getSDi() const
{	return SDi; }


void Network::start_co() const
{
	cout << "CONNEXION" << endl;
	cout << "[0%]";
}

void Network::loading_co(size_t k,size_t n) const
{
	size_t l=ceil(n*0.1);
	if(k==round(n*0.5)) cout << "[50%]" << flush;
	else if(k%l==0) cout << "=" << flush;
}

void Network::end_co() const
{ 	cout << "[100%]" << endl; }
