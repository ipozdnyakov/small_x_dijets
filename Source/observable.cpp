#include<iostream>
#include<TFile.h>
#include"observable.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(Object *object, Function *function, TString name){
	this->object = object;
	this->function = function;
	this->name =  function->name + "_" + object->name + "_" + name;

        data = new TH1D(this->name + "_DATA", this->name + "_DATA", function->n_bins, function->bins);
        data->Sumw2();
	data->SetStats(false);

        jecp = new TH1D(this->name + "_JECP", this->name + "_JECP", function->n_bins, function->bins);
        jecp->Sumw2();
	jecp->SetStats(false);

        jecm = new TH1D(this->name + "_JECM", this->name + "_JECM", function->n_bins, function->bins);
        jecm->Sumw2();
	jecm->SetStats(false);

        hpu = new TH1D(this->name + "_HPU", this->name + "_HPU", function->n_bins, function->bins);
        hpu->Sumw2();
	hpu->SetStats(false);

        lpu = new TH1D(this->name + "_LPU", this->name + "_LPU", function->n_bins, function->bins);
        lpu->Sumw2();
	lpu->SetStats(false);
};

void Observable::ReadEvent(Event *event){	
        if(event->nPV == 1){
		this->n_events++;

		object->LoadEvent(event);
		function->CalculateValues(object);
		this->FillValues("data",function->values,function->weights);
		if(event->RunPileUp() == "H"){
			this->FillValues("hpu",function->values,function->weights);
		}
		if(event->RunPileUp() == "L"){
			this->FillValues("lpu",function->values,function->weights);
		}
		function->Clear();
		object->Clear();

		event->JecUp();
		object->LoadEvent(event);
		function->CalculateValues(object);
		this->FillValues("jecp",function->values,function->weights);
		function->Clear();
		object->Clear();
		event->JecCentr();

		event->JecDown();
		object->LoadEvent(event);
		function->CalculateValues(object);
		this->FillValues("jecm",function->values,function->weights);
		function->Clear();
		object->Clear();
		event->JecCentr();
	}
};

void Observable::FillValues(string hist_name, vector<double> values, vector<double> weights){

	if(values.size() != weights.size()){
		cout << "Observable FillValues Error: vectors from function do not match - data lost\n";
		return;
	}

	if(hist_name == "data"){
	        for(int i = 0; i < values.size(); i++){
			this->data->Fill(values[i], weights[i]);
		}
	}

	if(hist_name == "jecp"){
	        for(int i = 0; i < values.size(); i++){
			this->jecp->Fill(values[i], weights[i]);
		}
	}

	if(hist_name == "jecm"){
	        for(int i = 0; i < values.size(); i++){
			this->jecm->Fill(values[i], weights[i]);
		}
	}

	if(hist_name == "hpu"){
	        for(int i = 0; i < values.size(); i++){
			this->hpu->Fill(values[i], weights[i]);
		}
	}

	if(hist_name == "lpu"){
	        for(int i = 0; i < values.size(); i++){
			this->lpu->Fill(values[i], weights[i]);
		}
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
	this->data->Write();
	this->jecp->Write();
	this->jecm->Write();
	//this->hpu->Write();
	//this->lpu->Write();
	file_res.Close();
};
