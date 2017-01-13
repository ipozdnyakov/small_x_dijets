#include<iostream>
#include"result.h"

using namespace std;

Result::Result(TString name){
	this->name = name;
	result = new TH1D();
	syst = new TGraphAsymmErrors();
};

void Result::WriteToFile(TString name){
	TFile file_res(name,"UPDATE");
	this->result->Write();
	this->syst->Write();
	file_res.Close();
	cout << "Result " << this->name << " obtained\n";
};
