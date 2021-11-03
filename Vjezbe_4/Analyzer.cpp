#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include "Analyzer.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
using namespace std;

Analyzer::Analyzer()
{
}
void Analyzer::ReadData()
{
	
	ifstream myfile;
	myfile.open("Analysis.txt");
	string line,OneName, TwoName;
	int n;
	float px1,px2,py1,py2,pz1,pz2,pt1,pt2,E1,E2;
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			stringstream linestream(line);
			linestream >> n >> OneName >> px1 >> py1 >> pz1 >> pt1 >> E1 >> TwoName >> px2 >> py2 >> pz2 >> pt2 >> E2;
			//cout<<n<<" "<<OneName<<" "<<px1<<" "<<py1<<" "<<pz1<<" "<<pt1<<" "<<E1<<" "<<TwoName<<" "<<px2<<" "<<py2<<" "<<pz2<<" "<<pt2<<" "<<E2;
		}
	}
	myfile.close();


}

void Analyzer::ConvertTxtToRootFile()
{
	ifstream input;
	input.open("Analysis.txt");

	TFile* output=output=TFile::Open("Analysis.root", "RECREATE");
	TTree* tree=new TTree("tree", "Vjezbe_4");

	Int_t n;

	Char_t NameOne;
	Float_t px1;
	Float_t py1;
	Float_t pz1;
	Float_t pt1;
	Float_t E1;

	Char_t NameTwo;
	Float_t px2;
	Float_t py2;
	Float_t pz2;
	Float_t pt2;
	Float_t E2;
	
	tree->Branch("n",&n,"n");
	tree->Branch("NameOne", &NameOne, "NameOne/C");
	tree->Branch("px1", &px1, "px1/F");
	tree->Branch("py1", &py1, "py1/F");
	tree->Branch("pz1", &pz1, "pz1/F");
	tree->Branch("pt1", &pt1, "pt1/F");
	tree->Branch("E1",&E1,"E1/F");
	tree->Branch("NameTwo", &NameTwo, "NameTwo/C");
	tree->Branch("px2", &px2, "px2/F");
	tree->Branch("py2", &py2, "py2/F");
	tree->Branch("pz2", &pz2, "pz2/F");
	tree->Branch("pt2", &pt2, "pt2/F");
	tree->Branch("E2",&E2,"E2/F");	

	string line;
	if(input.is_open())
	{
		while(getline(input,line))
		{
			stringstream linestream(line);
			linestream >> n >> NameOne >> px1 >> py1 >> pz1 >> pt1 >> E1 >> NameTwo >> px2 >> py2 >> pz2 >> pt2 >> E2;
			tree->Fill();
		}
	}
	tree->Print();
	tree->Write();
	input.close();
	delete output;
}