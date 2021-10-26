#include<iostream>
#include<cstdlib>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#include "ElementaryParticle.h"
using namespace EP;
using namespace std;
ElementaryParticle::ElementaryParticle(string n, float m, bool b)
{
	name = n;
	mass = m;
	boson = b;

	//cout << "Particle named " << name << " has a mass of " << mass << " GeV." << endl;
	//cout << "This particle is ";
	//if (!boson) cout << "not ";
	//cout << "a boson!" << endl;
}
ElementaryParticle::ElementaryParticle()
{
	name = "";
	mass = 0;
	boson = false;
}
void ElementaryParticle::Momentum(float a, float b, float c)
{
	float P;
	px=a;
	py=b;
	pz=c;
	P=sqrt(px*px+py*py+pz*pz);
	E=sqrt(P*P+mass*mass);
	//cout<<"Energija vaše čestice iznosi: ";cout<<E<<endl;
}
void ElementaryParticle::TransversalMomentum(float a, float b)
{
	px=a;
	py=b;
	pt=sqrt(a*a+b*b);
	//cout<<"Transverzalna količina gibanja iznosi: "<<pt<<endl;
}
void ElementaryParticle::bosonDecay(int i,ElementaryParticle* one, ElementaryParticle* two)
{
	float temp;
	if(boson==false)
		cout<<"Decay of "<<name <<" is not possible"<<endl;
	else {
		temp=float((rand()%100))/100;
		//cout<<temp<<endl;
		if(temp<=0.214)
			{//cout<<"raspad u W bozone"<<endl;
				one->name="W";
				two->name="W";
				one->mass=80.38;
				two->mass=80.38;
				one->px=px*float(rand()%100)/100;
				one->py=py*float(rand()%100)/100;
				one->pz=pz*float(rand()%100)/100;
				one->Momentum(one->px,one->py,one->pz);
				one->TransversalMomentum(one->px,one->py);
				
				two->px=px-one->px;
				two->py=py-one->py;
				two->pz=pz-one->pz;
				two->Momentum(two->px,two->py,two->pz);
				two->TransversalMomentum(two->px,two->py);
			}
		else if(temp>0.214&&temp<=0.278)
			{//cout<<"raspad u tau leptone"<<endl;
				one->name="T";
				two->name="T";
				one->mass=1.78;
				two->mass=1.78;
				one->px=px*float(rand()%100)/100;
				one->py=py*float(rand()%100)/100;
				one->pz=pz*float(rand()%100)/100;
				one->Momentum(one->px,one->py,one->pz);
				one->TransversalMomentum(one->px,one->py);
				
				two->px=px-one->px;
				two->py=py-one->py;
				two->pz=pz-one->pz;
				two->Momentum(two->px,two->py,two->pz);
				two->TransversalMomentum(two->px,two->py);
			}
		else if(temp>0.278&&temp<=0.304)
			{//cout<<"raspad u Z bozone"<<endl;
				one->name="Z";
				two->name="Z";
				one->mass=91.19;
				two->mass=91.19;
				one->px=px*float(rand()%100)/100;
				one->py=py*float(rand()%100)/100;
				one->pz=pz*float(rand()%100)/100;
				one->Momentum(one->px,one->py,one->pz);
				one->TransversalMomentum(one->px,one->py);
				
				two->px=px-one->px;
				two->py=py-one->py;
				two->pz=pz-one->pz;
				two->Momentum(two->px,two->py,two->pz);
				two->TransversalMomentum(two->px,two->py);
			}
		else{//cout<<"raspad u b kvarkove"<<endl;
				one->name="B";
				two->name="B";
				one->mass=4.18;
				two->mass=4.18;
				one->px=px*float(rand()%100)/100;
				one->py=py*float(rand()%100)/100;
				one->pz=pz*float(rand()%100)/100;
				one->Momentum(one->px,one->py,one->pz);
				one->TransversalMomentum(one->px,one->py);
				
				two->px=px-one->px;
				two->py=py-one->py;
				two->pz=pz-one->pz;
				two->Momentum(two->px,two->py,two->pz);
				two->TransversalMomentum(two->px,two->py);
		    }
	cout<<i<<one->name<<"\t"<<one->px<<"\t"<<one->py<<"\t"<<one->pz<<"\t"<<one->E<<endl;
	cout<<i<<two->name<<"\t"<<two->px<<"\t"<<two->py<<"\t"<<two->pz<<"\t"<<two->E<<endl;
	ofstream file;
	file.open("Analysis.txt",ios_base::app);
	file << i <<" "<<one->name<<" "<<one->px<<" "<<one->py<<" "<<one->pz<<" "<<one->pt<<" "<<one->E<<" "<<two->name<<" "<<two->px<<" "<<two->py<<" "<<two->pz<<" "<<two->pt<<" "<<two->E<<endl;
	file.close();
	}
}


