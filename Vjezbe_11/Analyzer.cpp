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
double Analyzer::Factorial(int n){
	long int f=1;
	
	if(n!=0)
	{
		for(int i=1;i<=n;i++)
		{
			f*=i;
		}
	}
	return f;
}
double Analyzer::Binomial(int r, int N, double p)
{
	double a,b,binomial;
	a=Factorial(N)/(Factorial(r)*Factorial(N-r));
	b=pow(p,r)*pow(1-p,N-r);
	
	binomial=a*b;
	//cout <<"Binomial: " << binomial << endl;
	return binomial;
}

double Analyzer::sum_upper(int m, int N1, double C)
{
	double temp=0.0,sum=0.0;
	int r1;
	double p_plus=1.0;
	
	
	while(sum<((1.0-C)/2.0))
		{
			for(r1=m+1;r1<=N1;r1++)
				{
					temp+=Binomial(r1,N1,p_plus);
				}
		sum=1.0-temp;
		p_plus-=0.001;
		temp=0.0;
		}
	
	return p_plus;

}

double Analyzer::sum_lower(int m, int N2, double C)
{
	double temp=0.0,sum=0.0;
	int r2;
	double p_minus=0.0;
	
	
	while(sum<((1.0-C)/2.0))
		{
			for(r2=0;r2<=m-1;r2++)
				{
					temp+=Binomial(r2,N2,p_minus);
				}
		sum=1.0-temp;
		p_minus+=0.001;
		temp=0.0;
		}
	
	return p_minus;

}

void Analyzer::Belt(int N, double C)
{
	double p_plus,p_minus;
	int r;
	for(r=0;r<=N;r++)
		{
		p_plus=sum_upper(r,N,C);
		p_minus=sum_lower(r,N,C);
		cout << "Limits for r="<<r<<" successful outcomes out of 10 events is ["<<p_minus<<","<<p_plus<<"]"<<endl;
		}
}

void Analyzer::Draw(int N,double C)
{
	TH1F *upper, *lower;
	upper=new TH1F("upper","upper",N,0,N);
	lower=new TH1F("lower","lower",N,0,N);
	
	int r;
	double p_plus,p_minus;
	for(r=0;r<=N;r++)
	{
		p_plus=sum_upper(r,N,C);
		p_minus=sum_lower(r,N,C);
		
		upper->SetBinContent(r,p_plus);
		lower->SetBinContent(r,p_minus);
	}
	
	TCanvas *canvas;
	canvas=new TCanvas("Belt","Belt",1600,900);
	gStyle->SetOptStat(0);
	
	upper->SetMaximum(1.1);
	upper->SetMinimum(-0.1);
	lower->SetMaximum(1.1);
	lower->SetMinimum(-0.1);
	upper->GetYaxis()->SetRangeUser(0.,1.1);
	lower->GetYaxis()->SetRangeUser(0.,1.1);
	upper->GetXaxis()->SetTitle("r / number of successful events");
	upper->GetYaxis()->SetTitle("p / probability");
	upper->SetTitle("Belt");
	
	TLine *l1,*l2,*l3;
	
	
	l1=new TLine(0,sum_upper(4,N,C),4,sum_upper(4,N,C));
	l2=new TLine(0,sum_lower(4,N,C),4,sum_lower(4,N,C));
	l3=new TLine(4,-0.01,4,sum_upper(4,N,C));
	
	
	l1->SetLineColor(kRed);
	l2->SetLineColor(kRed);
	l3->SetLineColor(kRed);
	l1->SetLineStyle(kDashed);
	l2->SetLineStyle(kDashed);
	l3->SetLineStyle(kDashed);
	
	Int_t color = TColor::GetFreeColorIndex();
	TColor *colour;
	colour=new TColor(color,1.,1.,1.);
	upper->SetFillColor(kBlue);
	lower->SetFillColor(color);

	upper->Draw();
	lower->Draw("same");
	l1->Draw("same");
	l2->Draw("same");
	l3->Draw("same");
	
	canvas->SaveAs("Belt.png");

}
void Analyzer::Dice(int N, double C)
{
	srand(time(NULL));
	int i, j, br, s=0;
	double p_plus, p_minus,p_true=1.0/6;

	for(i=0;i<1000;i++)
	{
		br=0;
		for(j=0;j<N;j++)
			{
				if((rand()%6+1)==6)
				br++;
			}
		
	p_plus=sum_upper(br,N,C);
	p_minus=sum_lower(br,N,C);	
	if(p_plus>=p_true && p_minus<=p_true)
		s++;
	}
	cout<<"Number of experiments (out of 1000) that contain p_true in 10 throws in confidence interval of " << C << " is " << s << endl;	
}
