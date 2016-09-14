#include<TFile.h>
#include"observable.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(TString dir_name, TString name, double *bins, int n_bins):name(name){

        sum_of_weights = new TH1D(name, dir_name, n_bins - 1, bins);
        sum_of_weights->Sumw2();

        sum_of_square_weights = new TH1D(name, dir_name, n_bins - 1, bins);
        sum_of_square_weights->Sumw2();

}

void Observable::catchEvent(Event *event){
	
	this->n_events++;

}

void Observable::writeToFile(TString name){

	TFile file_res(name + this->name + ".root","RECREATE");
	sum_of_weights->Write();
	sum_of_square_weights->Write();

};

void Observable::plotToFile(TString name){

};
