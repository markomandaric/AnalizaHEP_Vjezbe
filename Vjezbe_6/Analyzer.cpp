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
	
	TH1F *h0,*h1,*h2,*h3;
	TH1F *hi0,*hi1,*hi2,*hi3;
	TH1F *his0,*his1,*his2,*his3;
	TH1F *hist0,*hist1,*hist2,*hist3;

	h0=new TH1F("LeptPt1","Transversal momentum",100,0,140);
	h1=new TH1F("LeptPt2","Transversal momentum",100,0,140);
	h2=new TH1F("LeptPt3","Transversal momentum",100,0,140);
	h3=new TH1F("LeptPt4","Transversal momentum",100,0,140);

	hi0=new TH1F("LepEta1","Pseudorapidity",100,-5,5);
	hi1=new TH1F("LepEta2","Pseudorapidity",100,-5,5);
	hi2=new TH1F("LeptEta3","Pseudorapidity",100,-5,5);
	hi3=new TH1F("LeptEta4","Pseudorapidity",100,-5,5);

	his0=new TH1F("LeptPhi1","Azimuthal angle",100,-6,6);
	his1=new TH1F("LeptPhi2","Azimuthal angle",100,-6,6);
	his2=new TH1F("LeptPhi3","Azimuthal angle",100,-6,6);
	his3=new TH1F("LeptPhi4","Azimuthal angle",100,-6,6);

	hist0=new TH1F("LeptBDT1","BDT score",40,0,10);
	hist1=new TH1F("LeptBDT2","BDT score",40,0,10);
	hist2=new TH1F("LeptBDT3","BDT score",40,0,10);
	hist3=new TH1F("LeptBDT4","BDT score",40,0,10);
	

	TLorentzVector* higgs = new TLorentzVector();
        TLorentzVector* Z1 = new TLorentzVector();
        TLorentzVector* Z2 = new TLorentzVector();
        TLorentzVector* l1 = new TLorentzVector();
        TLorentzVector* l2 = new TLorentzVector();
        TLorentzVector* l3 = new TLorentzVector();
        TLorentzVector* l4 = new TLorentzVector();
	TH1F* h4 = new TH1F("h4", "Higgs Mass", 25, 90, 140);
	TFile f("/home/public/data/ggH125/ZZ4lAnalysis.root");
	TH1F* histoCounter=(TH1F*)f.Get("ZZTree/Counters");

	  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       
	float binContent=histoCounter->GetBinContent(40);
	float w=(137.0*1000.0*xsec*overallEventWeight)/binContent;

	h0->Fill(LepPt->at(0),w);
	h1->Fill(LepPt->at(1),w);
	h2->Fill(LepPt->at(2),w);
	h3->Fill(LepPt->at(3),w);

	hi0->Fill(LepEta->at(0),w);
	hi1->Fill(LepEta->at(1),w);
	hi2->Fill(LepEta->at(2),w);
	hi3->Fill(LepEta->at(3),w);

	his0->Fill(LepPhi->at(0),w);
	his1->Fill(LepPhi->at(1),w);
	his2->Fill(LepPhi->at(2),w);
	his3->Fill(LepPhi->at(3),w);

	hist0->Fill(LepBDT->at(0),w);
	hist1->Fill(LepBDT->at(1),w);
	hist2->Fill(LepBDT->at(2),w);
	hist3->Fill(LepBDT->at(3),w);

	l1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
        l2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
        l3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
        l4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);

	*Z1 = *l1 + *l2;
        *Z2 = *l3 + *l4;

        *higgs = *Z1 + *Z2;
        h4->Fill(higgs->M(),w);
}


auto canvas=new TCanvas("canvas","canvas",900,900);
canvas->Divide(2,2);
gStyle->SetOptStat(0);

	canvas->cd(1);
	h2->Draw("HISTO");
	h3->Draw("HISTO same");
	h0->Draw("HISTO same"); 
	h1->Draw("HISTO same");
	
	h2->GetXaxis()->SetTitle("p_{T} [GeV]");
	h2->GetYaxis()->SetTitle("Events");
	
	h0->SetLineColor(kRed);
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

	canvas->cd(2);
	hi2->Draw("HISTO");
	hi3->Draw("HISTO same");
	hi0->Draw("HISTO same"); 
	hi1->Draw("HISTO same");
	
	hi2->GetXaxis()->SetTitle("Pseudorapidity");
	hi2->GetYaxis()->SetTitle("Events");
	
	hi0->SetLineColor(kRed);
	hi1->SetLineColor(kBlue);
	hi2->SetLineColor(kYellow);
	hi3->SetLineColor(kGreen);
	
	gStyle->SetOptStat(0);

	TLegend *legend2=new TLegend(.75,.75,1.0,.95);
	legend2->AddEntry(hi0,"First lepton");
        legend2->AddEntry(hi1,"Second lepton");
	legend2->AddEntry(hi2,"Third lepton");
	legend2->AddEntry(hi3,"Fourth lepton");
        legend2->Draw();
 	

	canvas->cd(3);
	his2->Draw("HISTO");
	his3->Draw("HISTO same");
	his0->Draw("HISTO same"); 
	his1->Draw("HISTO same");
	
	his2->GetXaxis()->SetTitle("Azimuthal angle [rad]");
	his2->GetYaxis()->SetTitle("Events");
	
	his0->SetLineColor(kRed);
	his1->SetLineColor(kBlue);
	his2->SetLineColor(kYellow);
	his3->SetLineColor(kGreen);
	
	gStyle->SetOptStat(0);

	TLegend *legend3=new TLegend(.75,.75,1.0,.95);
	legend3->AddEntry(his0,"First lepton");
        legend3->AddEntry(his1,"Second lepton");
	legend3->AddEntry(his2,"Third lepton");
	legend3->AddEntry(his3,"Fourth lepton");
        legend3->Draw();

	canvas->cd(4);
	hist2->Draw("HISTO");
	hist3->Draw("HISTO same");
	hist0->Draw("HISTO same"); 
	hist1->Draw("HISTO same");
	
	hist2->GetXaxis()->SetTitle("BDT score");
	hist2->GetYaxis()->SetTitle("Events");
	
	hist0->SetLineColor(kRed);
	hist1->SetLineColor(kBlue);
	hist2->SetLineColor(kYellow);
	hist3->SetLineColor(kGreen);
	
	gStyle->SetOptStat(0);

	TLegend *legend4=new TLegend(.75,.75,1.0,.95);
	legend4->AddEntry(hist0,"First lepton");
        legend4->AddEntry(hist1,"Second lepton");
	legend4->AddEntry(hist2,"Third lepton");
	legend4->AddEntry(hist3,"Fourth lepton");
        legend4->Draw();

	canvas->SaveAs("zdk2.pdf");
	canvas->SaveAs("zdk2.png");
	canvas->SaveAs("zdk2.root");

	TCanvas *canvas2;
	canvas2=new TCanvas("canvas2", "canvas2", 1000,1000);
	gStyle->SetOptStat(0);
	h4->Draw("HISTO");
	
	h4->GetXaxis()->SetTitle("mass_{4 leptons} [GeV]");
	h4->GetYaxis()->SetTitle("Events");
	
	TLegend *legendd = new TLegend(.75,.75,1.0,.95); 
        legendd->AddEntry(h4,"Reconstructed Higgs mass");
	legendd->Draw();
	
	canvas2->SaveAs("Higgsw.pdf");
	canvas2->SaveAs("Higgsw.png");
	canvas2->SaveAs("Higgsw.root");
}
