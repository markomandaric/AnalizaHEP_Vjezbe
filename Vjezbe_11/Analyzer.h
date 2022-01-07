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
#include<TGraphErrors.h>

using namespace std;

class Analyzer{
	public:
	
	Analyzer();
	double Factorial(int n);
	double Binomial(int r, int N, double p);
	double sum_upper(int m1, int N1, double CL);
	double sum_lower(int m2, int N2, double CL);
	void Belt(int N, double C);
	void Draw(int N, double C);
	void Dice(int N, double C);
};

