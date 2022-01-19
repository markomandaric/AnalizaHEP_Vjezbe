#define Anlayzer_cxx
#include "Anlayzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TGraph.h>
using namespace std;
void Anlayzer::Loop()
{
	
	Init(Signal);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histo_signal[0]->Fill(ele_pt);
      histo_signal[1]->Fill(scl_eta);
      histo_signal[2]->Fill(ele_hadronicOverEm);
      histo_signal[3]->Fill(ele_gsfchi2);
      histo_signal[4]->Fill(ele_fbrem);
      histo_signal[5]->Fill(ele_ep);
      histo_signal[6]->Fill(ele_eelepout);
      histo_signal[7]->Fill(ele_pfChargedHadIso);
      histo_signal[8]->Fill(ele_expected_inner_hits);
      histo_signal[9]->Fill(ele_sclRawE);
      histo_signal[10]->Fill(ele_ecalE);
      histo_signal[11]->Fill(ele_sclNclus);
      histo_signal[12]->Fill(ele_oldhebc);
      histo_signal[13]->Fill(ele_oldcircularity);
      histo_signal[14]->Fill(ele_kfhits);
      

   }
	Init(Background);
   if (fChain == 0) return;

    nentries = fChain->GetEntriesFast();

  nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histo_background[0]->Fill(ele_pt);
      histo_background[1]->Fill(scl_eta);
      histo_background[2]->Fill(ele_hadronicOverEm);
      histo_background[3]->Fill(ele_gsfchi2);
      histo_background[4]->Fill(ele_fbrem);
      histo_background[5]->Fill(ele_ep);
      histo_background[6]->Fill(ele_eelepout);
      histo_background[7]->Fill(ele_pfChargedHadIso);
      histo_background[8]->Fill(ele_expected_inner_hits);
      histo_background[9]->Fill(ele_sclRawE);
      histo_background[10]->Fill(ele_ecalE);
      histo_background[11]->Fill(ele_sclNclus);
      histo_background[12]->Fill(ele_oldhebc);
      histo_background[13]->Fill(ele_oldcircularity);
      histo_background[14]->Fill(ele_kfhits);
      
   }
}
void Anlayzer::Plot()
{
	auto canvas = new TCanvas("canvas","canvas",1300,1300);	
	canvas->Divide(2,4);
	gStyle->SetOptStat(0);

	 TString Xaxis_title[8] = { "ele_pt", "scl_eta", "ele_hadronicOverEm", "ele_gsfchi2", "ele_fbrem", "ele_ep", "ele_eelepout", "ele_pfChargedHadIso" };
	
	for(int i=0;i<8;i++)
	{
		canvas->cd(i + 1);
		histo_signal[i]->GetXaxis()->SetTitle(Xaxis_title[i]);
	        histo_background[i]->GetXaxis()->SetTitle(Xaxis_title[i]);
	        histo_signal[i]->GetYaxis()->SetTitle("events");
	        histo_background[i]->GetYaxis()->SetTitle("events");
	        histo_signal[i]->SetLineColor(kRed);
	        histo_background[i]->SetLineColor(kBlue);

       		TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
        	legend->AddEntry(histo_signal[i], "Signal", "l");
        	legend->AddEntry(histo_background[i], "Background", "l");
        	legend->Draw();

        	int s_max = histo_signal[i]->GetBinContent(histo_signal[i]->GetMaximumBin());
        	int b_max = histo_background[i]->GetBinContent(histo_background[i]->GetMaximumBin());

	        if (s_max > b_max)
		{
	            histo_signal[i]->Draw("hist");
	            histo_background[i]->Draw("hist same");
	        }
	        else 
		{
	            histo_background[i]->Draw("hist");
	            histo_signal[i]->Draw("hist same");
	        }
        }

    canvas->SaveAs("All.png");

}

void Anlayzer::TMVATraining()
{
   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";
   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   dataloader->AddVariable( "ele_pt", 'F');
   dataloader->AddVariable( "ele_fbrem", 'F');
   dataloader->AddVariable( "ele_ep", 'F' );
   dataloader->AddVariable( "ele_eelepout", 'F' );
   dataloader->AddVariable( "ele_hadronicOverEm", 'F' );
   dataloader->AddVariable( "scl_eta", 'F' );
   dataloader->AddVariable( "ele_gsfchi2", 'F' );
   dataloader->AddVariable( "ele_pfChargedHadIso", 'F' );
   dataloader->AddVariable( "ele_expected_inner_hits", 'F' );
   dataloader->AddVariable( "ele_sclRawE", 'F' );
   dataloader->AddVariable( "ele_ecalE", 'F' );
   dataloader->AddVariable( "ele_sclNclus", 'F' );
   dataloader->AddVariable( "ele_oldhebc", 'F' );
   dataloader->AddVariable( "ele_oldcircularity", 'F' );
   dataloader->AddVariable( "ele_kfhits", 'F' );
  
   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   //dataloader->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
   //dataloader->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree(Signal,signalWeight);
   dataloader->AddBackgroundTree(Background,backgroundWeight);
   // To give different trees for training and testing, do as follows:
   //
   //     dataloader->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //     dataloader->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   // ```cpp
   // // --- begin ----------------------------------------------------------
   // std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   // Float_t  treevars[4], weight;
   //
   // // Signal
   // for (UInt_t ivar=0; ivar<4; ivar++) signalTree->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<signalTree->GetEntries(); i++) {
   //    signalTree->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < signalTree->GetEntries()/2.0) dataloader->AddSignalTrainingEvent( vars, signalWeight );
   //    else                              dataloader->AddSignalTestEvent    ( vars, signalWeight );
   // }
   //
   // // Background (has event weights)
   // background->SetBranchAddress( "weight", &weight );
   // for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<background->GetEntries(); i++) {
   //    background->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < background->GetEntries()/2) dataloader->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //    else                                dataloader->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   // }
   // // --- end ------------------------------------------------------------
   // ```
   // End of tree registration
   // Set individual event weights (the variables must exist in the original TTree)
   // -  for signal    : `dataloader->SetSignalWeightExpression    ("weight1*weight2");`
   // -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
   //ja zakomentira dataloader->SetBackgroundWeightExpression( "weight" );
   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
   // Tell the dataloader how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   //
   // To also specify the number of testing events, use:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut,
   //         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable
   // Cut optimisation
   
   // Boosted Decision Trees
   // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=2.0%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3" );
  /* if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );*/
  //For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAt001","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------
   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   // --------------------------------------------------------------
   // Save the output
   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   delete factory;
   delete dataloader;

}


void Anlayzer::TMVA() 
{
    TFile* f = new TFile("TMVA.root");

    TGraph* TMVA_signal = (TGraph*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_S");
    TGraph* TMVA_background = (TGraph*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_B");
    TH1F* ROC_curve = (TH1F*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_effBvsS");

    auto canvas = new TCanvas("canvas", "canvas", 1900, 800);
    canvas->Divide(2);
    gStyle->SetOptStat(0);

    canvas->cd(1);
    TMVA_signal->SetLineColor(kRed);
    TMVA_background->SetLineColor(kBlue);
    TMVA_signal->SetTitle("MVA results");
    TMVA_signal->Draw("histo");
    TMVA_background->Draw("histo same");

    TLegend* legend = new TLegend(0.8, 0.8, 0.9, 0.9);
    legend->AddEntry(TMVA_signal, "Signal", "l");
    legend->AddEntry(TMVA_background, "Background", "l");
    legend->Draw();

    canvas->cd(2);
    ROC_curve->SetLineColor(kGreen);
    std::cout << ROC_curve->Interpolate(0.9) * 100.0 << "% background for 90% signal" << std::endl; 
    ROC_curve->Draw();

    canvas->SaveAs("MVA.png");
}



