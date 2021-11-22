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
    TString path,path2;
    path="ggH125";
    path2="qqZZ";
    Analyzer *analysis;
    analysis=new Analyzer();
    analysis->Plot(path);
    analysis->Plot(path2);
    return 0;
}
