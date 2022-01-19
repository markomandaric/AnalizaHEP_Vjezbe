#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom.h>
#include <iostream>
#include <TMath.h>
#include <TLine.h>
#include <TLegend.h>
using namespace std;
void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

	TRandom *h;
	h=new TRandom();
	//for(int i=0;i<10;i++)
	//cout<<h->Gaus(164.7,7.1)<<endl;


	TH1F *test = new TH1F("test statistic", "test statistic", 500,160,170);
	


	double sum=0.0,zbroj;
	
	double p_value;
	double z_score;	

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	
	sum+=height;
      // if (Cut(ientry) < 0) continue;
   }
	average=sum/nentries;
	
	for(int i=0;i<1000000;i++)
	{
		zbroj=0.0;
		for(int j=0;j<100;j++)
		{
			zbroj+=h->Gaus(164.7,7.1);
		}
		test->Fill(zbroj/100);
	}
	test->Scale(1.0/test->Integral());

   	p_value=test->Integral(test->FindBin(average),500);
   	
	if(p_value<0.05)
	cout<<"Rejecting France"<<endl;
	cout<<"p_value: "<<p_value<<endl;
	
	z_score=TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);
	cout<<"Confidence level :"<<z_score<<" sigma"<<endl;
	TCanvas *canvas;
        canvas=new TCanvas("canvas","canvas",1600,900);
	test->Draw("histo");
	TLine *line = new TLine(average, 0.0, average, 0.01);
   	line->Draw();
	canvas->SaveAs("test.png");
}
void Analyzer::Compare(TString name, double mi, double sigma)
{
	TRandom* h;
	h=new TRandom();
	
	double sum_spain, sum_other;
	double p_value_spain, p_value_other;
	

	TH1F *histo_spain=new TH1F("spain","spain",500,155,180);
	TH1F *histo_other=new TH1F("other","other",500,155,180);

	for(int i=0;i<1000000;i++)
	{
	   sum_spain=0.0;
	   sum_other=0.0;
	   for(int j=0;j<100;j++)
		{
			sum_spain+=h->Gaus(168.0,7.0);
			sum_other+=h->Gaus(mi,sigma);
		}
	   histo_spain->Fill(sum_spain/100);
	   histo_other->Fill(sum_other/100);
	}
	  

	histo_spain->Scale(1./histo_spain->Integral());
   	histo_other->Scale(1./histo_other->Integral());	

	p_value_spain = histo_spain->Integral(histo_spain->FindBin(average),500);
  	p_value_other=histo_other->Integral(histo_other->FindBin(average),500);

	double CL;

	if(name=="Netherlands")
		CL=1-(histo_other->Integral(0,histo_other->FindBin(average))/p_value_spain);
	else
		CL=1-(p_value_other/(histo_spain->Integral(0,histo_spain->FindBin(average))));
	cout << "Rejecting " << name << " with confidence level of : " << CL*100 << "%" << endl; 
    
	TCanvas *canvas1=new TCanvas("","",1600,900);
	
	histo_other->SetTitle("Hypothesis testing");
	histo_spain->SetTitle("Hypothesis testing");
	histo_other->GetXaxis()->SetTitle("test");
        histo_other->GetYaxis()->SetTitle("PDF");
	histo_spain->GetXaxis()->SetTitle("test");
        histo_spain->GetYaxis()->SetTitle("PDF");
	histo_spain->SetLineColor(kRed);
	histo_other->SetLineColor(kBlue);

	histo_spain->Draw("histo");
	histo_other->Draw("histo same");
	
	
	TLine *line = new TLine(average, 0., average, 0.03);
	line->Draw();
	
	TLegend *legend=new TLegend(0.1,0.7,0.3,0.9);
	legend->AddEntry(histo_spain, "Spain", "f");
	legend->AddEntry(histo_other, name, "f");
	legend->Draw();

	
	
	
	canvas1->SaveAs("Spain vs "+name+".png");


}
