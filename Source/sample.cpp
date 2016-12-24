#include<fstream>
#include<iostream>
#include<TTree.h>
#include<TFile.h>
#include"sample.h"
#include"object.h"
#include"event.h"

#define pi 3.1415926
using namespace std;

void Sample::ReadSample(Measurement *measurement){

        string file_name;


	if(this->name == "13TeV_data_2015C_FSQJets3") this->Set13TeVNamesCFF();
	if(this->name == "FSQJets_2015_2016") this->Set13TeVNames();
	if(this->name == "datasets/FSQJets3_2015C_VdMaugust") this->Set13TeVNames();
	if(this->name == "datasets/7TeV_JetMETTau_Centr") this->Set7TeVNames(); 

        ifstream data_files("./Docs/listing/" + this->name);
	cout << "\t-reading data files from set " << this->name << ":\n";
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, measurement);
        }
	cout << "\n";

};

void Sample::ReadFile(string name, Measurement *measurement){

	TString file_name = name;
	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get(this->tree_name);
	Int_t nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\t";

        Int_t iLumi = 0, iEvent = 0, iRun = 0, nPV = 0;
	Int_t CNTR = 1, FWD2 = -1, FWD3 = -1;
	Int_t CNTR_ps = 1, FWD2_ps = -1, FWD3_ps = -1;
        double pt = 0., phi = 0., eta = 0., rap = 0., cor = 0., unc = 0.;
        vector<float> *pt_v = 0, *phi_v = 0, *eta_v = 0, *rap_v = 0, *cor_v = 0, *unc_v = 0;

	if(this->lumi_num_name != "") tree->SetBranchAddress(this->lumi_num_name, &iLumi);
	if(this->run_num_name != "") tree->SetBranchAddress(this->run_num_name, &iRun);
	if(this->event_num_name != "") tree->SetBranchAddress(this->event_num_name, &iEvent);
	if(this->nPV_name != "") tree->SetBranchAddress(this->nPV_name, &nPV);
	if(this->CNTR_trg_name != "") tree->SetBranchAddress(this->CNTR_trg_name, &CNTR);
	if(this->FWD2_trg_name != "") tree->SetBranchAddress(this->FWD2_trg_name, &FWD2);
	if(this->FWD3_trg_name != "") tree->SetBranchAddress(this->FWD3_trg_name, &FWD3);
	if(this->CNTR_trg_ps_name != "") tree->SetBranchAddress(this->CNTR_trg_ps_name, &CNTR_ps);
	if(this->FWD2_trg_ps_name != "") tree->SetBranchAddress(this->FWD2_trg_ps_name, &FWD2_ps);
	if(this->FWD3_trg_ps_name != "") tree->SetBranchAddress(this->FWD3_trg_ps_name, &FWD3_ps);

	if(this->pt_name != "") tree->SetBranchAddress(this->pt_name, &pt);
	if(this->rap_name != "") tree->SetBranchAddress(this->rap_name, &rap);
	if(this->eta_name != "") tree->SetBranchAddress(this->eta_name, &eta);
	if(this->phi_name != "") tree->SetBranchAddress(this->phi_name, &phi);
	if(this->cor_name != "") tree->SetBranchAddress(this->cor_name, &cor);
	if(this->unc_name != "") tree->SetBranchAddress(this->unc_name, &unc);

	if(this->pt_vector_name != "") tree->SetBranchAddress(this->pt_vector_name, &pt_v);
	if(this->rap_vector_name != "") tree->SetBranchAddress(this->rap_vector_name, &rap_v);
	if(this->eta_vector_name != "") tree->SetBranchAddress(this->eta_vector_name, &eta_v);
	if(this->phi_vector_name != "") tree->SetBranchAddress(this->phi_vector_name, &phi_v);
	if(this->cor_vector_name != "") tree->SetBranchAddress(this->cor_vector_name, &cor_v);
	if(this->unc_vector_name != "") tree->SetBranchAddress(this->unc_vector_name, &unc_v);

	tree->GetEntry(0);
	cout << "Run: " << iRun << " pt:" << pt_v << "\n";
	Int_t nEvent = iEvent;

	Event *event = new Event();

	if(pt_v != 0){
		for(int i = 0 ; i < nentries ; i++){
			tree->GetEntry(i);
			event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
			event->AddJets(*pt_v, *eta_v, *phi_v, *rap_v, *cor_v, *unc_v);
			measurement->ReadEvent(event);
			event->Clear();
		}
	}else{
		event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
		for(int i = 0 ; i < nentries ; i++){
			tree->GetEntry(i);
				//cout << iRun << " " << iEvent << " " << nPV << " " << CNTR << " " << FWD2 << " " << FWD3 
				//<< " " << pt << " " << eta << " " << rap << " " << phi << "\n";
			if(iEvent == nEvent){				//in Event
				event->AddJet(pt, eta, phi, rap, cor, -1.);
			}else{						//out Event
				//i = i-1;
				nEvent = iEvent;
				measurement->ReadEvent(event);
				event->Clear();
				event->Init(iRun, iEvent, nPV, CNTR, FWD3, -1, 1.);
	   		}
		}
	}
};

void Sample::Set13TeVNamesCFF(){
	this->tree_name		= 	"JetTree/data";
        this->run_num_name	=	"event_run";
        this->lumi_num_name	=	"event_lumi";
	this->event_num_name	=	"event_event";
	this->nPV_name		=	"event_nPV";
	this->CNTR_trg_name	=	"trgHLT_DiPFJet15_NoCaloMatched_v2";
	this->CNTR_trg_ps_name	= 	"trgHLTPS_HLT_DiPFJet15_NoCaloMatched_v2";
	this->FWD2_trg_name	=	"trgHLT_DiPFJet15_FBEta2_NoCaloMatched_v2";
	this->FWD2_trg_ps_name	= 	"trgHLTPS_HLT_DiPFJet15_FBEta2_NoCaloMatched_v2";
        this->pt_vector_name	=	"slimmedJetsPt10_pt";
	this->rap_vector_name	=	"slimmedJetsPt10_rap";
	this->eta_vector_name	=	"slimmedJetsPt10_eta";
	this->phi_vector_name	=	"slimmedJetsPt10_phi";
        this->cor_vector_name	=	"slimmedJetsPt10_cor";
	this->unc_vector_name	=	"slimmedJetsPt10_unc";
};

void Sample::Set13TeVNames(){
	this->tree_name = 	"JetCollection/jet_tree";
        this->run_num_name =	"iRun";
	this->event_num_name =	"iEvt";
	this->nPV_name = 	"nPV";
        this->pt_name = 	"pt";
	this->rap_name = 	"rap";
	this->eta_name = 	"eta";
	this->phi_name = 	"phi";
        this->CNTR_trg_name = 	"CNTR";
	this->FWD2_trg_name = 	"FWD2";
	this->FWD3_trg_name = 	"FWD3";
        this->cor_name = 	"cor";
};

void Sample::Set7TeVNames(){
	this->tree_name = 	"tr";
        this->run_num_name =	"irun";
	this->event_num_name =	"ievt";
	this->nPV_name = 	"nPV";
        this->pt_name = 	"pt";
	this->rap_name = 	"rap";
	this->eta_name = 	"eta";
	this->phi_name = 	"phi";
	this->unc_name = 	"uncert";
};
