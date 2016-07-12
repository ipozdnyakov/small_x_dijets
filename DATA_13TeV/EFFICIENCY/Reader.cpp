#include <TTree.h>
#include <stdlib.h>
#include <iostream>
#include <TH1.h>
#include "TKey.h"
#include "TFile.h"
#include "TMath.h"
#include <vector>
#include <math.h>

#include "reader.h"
#include "finder.h"
#define pi 3.1415926

using namespace std;

void treereader(Int_t *n_event_cntr, Int_t *n_event_fwd, TString name,
        TH1D *pt_cntr, TH1D *eta_cntr, TH1D *phi_cntr,
        TH1D *pt_cntr_mb, TH1D *eta_cntr_mb, TH1D *phi_cntr_mb,
        TH1D *pt_fwd, TH1D *eta_fwd, TH1D *phi_fwd,
        TH1D *pt_fwd_mb, TH1D *eta_fwd_mb, TH1D *phi_fwd_mb,     
   	TH2D *pt_cntr_2D, TH2D *pt_cntr_mb_2D,
        TH2D *pt_fwd_2D, TH2D *pt_fwd_mb_2D,
        TH2D *eta_cntr_2D, TH2D *eta_cntr_mb_2D,
        TH2D *eta_fwd_2D, TH2D *eta_fwd_mb_2D,
	TH1D *eta_cntr_1, TH1D *eta_cntr_2, TH1D *eta_cntr_3,
	TH1D *eta_cntr_mb_1, TH1D *eta_cntr_mb_2, TH1D *eta_cntr_mb_3,
	TH1D *eta_fwd_1, TH1D *eta_fwd_2, TH1D *eta_fwd_3,
	TH1D *eta_fwd_mb_1, TH1D *eta_fwd_mb_2, TH1D *eta_fwd_mb_3,
	TH1D *ps_cntr, TH1D *ps_fwd,
        Double_t FWD_weight
        ){

	vector<Double_t> pt_v, y_v, phi_v, eta_v;
	vector<Double_t>::iterator m, n, q;

	Int_t nentries = 0, nEvent = 0;

	Int_t CNTR = -1, FWD = -1;
	Int_t CNTR_mb = 0, FWD_mb_p = 0, FWD_mb_m = 0;
	Int_t i_lead = -1, i_sublead = -1;
	Double_t pt_lead = -1, pt_sublead = -1;

        Double_t pt = 0, eta = 0, phi = 0, rap = 0, wght = 0;
        Int_t iEvent, iRun, nPV;
        Double_t weight = 0.;

TFile Jfile(name);
TTree* tree;
tree = (TTree*) Jfile.Get("JetCollection/jet_tree");
nentries = tree->GetEntries();
cout << "Entries: " << nentries << "\n";

tree->SetBranchAddress("pt",&pt);
tree->SetBranchAddress("eta",&eta);
tree->SetBranchAddress("phi",&phi);
tree->SetBranchAddress("rap",&rap);
//tree->SetBranchAddress("weight",&wght);

tree->SetBranchAddress("nPV",&nPV);
tree->SetBranchAddress("iEvt",&iEvent);
tree->SetBranchAddress("iRun",&iRun);
tree->SetBranchAddress("CNTR",&CNTR);
tree->SetBranchAddress("FWD",&FWD);

tree->GetEntry(0);
nEvent = iEvent;

for(int i = 0 ; i < nentries ; ++i){
	tree->GetEntry(i);
	weight = 1.;

	if(iEvent == nEvent){//in Event
		if(pt > 15){//minimum-bias triggers
			pt_v.push_back(pt);
			y_v.push_back(rap);
			eta_v.push_back(eta);
			phi_v.push_back(phi);
			CNTR_mb++;
			if(eta > 2) FWD_mb_p++;
			if(eta < -2) FWD_mb_m++;
		}
	}else{//out Event
	//back initialization PART-1
	nEvent = iEvent;
	i = (i-1);
	tree->GetEntry(i);
	//-------------------------
//if((iRun == 254989)){
if(nPV == 1){
	//TRIGGER EFFICIENCY ANALYSIS
	ps_cntr->Fill(CNTR);
		//if(CNTR > 0) cout << CNTR << " ";
	ps_fwd->Fill(FWD);
		//if(FWD > 0) cout << FWD << " ";
	
//if(CNTR < 3){ //prescale cut <= 1

	pt_lead = -1;
	pt_sublead = -1;
	i_lead = -1;
	i_sublead = -1;

if(pt_v.size() > 1){

        for(int j = 0; j < pt_v.size(); j++){
		if(pt_v[j] > pt_sublead){

			pt_sublead = pt_v[j];
			i_sublead = j;

			if(pt_v[j] > pt_lead){
				pt_sublead = pt_lead;
				i_sublead = i_lead;
				pt_lead = pt_v[j];
				i_lead = j;
			}
		}
	}

//if((fabs(eta_v[i_sublead]) > 3)&&(fabs(eta_v[i_lead]) > 3)){ //SELECT REGION

	if(CNTR_mb > 1){
	(*n_event_cntr)++;
		pt_cntr_mb->Fill(pt_v[i_sublead],weight);
		eta_cntr_mb->Fill(eta_v[i_sublead],weight);
		phi_cntr_mb->Fill(phi_v[i_sublead],weight);

		if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 35)){
		        for(int j = 0; j < eta_v.size(); j++){
				eta_cntr_mb_1->Fill(eta_v[j],weight);
			}
		}
		if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 25)){
		        for(int j = 0; j < eta_v.size(); j++){
				eta_cntr_mb_2->Fill(eta_v[j],weight);
			}
		}
		if((pt_v[i_lead] > 30)&&(pt_v[i_sublead] > 20)){
		        for(int j = 0; j < eta_v.size(); j++){
				eta_cntr_mb_3->Fill(eta_v[j],weight);
			}
		}

                pt_cntr_mb_2D->Fill(pt_v[i_lead],pt_v[i_sublead],weight);
                eta_cntr_mb_2D->Fill(eta_v[i_lead],eta_v[i_sublead],weight);

		if(CNTR > 0){
			pt_cntr->Fill(pt_v[i_sublead],weight*CNTR);
			eta_cntr->Fill(eta_v[i_sublead],weight*CNTR);
			phi_cntr->Fill(phi_v[i_sublead],weight*CNTR);

			if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 35)){
			        for(int j = 0; j < eta_v.size(); j++){
					eta_cntr_1->Fill(eta_v[j],weight*CNTR);
				}
			}
			if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 25)){
			        for(int j = 0; j < eta_v.size(); j++){
					eta_cntr_2->Fill(eta_v[j],weight*CNTR);
				}
			}
			if((pt_v[i_lead] > 30)&&(pt_v[i_sublead] > 20)){
		        	for(int j = 0; j < eta_v.size(); j++){
					eta_cntr_3->Fill(eta_v[j],weight*CNTR);
				}
			}
	
			pt_cntr_2D->Fill(pt_v[i_lead],pt_v[i_sublead],weight*CNTR);
			eta_cntr_2D->Fill(eta_v[i_lead],eta_v[i_sublead],weight*CNTR);
		}
	//}//close if(CNTR_mb)

	if((FWD_mb_m > 0)&&(FWD_mb_p > 0)&&(fabs(eta_v[i_lead]) > 2)&&(fabs(eta_v[i_sublead]) > 2)&&(eta_v[i_lead]*eta_v[i_sublead] < 0)){
		(*n_event_fwd)++;
			pt_fwd_mb->Fill(pt_v[i_sublead],weight);
			eta_fwd_mb->Fill(eta_v[i_sublead],weight);
			phi_fwd_mb->Fill(phi_v[i_sublead],weight);

			if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 35)){
			        for(int j = 0; j < eta_v.size(); j++){
					eta_fwd_mb_1->Fill(eta_v[j],weight);
				}
			}
			if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 25)){
			        for(int j = 0; j < eta_v.size(); j++){
					eta_fwd_mb_2->Fill(eta_v[j],weight);
				}
			}
			if((pt_v[i_lead] > 30)&&(pt_v[i_sublead] > 20)){
		        	for(int j = 0; j < eta_v.size(); j++){
					eta_fwd_mb_3->Fill(eta_v[j],weight);
				}
			}

                	pt_fwd_mb_2D->Fill(pt_v[i_lead],pt_v[i_sublead],weight);
        	        eta_fwd_mb_2D->Fill(eta_v[i_lead],eta_v[i_sublead],weight);

			if(FWD > 0){
				pt_fwd->Fill(pt_v[i_sublead],weight*FWD);
				eta_fwd->Fill(eta_v[i_sublead],weight*FWD);
				phi_fwd->Fill(phi_v[i_sublead],weight*FWD);

				if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 35)){
				        for(int j = 0; j < eta_v.size(); j++){
						eta_fwd_1->Fill(eta_v[j],weight*FWD);
					}
				}
				if((pt_v[i_lead] > 35)&&(pt_v[i_sublead] > 25)){
				        for(int j = 0; j < eta_v.size(); j++){
						eta_fwd_2->Fill(eta_v[j],weight*FWD);
					}
				}
				if((pt_v[i_lead] > 30)&&(pt_v[i_sublead] > 20)){
			        	for(int j = 0; j < eta_v.size(); j++){
						eta_fwd_3->Fill(eta_v[j],weight*FWD);
					}
				}

				pt_fwd_2D->Fill(pt_v[i_lead],pt_v[i_sublead],weight*FWD);
				eta_fwd_2D->Fill(eta_v[i_lead],eta_v[i_sublead],weight*FWD);
			}
	}//close if(FWD_mb_m/p ...)
	}//close if(CNTR_mb)

//}//run number
}//nPV == 1
//}//ETA pt_lead, pt_sublead
}//pt_v.size() > 1
//}//CNTR < 3

	//back initialization PART-2
	pt_v.clear();
	y_v.clear();
	phi_v.clear();
	eta_v.clear();

	FWD = -1;
	CNTR = -1;
	CNTR_mb = 0;
	FWD_mb_p = 0;
	FWD_mb_m = 0;
   	}
}
//cout << *n_event << "\n";
};

