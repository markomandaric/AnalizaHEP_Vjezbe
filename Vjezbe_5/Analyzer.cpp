#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>

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
      //std::cout<<px1<<std::endl;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::PlotHistogram()
{
	TH1F* h1=new TH1F("h1","Decay particles transversal momentum histogram",100,0,130);
	TH1F* h2=new TH1F("h2","Particle two transversal momentum histogram",100,0,130);
	TH1F* h3=new TH1F("h_Higgs","Higgs boson transversal momentum histogram",100,0,130);
	
	TLorentzVector* particle_one;
	TLorentzVector* particle_two;
	TLorentzVector* Higgs;
	particle_one=new TLorentzVector();
	particle_two=new TLorentzVector();
	Higgs=new TLorentzVector();

	  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::cout<<px1<<std::endl;
	h1->Fill(pt1);
	h2->Fill(pt2);
	
	particle_one->SetPxPyPzE(px1,py1,pz1,E1);
	particle_two->SetPxPyPzE(px2,py2,pz2,E2);
	*Higgs=*particle_one+*particle_two;

	h3->Fill(sqrt(Higgs->Px()*Higgs->Px()+Higgs->Py()*Higgs->Py()));

}

auto canvas = new TCanvas("canvas","canvas",600,600);
canvas->Divide(2,2);
canvas->cd(1);
h1->Draw();
canvas->cd(1);
h2->Draw("hist same");
canvas->cd(2);
h3->Draw("hist same");

h1->GetYaxis()->SetRangeUser(0,220);
h2->GetYaxis()->SetRangeUser(0,220);
h1->GetXaxis()->SetTitle("p_{t} [GeV]");
h1->GetYaxis()->SetTitle("Number of events");
h3->GetXaxis()->SetTitle("p_{t} [GeV]");
h3->GetYaxis()->SetTitle("Number of events");

h1->SetLineColor(kRed);
h1->SetFillColor(kRed);
h2->SetLineColor(kBlue);
h3->SetLineColor(kYellow);

h1->SetStats(0);
TLegend* legend=new TLegend(.7,.75,.89,.89);
legend->SetHeader("Final Histogram","C");
legend->AddEntry(h1,"Particle 1","f");
legend->AddEntry(h2,"Particle 2","f");
legend->AddEntry(h3,"Higgs","f");
legend->Draw();

canvas->SaveAs("Higgs_reconstructed.pdf");
canvas->SaveAs("Higgs_reconstructed.root");
canvas->SaveAs("Higgs_reconstructed.png");
}
