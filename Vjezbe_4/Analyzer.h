#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
using namespace std;

    class Analyzer
    {
    public:
    	Analyzer();
    	void ReadData();
    	void ConvertTxtToRootFile();
    };

