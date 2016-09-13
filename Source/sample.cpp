#include<TTree.h>
#include<TFile.h>
#include<fstream>
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include"observable.h"
#include"event.h"
#include"sample.h"

#define pi 3.1415926
using namespace std;

template void Sample::ReadSample<Observable>(Observable *);
template void Sample::ReadSample<MN>(MN *);
template <class Obs> void Sample::ReadSample(Obs *observable){

        ifstream data_files("./listing/" + this->name);
	cout << "\t-reading data files from " << this->name << ":\n";

        string file_name;
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, observable);
        }
	cout << "\n";

};

template void Sample::ReadFile<Observable>(string , Observable *);
template void Sample::ReadFile<MN>(string , MN *);
template <class Obs> void Sample::ReadFile(string name, Obs *observable){

	TString file_name = name;
	Int_t nentries = 0, nEvent = 0;
        Double_t pt = 0, eta = 0, phi = 0, rap = 0, weight = 1.;
        Int_t iEvent, iRun, nPV;
	Int_t CNTR = -1, FWD = -1;

	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get("JetCollection/jet_tree");
	nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\r";

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
			observable->ReadEvent(event);
			delete event;
			event = new Event(iEvent,nPV,CNTR,FWD,weight);
   		}
	}

};
