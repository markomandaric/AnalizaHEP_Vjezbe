#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <cmath>
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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
void Analyzer::Plot()
{
	fit->SetParameter(0,195.2);
	fit->SetParName(0,"norm");
	fit->SetParameter(1,1.201);
	fit->SetParName(1,"#tau");
	
	double sum=0.0;
if (fChain == 0)
		return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		
		distribution->Fill(t);	
		sum+=t;
	}
	lnL->SetParameter(0,nentries);
	lnL->SetParName(0,"N");
	lnL->SetParameter(1,sum);
	lnL->SetParName(1,"sum");
	cout<<"Analitically, tau= "<<sum/nentries<<endl;
	cout<<"Tau using -2lnL gives "<<lnL->GetMinimumX(1.0,10.0)<<endl;
}
void Analyzer::Draw()
{
	TCanvas *c=new TCanvas("c","c",1800,900);
	c->Divide(3);
	c->cd(1);
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	distribution->Draw();
	distribution->Fit(fit);
	c->cd(2);
	MaxLike->Draw();
	TLegend *leg=new TLegend(0.5,0.7,0.9,0.9);
	leg->AddEntry(MaxLike, "Maximum likelihood function","f");
	leg->SetTextSize(0.025);
	leg->Draw();
	c->cd(3);
	lnL->Draw();
	TLegend *legend=new TLegend(0.5,0.7,0.9,0.9);
	legend->AddEntry(lnL, "-2ln maximum likelihood function","f");
	legend->SetTextSize(0.022);
	legend->Draw();
	c->SaveAs("LnMaxLike.png");
	
	
}
