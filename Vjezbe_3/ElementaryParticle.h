#include<iostream>
using namespace std;

namespace EP
{
    class ElementaryParticle
    {
    public:
        string name;
        float mass;
        bool boson;
	float E;
	float px;
	float py;
	float pz;
	float pt;
	void Momentum(float px, float py, float pz);
	void TransversalMomentum(float px, float py);
	void bosonDecay(int i,ElementaryParticle* one, ElementaryParticle* two);
        ElementaryParticle(string n, float m, bool b);
	ElementaryParticle();
    };

}

