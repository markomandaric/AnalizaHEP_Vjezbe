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
#include <THStack.h>
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

void Analyzer::Plot(TString Path)
{


        TFile* f = new TFile("/home/public/data/"+Path+"/ZZ4lAnalysis.root");
        TTree* tree = (TTree*) f->Get("ZZTree/candTree");
        Init(tree);
   	TH1F* histoCounter=(TH1F*)f->Get("ZZTree/Counters");
	float binContent=histoCounter->GetBinContent(40);
	

	TLorentzVector* higgs = new TLorentzVector();
        TLorentzVector* Z1 = new TLorentzVector();
        TLorentzVector* Z2 = new TLorentzVector();
        TLorentzVector* l1 = new TLorentzVector();
        TLorentzVector* l2 = new TLorentzVector();
        TLorentzVector* l3 = new TLorentzVector();
        TLorentzVector* l4 = new TLorentzVector();

	TCanvas* c=new TCanvas("c","c",1000,1000);
	THStack* hs=new THStack("hs","Reconstructed mass");

	  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


	float w=(137.0*1000.0*xsec*overallEventWeight)/binContent;

	

	l1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
        l2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
        l3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
        l4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);

	*Z1 = *l1 + *l2;
        *Z2 = *l3 + *l4;

        *higgs = *Z1 + *Z2;
        
	if(Path=="ggH125")
		histoSig->Fill(higgs->M(),w);
	else if(Path=="qqZZ")
		histoBack->Fill(higgs->M(),w);
}

	histoBack->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histoBack->GetYaxis()->SetTitle("Events / 2GeV");
	histoBack->SetStats(0);
	histoBack->SetLineColor(kBlue);
	histoBack->SetFillColor(kBlue);
	hs->Add(histoBack);

	histoSig->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histoSig->GetYaxis()->SetTitle("Events / 2GeV");
	histoSig->SetStats(0);
	histoSig->SetLineColor(kRed);
	histoSig->SetFillColor(kRed);
	hs->Add(histoSig);

	hs->Draw("hist");
	hs->GetXaxis()->SetTitle("m_{4l} (GeV)");
	hs->GetYaxis()->SetTitle("Events / 2GeV");

	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histoSig,"Signal","f");
	legend->AddEntry(histoBack,"Background","f");
	legend->Draw();

	c->SaveAs("Reconstructed_Higgs.png");
}	

