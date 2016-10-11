#include<iostream>
#include<TFile.h>
#include"observable.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(Object *object, Function *function, TString name){
	this->object = object;
	this->function = function;
	this->name =  function->name + "_" + object->name + "_" + name;
        sum_w = new TH1D(this->name, this->name, function->n_bins, function->bins);
        sum_w->Sumw2();
	sum_w->SetStats(false);
};

void Observable::ReadEvent(Event *event){	
	this->n_events++;
	object->LoadEvent(event);
	function->CalculateValues(object);
	if((false)&&(function->values.size() > 0)){
		event->Print();
		object->Print();
		function->Print();
	}
	this->FillValues(function->values,function->weights);
	function->Clear();
	object->Clear();
};

void Observable::FillValues(vector<double> values, vector<double> weights){

	if(values.size() != weights.size()){
		cout << "Observable FillValues Error: vectors from function do not match - data lost\n";
		return;
	}

        for(int i = 0; i < values.size(); i++){
		this->sum_w->Fill(values[i], weights[i]);
	}
};

void Observable::AverageAndNormalize(){
	if(this->averaged_and_normalized){
		cout << "Observable AverageAndNormalize Error: Observable already averaged and normalized!\n";
		return;
	}
	this->averaged_and_normalized = true;
};

void Observable::WriteToFile(TString name){
	TFile file_res(name,"UPDATE");
	cout << "Observable " << this->name << " with " << this->n_events << " events\n";
	this->sum_w->Write();
	file_res.Close();
};

