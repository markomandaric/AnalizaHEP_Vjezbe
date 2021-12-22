#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TColor.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <vector>
#include <TGraph.h>
#include <TH2F.h>
#include <TF1.h>
#include <stdlib.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>
using namespace std;

Analyzer::Analyzer()
{
}

void Analyzer::Draw()
{

	auto *canvas = new TCanvas("canvas","canvas",200,10,700,500);	
	canvas->Divide(2);
	canvas->cd(1);
	gStyle->SetOptFit();
	Double_t a[5]={9.8,21.2,34.5,39.9,48.5};
	Double_t a_error[5]={1.0,1.9,3.1,3.9,5.1};
	Double_t F[5]={1.0,2.0,3.0,4.0,5.0}; 	
	Double_t F_error[5]={0.0,0.0,0.0,0.0,0.0};
	Double_t theta,min,sigma_lower, sigma_upper,mass,x1,x2;
	TF1* fit;
	fit=new TF1("fit", "1/[0]*x",0,10);
	fit->SetParameter(0,0.1);
	fit->SetParName(0,"mass");

	auto gr = new TGraphErrors(5,F,a,F_error,a_error);
	gr->GetXaxis()->SetTitle("F [N]");
	gr->GetYaxis()->SetTitle("a [m/s^{2}]");
	gr->Fit(fit);
	gr->Draw("AP");
	
	canvas->cd(2);

	TF1* chi_square;
	chi_square=new TF1("chi_square","(pow(([0]-[1]*x),2)/([2]*[2]))+(pow(([3]-[4]*x),2)/([5]*[5]))+(pow(([6]-[7]*x),2)/([8]*[8]))+(pow(([9]-[10]*x),2)/([11]*[11]))+(pow(([12]-[13]*x),2)/([14]*[14]))",9,11);
	for(int i=0;i<5*5;i+=3)
	{
		chi_square->SetParameter(i,a[i/3]);
		chi_square->SetParameter(i+1,F[i/3]);
		chi_square->SetParameter(i+2,a_error[i/3]);
	}
	
	chi_square->SetLineColor(kCyan);
    	chi_square->GetYaxis()->SetRangeUser(0, 10.0);
    	chi_square->SetTitle("Chi-square; #hat{#theta}; #chi^{2}");
	
	chi_square->Draw();

	min=chi_square->GetMinimum();
	theta=chi_square->GetMinimumX();
	mass=1/theta;
	cout << "mass = " << mass <<endl;
	
	x1 = chi_square->GetX(min + 1.0, 6.0, chi_square->GetMinimumX() - 0.0001);
        x2 = chi_square->GetX(min + 1.0, chi_square->GetMinimumX() + 0.0001, 14.0);

    	sigma_lower = chi_square->GetMinimumX() - x1;
    	sigma_upper = x2 - chi_square->GetMinimumX();
    	cout << "Sigma_lower = " << -1.0*(sigma_lower/pow(theta, 2)) <<endl;
    	cout << "Sigma_upper = " << 1.0*(sigma_upper/pow(theta, 2)) <<endl;

	auto l1 = new TLine(x1, min + 1.0, x2, min + 1.0);
    	auto l2 = new TLine(theta, 0, theta, min);
    	auto l3 = new TLine(x1, 0.0, x1, min + 1.0);
    	auto l4 = new TLine(x2, 0.0, x2, min + 1.0);
    	l1->SetLineStyle(kDashed);
    	l2->SetLineStyle(kDashed);
    	l3->SetLineStyle(kDashed);
    	l4->SetLineStyle(kDashed);
    	l1->Draw();
    	l2->Draw();
    	l3->Draw();
    	l4->Draw();
	



	canvas->SaveAs("chi_square.png");

}
