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
	//odredujem unaprijed p vrijednost od 5 sigma za odbacivanje

}
void Analyzer::pValueScan()
{
	TRandom3 *r3=new TRandom3();
	double mh, pValue;
	int br=0;	 

	TF1 *f=new TF1("fit","[0]*exp(-x/[1])",0,700);
	f->SetParName(0,"N_{sm}");
	f->SetParameter(0,100.0);
	f->SetParName(1,"#Zeta_{sm}");
	f->FixParameter(1,100.0);

	TGraph *scan=new TGraph();

	TH1F *histo=new TH1F("histo","histo",200,0,700);

	for(int i=10;i<=690;i+=5)
	{
		mh=i/1.0;
		for(int j=0;j<10000;j++)
		{
			if(r3->Rndm()>(-1*(mh-190)*(mh-190)+0.02))
				histo->Fill(r3->Exp(100));//pozadina
			else histo->Fill(r3->Gaus(mh, 0.0236*mh));//signal
		}
	
	histo->Fit(f,"Q","",i-10,i+10);
	pValue=(histo_chi->Integral(histo_chi->FindBin(f->GetChisquare()),200))/(histo_chi->Integral());
	scan->SetPoint(br,mh,pValue);
	br++;
	histo->Reset();
	}

	TCanvas *canvas=new TCanvas("canvas","canvas",1600,900);
	gPad->SetLogy();
	scan->SetMinimum(0.0001);
	scan->GetXaxis()->SetTitle("m_{H}");
	scan->GetYaxis()->SetTitle("p-value");
	scan->SetTitle("P-value scan");
	scan->Draw("AL*");
	
	canvas->SaveAs("scan.png");

	double z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*0.001);
	cout<<"p Value of 0.001 means "<<z_score<<" sigma"<<endl;
}





