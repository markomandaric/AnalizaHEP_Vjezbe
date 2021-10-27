#include <iostream>
#include "Analyzer.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;
int main()
{
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->ReadData();
	return 0;
}
