#include <TTree.h>
#include <fstream>
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "observable.h"
#include "event.h"
#include "sample.h"
#include "finder.h"

#define pi 3.1415926
using namespace std;

template void Sample::ReadSample<MN>(MN *, Double_t , JetCorrectionUncertainty *);
template <class Obs> void Sample::ReadSample( 
	Obs *MN_jets,
        Double_t FWD_weight,
	JetCorrectionUncertainty *unc
){
        ifstream data_files("./listing/" + this->name);
	cout << "\t-reading data files from " << this->name << ":\n";

        string file_name;
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\n";
                this->ReadFile(file_name, MN_jets, FWD_weight, unc);
        }
};


void Sample::ReadFile(
	string name,
	MN *MN_jets,
        Double_t FWD_weight,
	JetCorrectionUncertainty *unc
){

	TString file_name = name;
	Int_t nentries = 0, nEvent = 0;
        Double_t pt = 0, eta = 0, phi = 0, rap = 0, weight = 1.;
        Int_t iEvent, iRun, nPV;
	Int_t CNTR = -1, FWD = -1;

	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get("JetCollection/jet_tree");
	nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\n";

	tree->SetBranchAddress("pt",&pt);
	tree->SetBranchAddress("eta",&eta);
	tree->SetBranchAddress("phi",&phi);
	tree->SetBranchAddress("rap",&rap);
	//tree->SetBranchAddress("weight",&weight);
	tree->SetBranchAddress("nPV",&nPV);
	tree->SetBranchAddress("iEvt",&iEvent);
	tree->SetBranchAddress("CNTR",&CNTR);
	tree->SetBranchAddress("FWD3",&FWD);

	tree->GetEntry(0);
	nEvent = iEvent;

	Event *event = new Event(iEvent,nPV,CNTR,FWD,weight);

	for(int i = 0 ; i < nentries ; i++){
		tree->GetEntry(i);
		if(iEvent == nEvent){				//in Event
			event->AddJet(pt,eta,phi,rap);
		}else{						//out Event
			nEvent = iEvent;
			this->ReadEvent(event, MN_jets, FWD_weight, unc);
			delete event;
			event = new Event(iEvent,nPV,CNTR,FWD,weight);
   		}
	}
};

void Sample::ReadEvent(
	Event *event,
	MN *MN_jets,
        Double_t FWD_weight,
	JetCorrectionUncertainty *unc
){

	vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
	vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
	vector<Double_t>::iterator m, n, q;
	vector<int> MN_index;

        Bool_t veto = true;
        Double_t dy_MN = 0., dphi_MN = 0.;

        for(int i = 0; i < event->pt.size(); i++){

		if((event->pt[i] > MN_jets->pt_min_1) && (fabs(event->rap[i]) < 4.7)){
		  pt_v_1.push_back(event->pt[i]);
		  phi_v_1.push_back(event->phi[i]);
		  y_v_1.push_back(event->rap[i]);
                  eta_v_1.push_back(event->eta[i]);
		}
		if((event->pt[i] > MN_jets->pt_min_2) && (fabs(event->rap[i]) < 4.7)){
		  pt_v_2.push_back(event->pt[i]);
		  phi_v_2.push_back(event->phi[i]);
		  y_v_2.push_back(event->rap[i]);
                  eta_v_2.push_back(event->eta[i]);
		}
		if((event->pt[i] < MN_jets->pt_min_2)&&(event->pt[i] > MN_jets->pt_veto)) veto = false;
	}

	if(event->nPV == 1){

	if((pt_v_2.size() > 1)&&(pt_v_1.size() > 0)){
		if(event->CNTR > 0) MN_jets->n_event_cntr++;
		if(event->FWD > 0) MN_jets->n_event_fwd++;
	if(event->CNTR > 0){
		MN_index = find_MN(y_v_1, y_v_2);
    		MN_jets->pt->Fill(pt_v_1[MN_index[0]],event->weight);
    		MN_jets->y->Fill(y_v_1[MN_index[0]],event->weight);
    		MN_jets->phi->Fill(phi_v_1[MN_index[0]],event->weight);

    		MN_jets->pt->Fill(pt_v_2[MN_index[1]],event->weight);
    		MN_jets->y->Fill(y_v_2[MN_index[1]],event->weight);
    		MN_jets->phi->Fill(phi_v_2[MN_index[1]],event->weight);

		dy_MN = find_dy_MN(y_v_1, y_v_2);
		dphi_MN = find_dphi_MN(y_v_1, phi_v_1, y_v_2, phi_v_2);

		MN_jets->dphi[0]->Fill(dphi_MN,event->weight);
		MN_jets->dy->Fill(dy_MN,event->weight);
		MN_jets->w2_dy->Fill(dy_MN,event->weight*event->weight);
		MN_jets->dphi_dy->Fill(dphi_MN,dy_MN,event->weight);

		if((dy_MN > 0.)&&(dy_MN < 3.))  MN_jets->dphi[1]->Fill(dphi_MN,event->weight);
		if((dy_MN > 3.)&&(dy_MN < 6.))  MN_jets->dphi[2]->Fill(dphi_MN,event->weight);
		if((dy_MN > 6.)&&(dy_MN < 9.4)) MN_jets->dphi[3]->Fill(dphi_MN,event->weight);

		MN_jets->cos_1->Fill(dy_MN, event->weight*cos(pi - dphi_MN));
		MN_jets->cos2_1->Fill(dy_MN,event->weight*pow(cos(pi - dphi_MN),2));
		MN_jets->cos_2->Fill(dy_MN,event->weight*cos(2*(pi - dphi_MN)));
		MN_jets->cos2_2->Fill(dy_MN,event->weight*pow(cos(2*(pi - dphi_MN)),2));
		MN_jets->cos_3->Fill(dy_MN,event->weight*cos(3*(pi - dphi_MN)));
		MN_jets->cos2_3->Fill(dy_MN,event->weight*pow(cos(3*(pi - dphi_MN)),2));

		if((pt_v_1.size() > 0)&&(pt_v_2.size() == 2)&&veto){
			MN_jets->excl_dy->Fill(dy_MN,event->weight);
		}

	}//only CNTR events
	}//enough jets
	}//nPV == 1

};
