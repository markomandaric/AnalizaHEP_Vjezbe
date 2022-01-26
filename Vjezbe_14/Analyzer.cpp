#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <vector>
#include <TGraph.h>
#include <TH2F.h>
#include <TF1.h>
#include <stdlib.h>
#include <TMath.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>
#include <TLine.h>
#include <TLatex.h>
#include <TRandom.h>
#include <TRandom3.h>

using namespace std;

Analyzer::Analyzer()
{
	histo_chi=new TH1F("histo_chi","histo_chi",200,0,25);	
}
void Analyzer::Generate()
{

	TRandom3 *r3=new TRandom3();
	//r3->Exp(100);	

	TF1 *fit=new TF1("fit","[0]*exp(-x/[1])",0,700);
	fit->SetParName(0,"N_{sm}");
	fit->SetParameter(0,100.0);
	fit->SetParName(1,"#Zeta_{sm}");
	fit->FixParameter(1,100.0);
	TH1F *histogram=new TH1F("histogram","histogram",200,0,700);
	for(int i=0;i<1000;i++)
	{
		
		for(int j=0;j<100000;j++)
		{
			histogram->Fill(r3->Exp(100));
		}
		for(int k=0;k<=680;k+=5)
		{
			histogram->Fit(fit,"Q","",k, k+20);
			histo_chi->Fill(fit->GetChisquare());
		}
	histogram->Reset();
	}
	histo_chi->Scale(1.0/histo_chi->Integral());
	TCanvas *c=new TCanvas("canvas","canvas",1600,900);
	gStyle->SetOptStat(0);
	histo_chi->GetXaxis()->SetTitle("#chi^{2}");
	histo_chi->GetYaxis()->SetTitle("PDF");
	histo_chi->SetTitle("Test statistic");
	histo_chi->Draw("histo");
	c->SaveAs("test.png");

}

