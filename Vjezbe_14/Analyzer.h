#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include<THStack.h>
#include <TH1F.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <TGraph.h>
#include <TH2F.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>

using namespace std;

class Analyzer
{
	public:
	Analyzer();
	TH1F *histo_chi;
	void Generate();
	void pValueScan();
};
