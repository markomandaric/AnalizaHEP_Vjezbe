#include<iostream>
#include<cstdlib>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include "Analyzer.h"

using namespace std;

Analyzer::Analyzer()
{
}
void Analyzer::ReadData()
{
	
	ifstream myfile;
	myfile.open("Analysis.txt");
	string line,OneName, TwoName;
	int n;
	float px1,px2,py1,py2,pz1,pz2,pt1,pt2,E1,E2;
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			stringstream linestream(line);
			linestream >> n >> OneName >> px1 >> py1 >> pz1 >> pt1 >> E1 >> TwoName >> px2 >> py2 >> pz2 >> pt2 >> E2;
			cout<<n<<" "<<OneName<<" "<<px1<<" "<<py1<<" "<<pz1<<" "<<pt1<<" "<<E1<<" "<<TwoName<<" "<<px2<<" "<<py2<<" "<<pz2<<" "<<pt2<<" "<<E2;
		}
	}
	myfile.close();


}

