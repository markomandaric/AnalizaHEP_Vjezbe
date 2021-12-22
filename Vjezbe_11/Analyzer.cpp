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

void Analyzer::Draw()
{
}
