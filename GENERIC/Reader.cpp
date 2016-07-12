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
        TH1D *pt_h, TH1D *y_h, TH1D *phi_h, TH1D *dphi_0, TH1D *dphi_1, TH1D *dphi_2, TH1D *dphi_3,  TH1D *dy,
	TH1D *w2_dy, TH1D *excl_dy,
        TH1D *cos_1, TH1D *cos_2, TH1D *cos_3, TH1D *cos2_1, TH1D *cos2_2, TH1D *cos2_3,
        TH2D *dphi_dy,
        Double_t pt_min_1, Double_t pt_min_2, Double_t FWD_weight,  Double_t pt_veto
        ){

	vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
	vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
	vector<Double_t>::iterator m, n, q;

        Bool_t veto = true;
	Int_t nentries = 0, nEvent = 0;
        Double_t dy_MN = 0., dphi_MN = 0.;

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

if(nPV == 1){
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
	}else{//out Event
	//back initialization PART-1
	nEvent = iEvent;
	i = (i-1);
	tree->GetEntry(i);
	//-------------------------
if((pt_v_2.size() > 1)&&(pt_v_1.size() > 0)){
	if(CNTR > 0) (*n_event_cntr)++;
	if(FWD > 0) (*n_event_fwd)++;

if((CNTR > 0)||(FWD > 0)){

	//!!!MERGING SHOULD BE ADDED THROUGHT GENERIC

   	for(int j = 0; j < pt_v_2.size(); j++){
    		pt_h->Fill(pt_v_2[j],weight);
    		y_h->Fill(y_v_2[j],weight);
    		phi_h->Fill(phi_v_2[j],weight);
	}

	dy_MN = find_dy_MN(y_v_1, y_v_2);
	dphi_MN = find_dphi_MN(y_v_1, phi_v_1, y_v_2, phi_v_2);

	dphi_0->Fill(dphi_MN,weight);
	dy->Fill(dy_MN,weight);
	w2_dy->Fill(dy_MN,weight*weight);
	dphi_dy->Fill(dphi_MN,dy_MN,weight);

	if((dy_MN > 0.)&&(dy_MN < 3.))dphi_1->Fill(dphi_MN,weight);
	if((dy_MN > 3.)&&(dy_MN < 6.))dphi_2->Fill(dphi_MN,weight);
	if((dy_MN > 6.)&&(dy_MN < 9.4))dphi_3->Fill(dphi_MN,weight);

	cos_1->Fill(dy_MN, weight*cos(pi - dphi_MN) );
	cos2_1->Fill(dy_MN,weight*pow(cos(pi - dphi_MN),2));
	cos_2->Fill(dy_MN,weight*cos(2*(pi - dphi_MN)));
	cos2_2->Fill(dy_MN,weight*pow(cos(2*(pi - dphi_MN)),2));
	cos_3->Fill(dy_MN,weight*cos(3*(pi - dphi_MN)));
	cos2_3->Fill(dy_MN,weight*pow(cos(3*(pi - dphi_MN)),2));

	if((pt_v_1.size() == 1)&&(pt_v_2.size() == 2)&&veto){
		excl_dy->Fill(dy_MN,weight);
	}
}//CNTR or FWD trigger
}//enough jets
}//nPV == 1

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

	dy_MN = 0.;
	dphi_MN = 0.;
	FWD = -1;
	CNTR = -1;
   	}
}
//cout << *n_event << "\n";
};

