#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TApplication.h>
#include "Analyzer.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
using namespace std;
int main()
{
    TString path,path2;
    path="ggH125";
    path2="qqZZ";
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->Plot(path);
    analysis->Plot(path2);
    return 0;
}
