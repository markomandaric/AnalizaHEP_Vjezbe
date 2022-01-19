#include "Analyzer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;
int main()
{
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->Loop();
    analysis->Compare("France",164.7,7.1);
    analysis->Compare("Italy",166.1,6.5);
    analysis->Compare("Netherlands",170.3,7.5);
    return 0;
}
