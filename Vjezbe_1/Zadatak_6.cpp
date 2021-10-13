#include<iostream>

 

using namespace std;

 

class ElementaryParticle

{

public:

    string name;

    float mass;

    bool boson;

   

    ElementaryParticle(string n, float m, bool b)

    {

        name = n;

        mass = m;

        boson = b;

        printInfo();

    }

    void printInfo()

    {

        cout << "Name: "<<name<<"\n";

        cout << "Mass:"<<mass<<"GeV\n";

        if (boson)

            cout << "The particle is a boson\n";

        else cout << "The particle is not a boson\n";

    }

 

};

 

int main() {

 

    ElementaryParticle Higgs("Higgs boson", 125, true);

    ElementaryParticle Top("Top quark",173,false);

    
    ElementaryParticle* pointerZ=new ElementaryParticle("Z boson", 91, true);
    
   

    

    cout << pointerZ->name;

    /*Higgs.name = "Higgs boson";

    Higgs.boson = true;

    Higgs.mass = 125;

    Top.name = "Top quark";

    Top.boson = false;

    Top.mass = 173;

    Z.boson = true;

    Z.mass = 91;

    Z.name = "Z boson";

    Higgs.printInfo();

    Top.printInfo();

    Z.printInfo();*/

    return 0;

 

}
