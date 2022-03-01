#include <gtest/gtest.h>
#include "../src/network.h"

using namespace std;
typedef std::multimap<size_t,double>::iterator mit;

class NetworkTest : public ::testing::Test {
protected:

  void SetUp() override
  {}

 Network network;

};

TEST_F(NetworkTest, initialize)
{
	EXPECT_EQ(false, network.initialize(10,2,10));
	EXPECT_EQ(false, network.initialize(90,0.8,-1));
	EXPECT_EQ(false, network.initialize(10,-0.2,10));

	network.initialize(50,0,1);
	EXPECT_EQ(true, network.initialize(50,0,1));
	EXPECT_EQ(network.size(),50);
	EXPECT_EQ(network.getpE(),0);
	EXPECT_EQ(network.getConnectivity(),1);

	network.initialize(100,0.5,3);
	EXPECT_EQ(true, network.initialize(100,0.5,3));
	EXPECT_EQ(network.size(),100);
	EXPECT_EQ(network.getConnectivity(),3);
	EXPECT_EQ(network.getnE(),50);


	network.initialize(12,1, 2.3);
	EXPECT_EQ(true, network.initialize(12,1,2.3));
	EXPECT_EQ(network.size(),12);
	EXPECT_EQ(network.getConnectivity(),2.3);
	EXPECT_EQ(network.getnE(),12);


	network.initialize(100,0.22,3.4,0.33,0.1,0.7); ///33% de RS, 10% de CH et 70% de FS
	EXPECT_EQ(true,network.initialize(100,0.22,3.4,0.33,0.1,0.7));
	EXPECT_EQ(network.size(),100);
	EXPECT_EQ(network.getnE(),22);
	EXPECT_EQ(network.getConnectivity(),3.4);

	EXPECT_NEAR(network.count_type(RS),7,1);
	EXPECT_NEAR(network.count_type(CH),2,1);
	EXPECT_NEAR(network.count_type(IB),13,1);
	EXPECT_NEAR(network.count_type(FS),54,1);
	EXPECT_NEAR(network.count_type(LTS),23,1);


	network.initialize(300,0.4,7,0.1,0.7,0.6); /// 10% de RS ,70% de CH et 60% de Fs
	EXPECT_EQ(true, network.initialize(300,0.4,7,0.1,0.7,0.6));
	EXPECT_EQ(network.size(),300);
	EXPECT_EQ(network.getConnectivity(),7);
	EXPECT_EQ(network.getpE(),0.4);
	EXPECT_EQ(network.getnE(),120);

	EXPECT_NEAR(network.count_type(RS),12,1);
	EXPECT_NEAR(network.count_type(CH),84,1);
	EXPECT_NEAR(network.count_type(IB),24,1);
	EXPECT_NEAR(network.count_type(FS),108,1);
	EXPECT_NEAR(network.count_type(LTS),72,1);

}

TEST_F(NetworkTest, connect) {
	network.initialize(12, 0.5, 3);

	EXPECT_EQ(network.count_links(),0);

    bool trylink = network.add_link(0,0);
    bool linkexist = network.exist_link(0,0);

    EXPECT_FALSE(trylink);
    EXPECT_FALSE(linkexist);

    trylink = network.add_link(-1,10);
    linkexist = network.exist_link(2,10);

    EXPECT_FALSE(trylink);

    trylink = network.add_link(9,100);
    linkexist =network.exist_link(9,1122);

    EXPECT_FALSE(trylink);
    EXPECT_FALSE(linkexist);

	network.initialize(20,0.5,2);	///taille=20; proportion=0.5 ; connectivité 2
	EXPECT_EQ(network.size(),20);
    network.connect(2);

    for(size_t i(0); i<(network).size() ; ++i)
    {
		EXPECT_NEAR(network.getNeurone(i)->getNumberLinks(),network.getConnectivity(),15);
	}

    network.initialize(4,0.6,0);
    network.connect(0);

    for(size_t i(0); i<network.size() ; ++i)
    {
		EXPECT_NEAR(network.getNeurone(i)->getNumberLinks(),network.getConnectivity(),4);
	}

}



TEST_F(NetworkTest, neighbors)
{
	(network).initialize(20, 0.5, 4);
	(network).connect(4);

	for( size_t i(0); i<network.size(); ++i)
	{
		vector<size_t> voisins((network.getNeurone(i))->getVoisins());
		sort (voisins.begin(),voisins.end());

		vector<size_t> vois(network.neighbors(i));
		sort (vois.begin(),vois.end());

		EXPECT_EQ(voisins,vois);
	}

}

TEST_F(NetworkTest, connections)
{
	network.initialize(100, 0.3, 5);			///taille=100, proportion=0.3, connectivité=5
	int counter(0);

	for( auto& neuron : network.getNeurones() )
	{
		counter+=neuron->getNumberLinks();
	}
	EXPECT_EQ(network.count_links(),counter);
}
