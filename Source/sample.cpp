#include <TTree.h>
#include <stdlib.h>
#include <iostream>
#include <TH1.h>
#include "TKey.h"
#include "TFile.h"
#include "TMath.h"
#include <vector>
#include <math.h>

#include <fstream>
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "observable.h"
#include "sample.h"
#include "finder.h"
#define pi 3.1415926

using namespace std;

void Sample::ReadSample( 
	Observable *MN_jets,
        Double_t pt_min_1, Double_t pt_min_2, Double_t FWD_weight,  Double_t pt_veto,
	JetCorrectionUncertainty *unc
        ){

    //Open file with names of data files
        ifstream data_files("./listing/" + this->name);
	cout << "\t-reading data files from " << this->name << ":\n";

    //Read each input file from the sample
        string file_name;
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\n";
                this->ReadFile(file_name, MN_jets, pt_min_1, pt_min_2, FWD_weight, pt_veto, unc);
        }
};

void Sample::ReadFile(
	string name,
	Observable *MN_jets,
        Double_t pt_min_1, Double_t pt_min_2, Double_t FWD_weight,  Double_t pt_veto,
	JetCorrectionUncertainty *unc
        ){

	TString file_name = name;
	vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
	vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
	vector<Double_t>::iterator m, n, q;
	vector<int> MN_index;

        Bool_t veto = true;
	Int_t nentries = 0, nEvent = 0;
        Double_t dy_MN = 0., dphi_MN = 0.;

        Double_t pt = 0, eta = 0, phi = 0, rap = 0, wght = 0;
        Int_t iEvent, iRun, nPV;
	Int_t CNTR = -1, FWD = -1;
        Double_t weight = 0.;

TFile Jfile(file_name);
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
tree->SetBranchAddress("FWD3",&FWD);

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
	}else{//out Event
	//back initialization PART-1
	nEvent = iEvent;
	i = (i-1);
	tree->GetEntry(i);
	//-------------------------
if(nPV == 1){

if((pt_v_2.size() > 1)&&(pt_v_1.size() > 0)){
	if(CNTR > 0) MN_jets->n_event_cntr++;
	if(FWD > 0) MN_jets->n_event_fwd++;
if(CNTR > 0){
	CNTR = 1; weight = weight*CNTR;
	//!!!MERGING SHOULD BE ADDED THROUGHT GENERIC
	//inclusive should be added throught generic

	MN_index = find_MN(y_v_1, y_v_2);
    		MN_jets->pt->Fill(pt_v_1[MN_index[0]],weight);
    		MN_jets->y->Fill(y_v_1[MN_index[0]],weight);
    		MN_jets->phi->Fill(phi_v_1[MN_index[0]],weight);

    		MN_jets->pt->Fill(pt_v_2[MN_index[1]],weight);
    		MN_jets->y->Fill(y_v_2[MN_index[1]],weight);
    		MN_jets->phi->Fill(phi_v_2[MN_index[1]],weight);

	dy_MN = find_dy_MN(y_v_1, y_v_2);
	dphi_MN = find_dphi_MN(y_v_1, phi_v_1, y_v_2, phi_v_2);

	MN_jets->dphi[0]->Fill(dphi_MN,weight);
	MN_jets->dy->Fill(dy_MN,weight);
	MN_jets->w2_dy->Fill(dy_MN,weight*weight);
	MN_jets->dphi_dy->Fill(dphi_MN,dy_MN,weight);

	if((dy_MN > 0.)&&(dy_MN < 3.))  MN_jets->dphi[1]->Fill(dphi_MN,weight);
	if((dy_MN > 3.)&&(dy_MN < 6.))  MN_jets->dphi[2]->Fill(dphi_MN,weight);
	if((dy_MN > 6.)&&(dy_MN < 9.4)) MN_jets->dphi[3]->Fill(dphi_MN,weight);

	MN_jets->cos_1->Fill(dy_MN, weight*cos(pi - dphi_MN));
	MN_jets->cos2_1->Fill(dy_MN,weight*pow(cos(pi - dphi_MN),2));
	MN_jets->cos_2->Fill(dy_MN,weight*cos(2*(pi - dphi_MN)));
	MN_jets->cos2_2->Fill(dy_MN,weight*pow(cos(2*(pi - dphi_MN)),2));
	MN_jets->cos_3->Fill(dy_MN,weight*cos(3*(pi - dphi_MN)));
	MN_jets->cos2_3->Fill(dy_MN,weight*pow(cos(3*(pi - dphi_MN)),2));

	if((pt_v_1.size() > 0)&&(pt_v_2.size() == 2)&&veto){
		MN_jets->excl_dy->Fill(dy_MN,weight);
	}

}//only CNTR events
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
};

