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

	if(this->name == "FSQJets_2015_2016") this->Set13TeVNames();
	if(this->name == "datasets/FSQJets3_2015C_VdMaugust") this->Set13TeVNames();
	if(this->name == "datasets/7TeV_JetMETTau_Centr") this->Set7TeVNames(); 

        ifstream data_files("./listing/" + this->name);
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

        Int_t iEvent = 0, iRun = 0, nPV = 0;
	Int_t CNTR = 1, FWD2 = -1, FWD3 = -1;
        double pt = 0., phi = 0., eta = 0., rap = 0., cor = 0., unc = 0.;

	if(this->run_num_name != "") tree->SetBranchAddress(this->run_num_name, &iRun);
	if(this->event_num_name != "") tree->SetBranchAddress(this->event_num_name, &iEvent);
	if(this->nPV_name != "") tree->SetBranchAddress(this->nPV_name, &nPV);
	if(this->pt_name != "") tree->SetBranchAddress(this->pt_name, &pt);
	if(this->rap_name != "") tree->SetBranchAddress(this->rap_name, &rap);
	if(this->eta_name != "") tree->SetBranchAddress(this->eta_name, &eta);
	if(this->phi_name != "") tree->SetBranchAddress(this->phi_name, &phi);

	if(this->CNTR_trg_name != "") tree->SetBranchAddress(this->CNTR_trg_name, &CNTR);
	if(this->FWD2_trg_name != "") tree->SetBranchAddress(this->FWD2_trg_name, &FWD2);
	if(this->FWD3_trg_name != "") tree->SetBranchAddress(this->FWD3_trg_name, &FWD3);
	if(this->cor_name != "") tree->SetBranchAddress(this->cor_name, &cor);
	if(this->unc_name != "") tree->SetBranchAddress(this->unc_name, &unc);

	tree->GetEntry(0);
	cout << "Run: " << iRun << "\r";
	Int_t nEvent = iEvent;

	//Event *event = new Event(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
	Event *event = new Event();
	event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);

	for(int i = 0 ; i < nentries ; i++){
		tree->GetEntry(i);
		//cout << iRun << " " << iEvent << " " << nPV << " " << CNTR << " " << FWD2 << " " << FWD3 << " " << pt << " " << eta << " " << rap << " " << phi << "\n";
		if(iEvent == nEvent){				//in Event
			event->AddJet(pt, eta, phi, rap, cor);
		}else{						//out Event
			i = i-1;
			nEvent = iEvent;
			measurement->ReadEvent(event);
			//event->Print();
			event->Clear();
			//delete event;
			//event = new Event(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
			event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
   		}
	}
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
	this->unc_name = 	"unc";
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
        this->CNTR_trg_name = 	"";
	this->FWD2_trg_name = 	"";
	this->FWD3_trg_name = 	"";
        this->cor_name = 	"";
	this->unc_name = 	"uncert";
};
