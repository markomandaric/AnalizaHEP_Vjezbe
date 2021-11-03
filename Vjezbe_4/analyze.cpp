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
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->ReadData();
    analysis->ConvertTxtToRootFile();
    return 0;
}
