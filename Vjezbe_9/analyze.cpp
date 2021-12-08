#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TApplication.h>
#include "Analyzer.h"
#include <cstdlib>
#include <vector>

using namespace std;
int main()
{
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->Plot();
    analysis->Draw();
    return 0;
}
