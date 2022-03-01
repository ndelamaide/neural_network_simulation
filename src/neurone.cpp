#include "neurone.h"
#include "random.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <ostream>
#include "network.h"

using namespace std;

Neurone::Neurone(Network* network,Type t, const double& SD, const bool& ext, const bool& evo)
: network(network)
	,b(0.2)
	,r(RNG.normal())
	,SD(SD)
	,firing_T(false)
	,firing_T1(false)
	,vt(-65)
	,vt_1(0)
	,ut(b*vt)
	,ut_1(0)
	,I(0)
	,type(t)
	,compteur(0)
	,a1(20)
	,a2(-13)
	,b1(-12)
	,b2(17)
	,t1(3)
	,t2(4)
	,ext(ext)
	,evo(evo)

{
	if (vt< T) firing_T1=false;
	else firing_T1 =true;

	switch(type)
	{
		case FS: 
		case LTS:
		w=2;
		break; 
		case RS: 
		case IB: 
		case CH: 
		default: 
		w=5; 
		break;
	}
}

Neurone::~Neurone()
{
	neurones_voisins.clear();
	network=nullptr;
}

bool Neurone::isFiring() const
{ 	return firing_T;}

bool Neurone::isFiring_1() const
{ 	return firing_T1;}

void Neurone::v(const double& I)
{	vt_1= vt + dv(I);}

double Neurone::dv(const double& I) const
{ 	return (0.04 * vt * vt + 5 * vt + 140 - ut + I)*0.5  ; }

void Neurone::u()
{ 	ut_1 = ut +du(); }

double Neurone::du() const
{ 	return (a * b * vt - a * ut); }

void Neurone::update(const double& I, const double& time)
{
	if(ext) link_Evo(time);
	if(evo) poids(time);
	v(I);
	int deux(time*2);
	if(deux%2==0 or deux==0) u();
    if(vt>30)
    {
		firing_T1=true;
		vt_1=c;
		ut_1=ut+d;
		time_spikes.push_back(time);
	} else firing_T1=false;

	vt=vt_1;
    ut=ut_1;
}

void Neurone::set_firing()
{
	firing_T = firing_T1;
	firing_T1=false;
}

double Neurone::courant()
{
	I=inputthalamique()+intensity();
	return I;
}

double Neurone::intensity() const
{
	double somme=0;
	for(auto i: neurones_voisins)
	{
		if(i.first!=nullptr && i.first->isFiring()) somme+=i.first->getM()*i.second;
	}
	return somme;
}

double Neurone::inputthalamique() const
{ 	return w*RNG.normal(0,SD); }

bool Neurone::link_exist(const size_t& n) const
{ 
	for(auto e : neurones_voisins) if(e.first->get_num()==n) return true;
	return false;
	
}

bool Neurone::link_exist(Neurone* n) const
{
	if(neurones_voisins.find(n)!=neurones_voisins.end()) return true;
	return false;
}


bool Neurone::add_neurone(Neurone* n, const double& strenght)
{	
	if((n!=nullptr && !(strenght>1 || strenght<0 )) && !link_exist(n))
	{
	neurones_voisins.insert(make_pair(n,strenght));
	return true;
	}
	return false;
}

void Neurone::after_spike(ofstream& file)
{
	switch(type){
		case FS:  file << "FS" << endl;
		break;
		case LTS: file << "LTS" << endl;
		break;
		case RS:  file << "RS" << endl;
		break;
		case IB:  file << "IB" << endl;
		break;
		case CH:  file << "CH" << endl;
		break;
		default:
		break;
	}
	if(time_spikes.empty()) file<< "Never firing ";
	else{
			file << "firing time: ";
			for(size_t i(0); i<time_spikes.size() ; ++i)
			{ file << time_spikes[i] << " " ; }
		}
}

void Neurone::link_Evo(const double& dt)
{
	
	double q;
	for(multimap<Neurone*, double>::iterator it=neurones_voisins.begin(); it!=neurones_voisins.end(); ++it)
	{
		double X(0);
		double Y(0);
		double tl=get_tlast();
		double tlast=(it->first)->get_tlast();
		if(isFiring())
		{
			X=X+exp((tlast-dt)/t1);
			Y=Y*exp((dt-tl)/t2);
			it->second=it->second+b1+b2*X;
		}
		if((it->first)->isFiring())
		{
			Y=Y+exp((tl-dt)/t2);
			X=X*exp((dt-tlast)/t1);
			it->second=it->second+a1+a2*Y;
		}

		q=RNG.uniform_double();
		it->second=abs((1-q*0.5)*it->second);
		}
	
}

void Neurone::printOut(ofstream &file)
{
	file.setf(ios::left);
	file << "	"<< vt << "	" << ut << "	" << I;
}

multimap<size_t, double> Neurone::getLinks() const
{
	multimap<size_t,double> l;
	for(auto e : neurones_voisins)
	{
		l.insert(make_pair(e.first->get_num(),e.second));
	}
	return l;
}

multimap<Neurone*,double> Neurone::neu_vois()
{ 	return neurones_voisins; }

size_t Neurone::getNumberLinks() const
{ 	return neurones_voisins.size(); }


vector<size_t> Neurone::getVoisins() const
{
	vector<size_t> voisins;
	for(auto e:neurones_voisins)
	{voisins.push_back(e.first->get_num());}
	return voisins;
}

parameters Neurone::getparam() const
{
	parameters values;
	values.param_a = a ;
	values.param_b = b ;
	values.param_c = c ;
	values.param_d = d ;

	return values;
}

double Neurone::getM()    const { return m;  }
double Neurone::getr()    const { return r;  }
double Neurone::getut()   const { return ut; }
double Neurone::getut_1() const { return ut_1; }
double Neurone::getvt()   const { return vt; }
double Neurone::getvt_1() const { return vt_1; }

size_t Neurone::get_num() const
{ 	return num; }

double Neurone::get_tlast() const
{
	if(time_spikes.empty()) return 0;
	else return time_spikes.back();
}

Type Neurone::getType() const
{ return type; }

void Neurone::setvt(const double& new_vt)
{ 	vt = new_vt; }

void Neurone::setut(const double& new_ut)
{	ut = new_ut; }

void Neurone::set_w(const double& new_w)
{	w=new_w; }

void Neurone::set_ext(const bool& extension)
{ 	ext=extension; }

void Neurone::set_num(const size_t& new_num)
{	num=new_num;
	if(evo) files(); 
}

void Neurone::files() const
{
	string s="../results/neurone" +to_string(num) +".txt";
	ofstream file(s);
	file.close();
	file.open(s,ios::out|ios::app);
	file << "NEURONE:" << num << endl;
	file.close();
}
void Neurone::poids(double dt) const
{
	ofstream file;
	
	string s="../results/neurone" +to_string(num) +".txt";
	file.open(s,ios::out|ios::app);
	if(dt==0) file << "Nombre de connexions: " << neurones_voisins.size() << endl;
	file << "step" << dt<< endl;
	for(auto a : neurones_voisins)
	{
		file <<  "neurone[" << a.first->get_num() << "]"  << "   force=" << a.second;
		switch(a.first->getType())
		{
		case FS: file << " FS";
		break;
		case LTS: file << " LTS";
		break;
		case RS: file << " RS";
		break;
		case IB: file << " IB";
		break;
		case CH: file  << " CH";
		break;
		}
		file << endl;
	}
	file << endl;
	file.close();
}
