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
        Double_t pt = 0, phi = 0, eta = 0, rap = 0, cor = 0, unc = 0;
        Int_t iEvent, iRun, nPV;
	Int_t CNTR = -1, FWD2 = -1, FWD3 = -1;

	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get("JetCollection/jet_tree");
	nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\r";

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
	nEvent = iEvent;

	Event *event = new Event(iEvent,nPV,CNTR,FWD2,1.);

	for(int i = 0 ; i < nentries ; i++){
		tree->GetEntry(i);
		if(iEvent == nEvent){				//in Event
			event->AddJet(pt,eta,phi,rap);
		}else{						//out Event
			nEvent = iEvent;
			observable->ReadEvent(event);
			delete event;
			event = new Event(iEvent,nPV,CNTR,FWD2,1.);
   		}
	}

};
