#include<iostream>
#include<cstdlib>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#include "Statistics.h"

using namespace std;
Statistics::Statistics()
{
	cout<<"Objekt je uspješno kreiran!"<<endl;
}

void Statistics::CalculatePi(int n)
{	
    int INTERVAL, i;
    double rand_x, rand_y, origin_dist, pi;
    int circle_points = 0, square_points = 0;
    INTERVAL=n;
    // Initializing rand()
    srand(time(NULL));
  
    // Total Random numbers generated = possible x
    // values * possible y values
    for (i = 0; i < (INTERVAL * INTERVAL); i++) {
  
        // Randomly generated x and y values
        rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;
  
        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;
  
        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1)
            circle_points++;
  
        // Total number of points generated
        square_points++;
  
        // estimated pi after this iteration
        pi = double(4 * circle_points) / square_points;
  
    }
  
    // Final Estimated Value
    cout<<"Procjena broja pi za "<<n<<"*"<<n<<" događaja: "<<pi<<endl;
}
void Statistics::NormalDistribution(double x,double mi, double sigma)
{
	double P;
	P=1/(sigma*sqrt(2*3.14159))*exp((-1*(x-mi)*(x-mi))/(2*sigma*sigma));
	cout<<"P("<<x<<";"<<mi<<","<<sigma<<")="<<P<<endl;

}
