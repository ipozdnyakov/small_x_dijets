#include<iostream>
#include<TFile.h>
#include"observable.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(Object *object, Function *function, TString name){
	this->object = object;
	this->function = function;
	this->name =  function->name + "_" + object->name + "_" + name;
        sum_w = new TH1D(this->name + "_w", this->name, function->n_bins, function->bins);
        sum_w->Sumw2();
        sum_i = new TH1D(this->name + "_i", this->name, function->n_bins, function->bins);
        sum_i->Sumw2();
};

void Observable::ReadEvent(Event *event){	
	this->n_events++;
	object->LoadEvent(event);
	function->CalculateValues(object);
	this->FillValues(function->values,function->weights);
	function->Clear();
	object->Clear();
};

void Observable::FillValues(vector<double> values, vector<double> weights){

	if(values.size() != weights.size()){
		cout << "PROCESSING ERROR: vectors of data do not match - data lost\n";
		return;
	}

        for(int i = 0; i < values.size(); i++){
		this->sum_i->Fill(values[i]);
		this->sum_w->Fill(values[i], weights[i]);
	}
};

void Observable::AverageAndNormalize(){

	if(this->averaged_and_normalized){
		cout << "PROCESSING ERROR: Observable already averaged and normalized!\n";
		return;
	}

	this->averaged_and_normalized = true;
};

void Observable::WriteToFile(TString name){

	TFile file_res(name,"UPDATE");

	sum_w->Write();
	sum_i->Write();

	file_res.Close();
};

