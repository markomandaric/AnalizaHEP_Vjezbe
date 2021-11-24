#include <iostream>
#include "Statistics.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

int main()
{
	Statistics *analysis;
	analysis=new Statistics();
	int number_of_events=5000;
	analysis->CalculatePi(number_of_events); 	
        double x,mi,sigma;
	x=185.0;
	mi=178.2;
	sigma=6.4;
	analysis->NormalDistribution(x,mi,sigma);
	x=205.0;
	mi=178.2;
	sigma=6.4;
	analysis->NormalDistribution(x,mi,sigma);
	x=185.0;
	mi=160.2;
	sigma=7.2;
	analysis->NormalDistribution(x,mi,sigma);
	return 0;
}
