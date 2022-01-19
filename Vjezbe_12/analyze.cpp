#include <iostream>
#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include "Anlayzer.h"
using namespace std;

int main() {
	Anlayzer* analyze = new Anlayzer();
	analyze->Loop();
	analyze->Plot();
	analyze->TMVATraining();
	analyze->TMVA();
	return 0;
}
