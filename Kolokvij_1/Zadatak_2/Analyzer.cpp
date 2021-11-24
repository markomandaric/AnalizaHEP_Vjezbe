#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2F.h>
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
	TH1F *h1,*h3,*h4;
	TH2F *h2;
	h1=new TH1F("ele_pt","Transversal momentum of electrons",100,0,300);
	h2=new TH2F("ele_pt vs scl_eta","2D histogram ele_pt vs scl_eta", 100,-120,500,100,-5,5); 
	h3=new TH1F("ele_ep","Ele_ep",100,0,300);
	h4=new TH1F("ele_eelepout","ele_eelepout",100,0,300);
	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	h1->Fill(ele_pt);
	h2->Fill(ele_pt,scl_eta);
	h3->Fill(ele_ep);
	h4->Fill(ele_eelepout);}


	TCanvas* canvas=new TCanvas("canvas","canvas",1000,1000);
	canvas->Divide(3);
	gStyle->SetOptStat(0);
	canvas->cd(1);
	h1->Draw("HISTO");
	h1->GetXaxis()->SetTitle("ele_pt");
	h1->GetYaxis()->SetTitle("Events");
	h1->SetLineColor(kRed);
	gStyle->SetOptStat(0);
	TLegend *legend=new TLegend(.75,.75,1.0,.95);
	legend->SetTextSize(0.5);
	legend->AddEntry(h1,"ele_pt");
	legend->Draw();

	canvas->cd(2);
	h2->GetXaxis()->SetTitle("ele_pt");
	h2->GetYaxis()->SetTitle("scl_eta");
	h2->Draw("COLZ");	

	canvas->cd(3);
	h3->Draw("histo");
	h4->Draw("histo same");
	h3->SetLineColor(kRed);
	h4->SetFillColor(kBlue);
	TLegend* legend2=new TLegend(0.7,0.8,0.9,0.9);
	legend2->SetTextSize(0.5);
	legend2->AddEntry(h3,"ele_ep","l");
	legend2->AddEntry(h4,"ele_eelepout","l");
	legend2->Draw();
	canvas->SaveAs("2abc.png");
}

