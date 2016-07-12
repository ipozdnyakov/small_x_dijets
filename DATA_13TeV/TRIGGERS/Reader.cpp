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
        TH1D *pt_h, TH1D *eta_h, TH1D *phi_h,
	TH1D *dy_cntr_MN, TH1D *dy_fwd_MN,
	TH1D *dy_cntr, TH1D *dy_fwd,
	TH1D *dy_cntr_minus_fwd_MN,
	TH1D *dy_cntr_minus_fwd,
        TH1D *pt_cntr,
        TH1D *pt_fwd, 
        TH1D *eta_cntr,
        TH1D *eta_fwd,
	TH1D *phi_cntr_1,  TH1D *phi_cntr_2,  TH1D *phi_cntr_3,
	TH1D *phi_fwd_1,  TH1D *phi_fwd_2,  TH1D *phi_fwd_3,
        TH1D *nPV_cntr, TH1D *nPV_fwd,
        Double_t pt_min_1, Double_t pt_min_2, Double_t FWD_weight,  Double_t pt_veto
        ){

	vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
	vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
	vector<Double_t> pt_v, eta_v;
	vector<Double_t>::iterator m, n, q;
        vector<int> MN_index;

        Bool_t veto = true;
	Int_t nentries = 0, nEvent = 0;
        Double_t dy_MN = 0., dphi_MN = 0.;
        vector<Double_t> dy_INCL;

        Double_t pt = 0, eta = 0, phi = 0, rap = 0, wght = 0;
        Int_t iEvent, iRun, nPV;
	Int_t CNTR = -1, FWD = -1;
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
tree->SetBranchAddress("CNTR",&CNTR);
tree->SetBranchAddress("FWD",&FWD);

tree->GetEntry(0);
nEvent = iEvent;

for(int i = 0 ; i < nentries ; ++i){
	tree->GetEntry(i);
	weight = 1.;

	if(iEvent == nEvent){//in Event
		if((pt > pt_min_1) && (fabs(rap) < 4.7)){
		  pt_v_1.push_back(pt);
		  phi_v_1.push_back(phi);
		  y_v_1.push_back(rap);
		  eta_v_1.push_back(eta);
		}

		if((pt > pt_min_2) && (fabs(rap) < 4.7)){
		  pt_v_2.push_back(pt);
		  phi_v_2.push_back(phi);
		  y_v_2.push_back(rap);
		  eta_v_2.push_back(eta);
		}
		if((pt < pt_min_2)&&(pt > pt_veto)) veto = false;
		if(pt > 15){//minimum-bias triggers
			pt_v.push_back(pt);
			eta_v.push_back(eta);
		}
	}else{//out Event
	//back initialization PART-1
	nEvent = iEvent;
	i = (i-1);
	tree->GetEntry(i);
	//-------------------------
	//PU ANALYSIS
	if(CNTR > 0){
		nPV_cntr->Fill(nPV,weight*CNTR);
	}
	if(FWD > 0){
		nPV_fwd->Fill(nPV,weight*FWD);
	}

if(nPV == 1){

	//INCLUSIVE JETS ANALYSIS
if((pt_v_2.size() > 1)&&(pt_v_1.size() > 0)){

	dy_MN = find_dy_MN(y_v_1, y_v_2);
	dy_INCL = find_dy_INCL(y_v_1, pt_min_1, y_v_2, pt_v_2);
	
	if(CNTR > 0){
		(*n_event_cntr)++;
		dy_cntr_MN->Fill(dy_MN,weight*CNTR);
   		for(int j = 0; j < dy_INCL.size(); j++){
			dy_cntr->Fill(dy_INCL[j],weight*CNTR);
		}
   		for(int j = 0; j < pt_v_2.size(); j++){
	    		pt_cntr->Fill(pt_v_2[j],weight*CNTR);
    			eta_cntr->Fill(eta_v_2[j],weight*CNTR);
			if(fabs(eta_v_2[j]) < 2) phi_cntr_1->Fill(phi_v_2[j],weight*CNTR);
			if((fabs(eta_v_2[j]) > 2)&&(fabs(eta_v_2[j]) < 3)) phi_cntr_2->Fill(phi_v_2[j],weight*CNTR);
			if(fabs(eta_v_2[j]) > 3) phi_cntr_3->Fill(phi_v_2[j],weight*CNTR);
		}
		if(FWD < 0){
			dy_cntr_minus_fwd_MN->Fill(dy_MN,weight*CNTR);
	   		for(int j = 0; j < dy_INCL.size(); j++){
				dy_cntr_minus_fwd->Fill(dy_INCL[j],weight*CNTR);
			}
		}
	}

	if(FWD > 0){
		(*n_event_fwd)++;
		dy_fwd_MN->Fill(dy_MN,weight*FWD);
   		for(int j = 0; j < dy_INCL.size(); j++){
			dy_fwd->Fill(dy_INCL[j],weight*FWD);
		}
   		for(int j = 0; j < pt_v_2.size(); j++){
	    		pt_fwd->Fill(pt_v_2[j],weight*FWD);
    			eta_fwd->Fill(eta_v_2[j],weight*FWD);
			if(fabs(eta_v_2[j]) < 2) phi_fwd_1->Fill(phi_v_2[j],weight*FWD);
			if((fabs(eta_v_2[j]) > 2)&&(fabs(eta_v_2[j]) < 3)) phi_fwd_2->Fill(phi_v_2[j],weight*FWD);
			if(fabs(eta_v_2[j]) > 3) phi_fwd_3->Fill(phi_v_2[j],weight*FWD);
		}
	}

	//MERGING SHOULD GO HERE

   	/*for(int j = 0; j < pt_v_2.size(); j++){
    		pt_h->Fill(pt_v_2[j],weight);
    		eta_h->Fill(y_v_2[j],weight);
    		phi_h->Fill(phi_v_2[j],weight);
	}*/

}//number of jets > 2
}//nPV = 1 cut

	//back initialization PART-2
	veto = true;

	pt_v_1.clear();
	y_v_1.clear();
	phi_v_1.clear();
	eta_v_1.clear();

	pt_v_2.clear();
	y_v_2.clear();
	phi_v_2.clear();
	eta_v_2.clear();

	pt_v.clear();
	eta_v.clear();

	dy_MN = 0.;
	dphi_MN = 0.;
	FWD = -1;
	CNTR = -1;
   	}
}
//cout << *n_event << "\n";
};

