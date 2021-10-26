#include <iostream>
#include "ElementaryParticle.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
using namespace EP;
int main()
{
    float a,b,c;
    int i;
    srand(time(0));
    char filename[]="Analysis.txt";
	remove(filename);
    
    ElementaryParticle *Higgs, *One, *Two;
    One=new ElementaryParticle();
    Two=new ElementaryParticle();
    //Higgs.Momentum(a,b,c);
    //Higgs.TransversalMomentum(a,b);
    
    
    for(i=1;i<=10000;i++)
    {
	a=(2*(rand()%100))-100;
        b=(2*(rand()%100))-100;
	c=(2*(rand()%100))-100;
	Higgs=new ElementaryParticle("Higgs boson", 126,true);
	Higgs->Momentum(a,b,c);
	Higgs->TransversalMomentum(a,b);
	Higgs->bosonDecay(i,One,Two);
	delete Higgs;
    }
    delete One;
    delete Two;
    
	return 0;
}



