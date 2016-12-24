#include<iostream>
#include"result.h"

using namespace std;
#define pi 3.1415926

Result::Result(TString name){
	this->name = name;
};

void Result::WriteToFile(TString name){
	TFile file_res(name,"UPDATE");
	cout << "Result " << this->name << " with " << " events\n";
	this->result->Write();
	this->syst->Write();
	file_res.Close();
};
