#include<iostream>
#include<TFile.h>
#include"observable.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(TString name, TString title, const double *bins, int n_bins):name(name){

        sum_w = new TH1D(name + "_sum_w", title, n_bins, bins);
        sum_w->Sumw2();

        sum_w2 = new TH1D(name + "_sum_w2", title, n_bins, bins);
        sum_w2->Sumw2();

        jec = new TH1D(name + "_jec", title, n_bins, bins);
        jec->Sumw2();

        unc = new TH1D(name + "_unc", title, n_bins, bins);
        unc->Sumw2();

        average_jec = new TH1D(name + "_average_jec", title, n_bins, bins);
        average_unc = new TH1D(name + "_average_unc", title, n_bins, bins);

};

void Observable::CatchObject(Object *object, string data_name){
	
	this->n_events++;
	vector<vector<double>> jets_data;

	jets_data = object->GetJetsData(data_name);
	this->FillData(jets_data, object->weight);
};

void Observable::FillData(vector<vector<double>> data, double weight){

        for(int i = 1; i < data.size(); i++){
		if(data[i-1].size() != data[i].size()){
			cout << "PROCESSING ERROR: vectors of data do not match - data lost\n";
			return;
		}
	}

        for(int i = 0; i < data[0].size(); i++){
		this->sum_w->Fill(data[2][i], weight);
		this->sum_w2->Fill(data[2][i], weight*weight);
		this->unc->Fill(data[2][i], data[1][i]*weight);
		this->jec->Fill(data[2][i], data[0][i]*weight);
                this->n_entries++;

	}

};

void Observable::WriteToFile(TString name){

	TFile file_res(name,"UPDATE");

	sum_w->Write();
	sum_w2->Write();
	average_jec->Write();
	average_unc->Write();

	file_res.Close();
};

void Observable::AverageAndNormalize(){

	if(this->averaged_and_normalized){
		cout << "PROCESSING ERROR: Observable already averaged and normalized!\n";
		return;
	}

	average_jec->Divide(jec, sum_w);
	average_unc->Divide(unc, sum_w);

	this->averaged_and_normalized = true;

};

void Observable::PlotToFile(TString name){

};
