#include <gtest/gtest.h>
#include "../src/network.h"
#include "../src/neurone.h"
#include "../src/excitateur.h"
#include "../src/inhibiteur.h"
#include "../src/random.h"
RandomNumbers RNG;

using namespace std;


class NeuroneTest : public ::testing::Test
{  };

TEST_F (NeuroneTest, fonctionvTest) {
Inhibiteur inhib(new Network);
Excitateur excit(new Network);


excit.v(48.0);
EXPECT_EQ(-42.5, excit.getvt_1());

excit.v(-12.0);
EXPECT_EQ(-72.5, excit.getvt_1());
EXPECT_EQ(-65, excit.getvt());

inhib.v(126.0);
EXPECT_EQ(-65.0 + (0.04 * (-65.0) * (-65.0) + 5 * (-65.0) + 140 - inhib.getut() + 126.0) * 0.5, inhib.getvt_1());

inhib.v(-2.0);
EXPECT_EQ(inhib.getvt() + (0.04 * inhib.getvt() * inhib.getvt() + 5 * inhib.getvt() + 140 - inhib.getut() - 2.0) * 0.5, inhib.getvt_1());

inhib.v(1949);
EXPECT_EQ(inhib.getvt() + (0.04 * inhib.getvt() * inhib.getvt() + 5 * inhib.getvt() + 140 - inhib.getut() + 1949) * 0.5, inhib.getvt_1());
}


TEST_F (NeuroneTest, fonctiondvTest) {
Inhibiteur inhib(new Network);
Excitateur excit(new Network);

EXPECT_EQ((0.04 * excit.getvt() * excit.getvt() + 5 * excit.getvt() + 140 - excit.getut() + 72.2) * 0.5, excit.dv(72.2));
EXPECT_EQ((0.04 * excit.getvt() * excit.getvt() + 5 * excit.getvt() + 140 - excit.getut() - 122.75) * 0.5, excit.dv(-122.75));
EXPECT_EQ((0.04 * inhib.getvt() * inhib.getvt() + 5 * inhib.getvt() + 140 - inhib.getut()) * 0.5, inhib.dv(0));
EXPECT_EQ((0.04 * inhib.getvt() * inhib.getvt() + 5 * inhib.getvt() + 140 - inhib.getut() + 0.5) * 0.5, inhib.dv(0.5));
}


TEST_F (NeuroneTest, fonctionuTest) {
Inhibiteur inhib(new Network);
Excitateur excit(new Network);

double excit_ut = excit.getut();
excit.u();
EXPECT_EQ(excit_ut + (excit.getparam().param_a * excit.getparam().param_b * excit.getvt() - excit.getparam().param_a * excit_ut), excit.getut());
double excit_ut_2 = excit.getut();
excit.u();
EXPECT_EQ(excit_ut_2 + (excit.getparam().param_a * excit.getparam().param_b * excit.getvt() - excit.getparam().param_a * excit_ut_2), excit.getut());
double inhib_ut = inhib.getut();
inhib.u();
EXPECT_EQ(inhib_ut + (inhib.getparam().param_a * inhib.getparam().param_b * inhib.getvt() - inhib.getparam().param_a * inhib_ut), inhib.getut());
double inhib_ut_2 = inhib.getut();
inhib.u();
EXPECT_EQ(inhib_ut_2 + (inhib.getparam().param_a * inhib.getparam().param_b * inhib.getvt() - inhib.getparam().param_a * inhib_ut_2), inhib.getut());


}


TEST_F (NeuroneTest, fonctionduTest) {
Inhibiteur inhib(new Network);
Excitateur excit(new Network);

EXPECT_EQ((excit.getparam().param_a * excit.getparam().param_b * excit.getvt() - excit.getparam().param_a * excit.getut()), excit.du());
EXPECT_EQ((inhib.getparam().param_a * inhib.getparam().param_b * inhib.getvt() - inhib.getparam().param_a * inhib.getut()), inhib.du());

inhib=nullptr;
excit=nullptr;
}

TEST_F (NeuroneTest, fonctionisFiringTest) {
Inhibiteur inhib(new Network);
Excitateur excit(new Network);

EXPECT_EQ(false, excit.isFiring());
EXPECT_EQ(false, inhib.isFiring());

EXPECT_EQ(false, excit.isFiring_1());
EXPECT_EQ(false, inhib.isFiring_1());

excit.setvt(-90);
excit.update(8,0.5);
EXPECT_EQ(false, inhib.isFiring());
EXPECT_EQ(false, excit.isFiring_1());

inhib.setvt(31);
inhib.update(13,9);
EXPECT_EQ(false, inhib.isFiring());
EXPECT_EQ(true, inhib.isFiring_1());

inhib.setvt(41);
inhib.update(2,3);
inhib.set_firing();
EXPECT_EQ(true, inhib.isFiring());
EXPECT_EQ(false, inhib.isFiring_1());

Inhibiteur inhib1(new Network,IB);
Excitateur excit1(new Network,FS);

EXPECT_EQ(false, excit1.isFiring());
EXPECT_EQ(false, inhib1.isFiring());

inhib  =nullptr;;
excit  =nullptr;
inhib1=nullptr;
excit1=nullptr;
}

TEST_F (NeuroneTest, fonction_add_neurone)
{
Excitateur excit(new Network);
Inhibiteur inhib(new Network);
Network net;
net.initialize(20,0.6,3);

size_t taille_initiale = excit.getNumberLinks();
excit.add_neurone(net.getNeurone(4),0.3);

EXPECT_EQ(taille_initiale + 1, excit.getNumberLinks());

for(auto e : net.getNeurones())
{
	double d=RNG.uniform_double(0,1);
	inhib.add_neurone(e,d);
}

EXPECT_EQ(inhib.getNumberLinks(),net.size());


excit.add_neurone(net.getNeurone(2),0.7);
EXPECT_TRUE(excit.link_exist(2));
EXPECT_FALSE(excit.link_exist(19));

inhib.add_neurone(net.getNeurone(3),0.8);
EXPECT_TRUE(inhib.link_exist(3));
EXPECT_FALSE(inhib.add_neurone(net.getNeurone(2),-0.9));
EXPECT_FALSE(inhib.add_neurone(net.getNeurone(10000),-9));

Inhibiteur i1(new Network);
Excitateur e1(new Network);
Excitateur e2(new Network);


EXPECT_FALSE(i1.add_neurone(net.getNeurone(1),-10));
i1.add_neurone(net.getNeurone(3),0.7);
EXPECT_TRUE(i1.link_exist(net.getNeurone(3)));
EXPECT_FALSE(i1.link_exist(net.getNeurone(1)));

e1.add_neurone(net.getNeurone(17),0.0006);
EXPECT_TRUE(e1.link_exist(net.getNeurone(17)));
EXPECT_FALSE(e1.link_exist(net.getNeurone(1628)));

e2.add_neurone(net.getNeurone(4),0.6789);
e2.add_neurone(net.getNeurone(7),0.29);
e2.add_neurone(net.getNeurone(8),0.4);
e2.add_neurone(net.getNeurone(9),0.89);

EXPECT_FALSE(e1.link_exist(net.getNeurone(0)));
EXPECT_TRUE(e2.link_exist(net.getNeurone(4)));
EXPECT_TRUE(e2.link_exist(net.getNeurone(7)));
EXPECT_TRUE(e2.link_exist(net.getNeurone(8)));
EXPECT_TRUE(e2.link_exist(net.getNeurone(9)));

inhib=nullptr;
excit=nullptr;
i1=nullptr;
e1=nullptr;
e2=nullptr;
}


TEST_F (NeuroneTest, fonction_update) {


Inhibiteur inhib(new Network);
double dt=0.5;
double I = 10;
double vi = inhib.getvt();
double ui = inhib.getut();

inhib.update(I,dt);
EXPECT_EQ(inhib.getvt_1(), vi + 0.5*(-16-(inhib.getparam().param_b * vi)+I));
EXPECT_FALSE(inhib.isFiring_1());
EXPECT_FALSE(inhib.isFiring());

dt = 0;
I  = inhib.courant();
vi = inhib.getvt();
ui = inhib.getut();
inhib.update(I, dt);
EXPECT_EQ(inhib.getvt(), vi + 0.5*(0.04*vi*vi+5*vi+140-ui+I));
EXPECT_NEAR(inhib.getut(), ui + (inhib.getparam().param_a * inhib.getparam().param_b * vi) - inhib.getparam().param_a * ui, 0.001); ///On met un expect_near car aroundis
EXPECT_FALSE(inhib.isFiring_1());

dt = 2;
I = inhib.courant();
vi = inhib.getvt();
ui = inhib.getut();
inhib.update(I, dt);
EXPECT_EQ(inhib.getvt(), vi + 0.5*(0.04*vi*vi+5*vi+140-ui+I));
EXPECT_EQ(inhib.getut(), ui + (inhib.getparam().param_a * inhib.getparam().param_b * vi - inhib.getparam().param_a * ui));
EXPECT_FALSE(inhib.isFiring_1());

Inhibiteur inhib1(new Network, LTS);
dt = 0;
ui = inhib1.getut();
inhib1.setvt(100.0);
vi = inhib1.getvt();
I  = inhib1.courant();

inhib1.update(I, dt);
EXPECT_EQ(-65, inhib1.getvt());
EXPECT_EQ(inhib1.getut_1(),inhib1.getut());
EXPECT_TRUE(inhib1.isFiring_1());
inhib1.set_firing();
EXPECT_TRUE(inhib1.isFiring());
EXPECT_FALSE(inhib1.isFiring_1());

Excitateur excit(new Network);

dt = 0.33;
I = excit.courant();
vi = excit.getvt();
ui = excit.getut();
excit.update(I, dt);

EXPECT_EQ(excit.getvt(), vi + 0.5*(-16-(0.2 * vi)+I));
EXPECT_EQ(excit.getut(),ui);
EXPECT_FALSE(excit.isFiring_1());

dt = 0;
I  = excit.courant();
vi = excit.getvt();
ui = excit.getut();
excit.update(I, dt);
EXPECT_EQ(excit.getvt(), vi + 0.5*(0.04*vi*vi+5*vi+140-ui+I));
EXPECT_EQ(excit.getut_1(), ui + (0.02 * 0.2 * vi - 0.02 * ui));
EXPECT_FALSE(excit.isFiring_1());

dt = 2;
I  = excit.courant();
vi = excit.getvt();
ui = excit.getut();
excit.update(I, dt);
EXPECT_EQ(excit.getvt(), vi + 0.5*(0.04*vi*vi+5*vi+140-ui+I));
EXPECT_EQ(excit.getut_1(), ui + (0.02 * 0.2 *vi - 0.02 * ui));
EXPECT_FALSE(excit.isFiring_1());

Excitateur excit2(new Network, IB);
dt = 0;
ui = excit2.getut();
vi = excit2.getvt();
excit2.setvt(100.0);
I  = excit2.courant();;
double ut2 = excit2.getut();

excit2.update(I, dt);

EXPECT_EQ(excit2.getparam().param_c, excit2.getvt());
EXPECT_EQ(ut2 + excit2.getparam().param_d, excit2.getut());
EXPECT_EQ(-55, excit2.getvt());

EXPECT_TRUE(excit2.isFiring_1());
excit2.set_firing();

EXPECT_TRUE(excit2.isFiring());
EXPECT_FALSE(excit2.isFiring_1());

Excitateur excit3(new Network, IB);
dt = 4.89;
excit3.setvt(300);
ui = excit3.getut();
I  = excit3.courant();


excit3.update(I,dt);

EXPECT_EQ(ui + excit3.getparam().param_d, excit3.getut());
EXPECT_FALSE(excit3.isFiring());
EXPECT_TRUE(excit3.isFiring_1());

inhib =nullptr;
inhib1=nullptr;
excit =nullptr;
excit2=nullptr;
excit3=nullptr;

}

TEST_F (NeuroneTest, fonction_courant_et_intensity) {

bool k(false);

Inhibiteur inhib(new Network);
Inhibiteur* p_inhib(&inhib);
Excitateur excit(new Network);
Excitateur* p_excit(&excit);

Inhibiteur inhib1(new Network);
Inhibiteur* p_inhib1(&inhib1);
Inhibiteur inhib2(new Network);
Inhibiteur* p_inhib2(&inhib2);
Excitateur excit1(new Network);
Excitateur* p_excit1(&excit1);
p_excit1->v(215.8);
k = (*p_inhib).add_neurone(p_inhib1, 0.1);
EXPECT_TRUE(k);
k = (*p_inhib).add_neurone(p_inhib2, 0.3);
EXPECT_TRUE(k);
k = (*p_inhib).add_neurone(p_excit1, 0.6);
EXPECT_TRUE(k);

Inhibiteur inhib3(new Network);
Inhibiteur* p_inhib3(&inhib3);
Excitateur excit2(new Network);
Excitateur* p_excit2(&excit2);
Excitateur excit3(new Network);
Excitateur* p_excit3(&excit3);
p_excit3->v(230.7);
k = (*p_excit).add_neurone(p_inhib3, 0.2);
EXPECT_TRUE(k);
k = (*p_excit).add_neurone(p_excit2, 0.4);
EXPECT_TRUE(k);
k = (*p_excit).add_neurone(p_excit3, 0.8);
EXPECT_TRUE(k);

double checkexcit = 0;
EXPECT_NEAR(checkexcit, p_excit->courant(), 20.4);
double checkinhib = 0;
EXPECT_NEAR(checkinhib, p_inhib->courant(), 8.3);

p_inhib =nullptr;
p_inhib1=nullptr;
p_inhib2=nullptr;
p_inhib3=nullptr;
p_excit =nullptr;
p_excit1=nullptr;
p_excit2=nullptr;
p_excit3=nullptr;
}
