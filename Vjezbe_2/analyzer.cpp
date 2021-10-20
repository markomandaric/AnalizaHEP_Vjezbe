#include <iostream>
#include "ElementaryParticle.h"
using namespace EP;
int main()
{


    ElementaryParticle Higgs("Higgs boson", 126, true);
    ElementaryParticle TopQuark("Top quark", 173.0, false);

    

    ElementaryParticle* Z;
    Z = new ElementaryParticle("Z boson", 91.2, true);
    //Z->printInfo();
    delete Z;

	return 0;
}
