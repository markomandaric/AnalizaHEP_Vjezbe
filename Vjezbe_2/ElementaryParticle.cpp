#include <iostream>
#include "ElementaryParticle.h"
using namespace EP;
using namespace std;
ElementaryParticle::ElementaryParticle(string n, float m, bool b)
{
	name = n;
	mass = m;
	boson = b;

	cout << "Particle named " << name << " has a mass of " << mass << " GeV." << endl;
	cout << "This particle is ";
	if (!boson) cout << "not ";
	cout << "a boson!" << endl;
}


