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
    analysis->Binomial(3,10,0.5);
    cout<<analysis->sum_upper(2,2,0.6827)<<endl;
    cout<<analysis->sum_lower(2,2,0.6827)<<endl;
    analysis->Belt(10,0.6827);
    //analysis->Draw();
    return 0;
}
