#include<fstream>
#include<iostream>
#include<TTree.h>
#include<TFile.h>
#include"sample.h"
#include"object.h"
#include"measurement.h"
#include"event.h"

#define pi 3.1415926
using namespace std;

template void Sample::ReadSample<Measurement>(Measurement *);
template void Sample::ReadSample<Decorrelations>(Decorrelations *);
template <class M> void Sample::ReadSample(M *measurement){

        string file_name;
        ifstream data_files("./listing/" + this->name);
	cout << "\t-reading data files from set " << this->name << ":\n";
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, measurement);
        }
	cout << "\n";

};

template void Sample::ReadFile<Measurement>(string , Measurement *);
template void Sample::ReadFile<Decorrelations>(string , Decorrelations *);
template <class M> void Sample::ReadFile(string name, M *measurement){

	TString file_name = name;
	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get("JetCollection/jet_tree");
	Int_t nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\t";

        Int_t iEvent = 0, iRun = 0, nPV = 0;
	Int_t CNTR = -1, FWD2 = -1, FWD3 = -1;
        Double_t pt = 0, phi = 0, eta = 0, rap = 0, cor = 0, unc = 0;

	tree->SetBranchAddress("iEvt",&iEvent);
	tree->SetBranchAddress("iRun",&iRun);
	tree->SetBranchAddress("nPV",&nPV);
	tree->SetBranchAddress("CNTR",&CNTR);
	tree->SetBranchAddress("FWD2",&FWD2);
	tree->SetBranchAddress("FWD3",&FWD3);
	tree->SetBranchAddress("pt",&pt);
	tree->SetBranchAddress("phi",&phi);
	tree->SetBranchAddress("eta",&eta);
	tree->SetBranchAddress("rap",&rap);
	tree->SetBranchAddress("cor",&cor);
	tree->SetBranchAddress("unc",&unc);

	tree->GetEntry(0);
	cout << "Run: " << iRun << "\r";
	Int_t nEvent = iEvent;

	Event *event = new Event(iRun, iEvent,nPV,CNTR,FWD2,1.);

	for(int i = 0 ; i < nentries ; i++){
		tree->GetEntry(i);
		if(iEvent == nEvent){				//in Event
			event->AddJet(pt,eta,phi,rap,cor);
		}else{						//out Event
			nEvent = iEvent;
			measurement->ReadEvent(event);
			delete event;
			event = new Event(iRun,iEvent,nPV,CNTR,FWD2,1.);
   		}
	}

};
