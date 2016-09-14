#include<TFile.h>
#include"observable.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Observable::Observable(TString name, TString title, const double *bins, int n_bins):name(name){

        sum_of_weights = new TH1D(name + "_sum_of_weights", title, n_bins, bins);
        sum_of_weights->Sumw2();

        sum_of_square_weights = new TH1D(name + "_sum_of_square_weights", title, n_bins, bins);
        sum_of_square_weights->Sumw2();

}

void Observable::CatchEvent(Event *event){
	
	this->n_events++;

	this->sum_of_weights->Fill(1.,event->weight);

/*        for(int i = 0; i < event->pt.size(); i++){
                this->pt->Fill(event->pt[i]);
                this->eta->Fill(event->eta[i]);
                this->y->Fill(event->rap[i]);
                this->phi->Fill(event->phi[i]);
                this->n_entries++;
        }*/

}

void Observable::WriteToFile(TFile *file_res){

	file_res->cd();
	sum_of_weights->Write();
	sum_of_square_weights->Write();

};

void Observable::PlotToFile(TString name){

};
