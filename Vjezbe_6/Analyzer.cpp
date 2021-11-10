#define Analyzer_cxx
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
	TH1F *h1,*h2,*h3;
	TH1F *hi0,*hi1,*hi2,*hi3;
	TH1F *his0,*his1,*his2,*his3;
	TH1F *hist0,*hist1,*hist2,*hist3;

	TH1F *h0=new TH1F("LeptPt1","Transversal momentum",100,0,140);
	h1=new TH1F("LeptPt2","Transversal momentum",100,0,140);
	h2=new TH1F("LeptPt3","Transversal momentum",100,0,140);
	h3=new TH1F("LeptPt4","Transversal momentum",100,0,140);

	hi0=new TH1F("LepEta1","Pseudorapidity",100,0,140);
	hi1=new TH1F("LepEta2","Pseudorapidity",100,0,140);
	hi2=new TH1F("LeptEta3","Pseudorapidity",100,0,140);
	hi3=new TH1F("LeptEta4","Pseudorapidity",100,0,140);

	his0=new TH1F("LeptPhi1","Azimuthal angle",100,0,140);
	his1=new TH1F("LeptPhi2","Azimuthal angle",100,0,140);
	his2=new TH1F("LeptPhi3","Azimuthal angle",100,0,140);
	his3=new TH1F("LeptPhi4","Azimuthal angle",100,0,140);

	hist0=new TH1F("LeptBDT1","BDT score",100,0,140);
	hist1=new TH1F("LeptBDT2","BDT score",100,0,140);
	hist2=new TH1F("LeptBDT3","BDT score",100,0,140);
	hist3=new TH1F("LeptBDT4","BDT score",100,0,140);

	  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
	h0->Fill(LepPt->at(0));
	h1->Fill(LepPt->at(1));
	h2->Fill(LepPt->at(2));
	h3->Fill(LepPt->at(3));
}


auto canvas=new TCanvas("canvas","canvas",900,900);
canvas->Divide(2,2,0,0);
	canvas->cd(1);
gStyle->SetOptStat(0);

	h2->Draw("HISTO");
	h3->Draw("HISTO same");
	h0->Draw("HISTO same"); 
	h1->Draw("HISTO same");
	
	h2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	h2->GetYaxis()->SetTitle("Events/2.8GeV");
	
	h0->SetLineColor(kRed);
	h0->SetFillColor(kRed);
	h1->SetLineColor(kBlue);
	h2->SetLineColor(kYellow);
	h3->SetLineColor(kGreen);
	
	gStyle->SetOptStat(0);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);
	
    legend->AddEntry(h0,"First lepton");
    legend->AddEntry(h1,"Second lepton");
	legend->AddEntry(h2,"Third lepton");
	legend->AddEntry(h3,"Fourth lepton");
    legend->Draw();
	canvas->SaveAs("zdk2.pdf");
	canvas->SaveAs("zdk2.png");
	canvas->SaveAs("zdk2.root");
}
