#include "simulation.h"
#include "network.h"
#include <tclap/CmdLine.h>
#include "random.h"
#include <iostream>
#include <cstdlib>

RandomNumbers RNG;
Simulation get_input(int argc, char **argv);
using namespace std;


int main(int argc, char **argv) {
	int nerr(0);

	try{
		TCLAP::CmdLine cmd("Neurone Simulation");

		TCLAP::ValueArg<int> nsample("N", "sample_size", "Number of neurons generate", false, 100, "int");
		cmd.add(nsample);

		TCLAP::ValueArg<double> Pex("p", "Pex", "Proportion of excitator neurons", false, 0.5, "double");
		cmd.add(Pex);


		TCLAP::ValueArg<int> time("T", "time", "Lenghth of simulation", false, 100, "int");
		cmd.add(time);

		TCLAP::ValueArg<int> Mconnect("c", "connections", "Mean number of connections between neurons", false, 40, "int");
		cmd.add(Mconnect);

		TCLAP::ValueArg<double> SDe("e" , "sde" , "standard deviation of the normal distribution for the thalamic input for exitators" , false , 1 , "double");
		cmd.add(SDe);

		TCLAP::ValueArg<double> SDi("i" , "sd" , "standard deviation of the normal distribution for the thalamic input for inhibitors" , false , 1 , "double");
		cmd.add(SDi);

		TCLAP::ValueArg<double> rs("r" , "rs" , "proportion of RS neurons" , false , 0.33 , "double");
		cmd.add(rs);

		TCLAP::ValueArg<double> ch("a" , "ch" , "proportion of CH neurons", false , 0.33 , "double");
		cmd.add(ch);

		TCLAP::ValueArg<double> fs("f" , "fs" , "proportion of FS neurons" , false , 0.5 ,  "double");
		cmd.add(fs);

		TCLAP::ValueArg<bool> ext("k" , "ext" , "extension of link's weight" , false , false ,  "bool");
		cmd.add(ext);
		
		TCLAP::ValueArg<bool> evo("l" , "evo" , "display new link's weight in function of time" , false , false ,  "bool");
		cmd.add(evo);
		
		cmd.parse(argc, argv);

		if (nsample.getValue()<1) 					 throw std::string("Number of neurons can't be under 1");
		if (time.getValue()<=0) 					 throw std::string("Time can't be negative or equal to 0");
		if (Mconnect.getValue()<0) 					 throw std::string("Connectivity can't be negative");
		if (Mconnect.getValue()>=nsample.getValue()) throw std::string("Cannot have more connections than neurons, default value for connection is 40.");
		if (Pex.getValue()<0 or Pex.getValue()>1)    throw std::string("Proportion of excitator neurons has to be a number between 0 and 1");
		if (rs.getValue()<0 or rs.getValue()>1) 	 throw std::string("Proportion of RS neurons has to be a number between 0 and 1");
		if (ch.getValue()<0 or ch.getValue()>1) 	 throw std::string("Proportion of CH neurons has to be a number between 0 and 1");
		if (fs.getValue()<0 or fs.getValue()>1) 	 throw std::string("Proportion of FS neurons has to be a number between 0 and 1");
		if (ch.getValue() + rs.getValue()>1)	     throw std::string("Proportion of added CH and RS neurons has to be lower than 1");
		if (SDe.getValue()<0)						 throw std::string("Upper value of normal distribution for the thalamic input for exitators can't be negative");
		if (SDi.getValue()<0)						 throw std::string("Upper value of normal distribution for the thalamic input for inhibitors can't be negative");


		Simulation sim(nsample.getValue(), Pex.getValue() , Mconnect.getValue(), time.getValue(), rs.getValue(), ch.getValue(), fs.getValue(), SDe.getValue(), SDi.getValue(), ext.getValue(), evo.getValue());

		sim.run();

		} catch(TCLAP::ArgException &e) {
				std::cerr << "Error: " + e.error() + " " + e.argId();
					throw 1;
		} catch (std::string e){
		std::cerr << "Incorrect input : "<< e << endl;
		throw 1;
	}
    return nerr;
}
