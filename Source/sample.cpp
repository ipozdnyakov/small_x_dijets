#include<fstream>
#include<iostream>
#include"finder.h"
#include"sample.h"

using namespace std;

extern bool print_this_event;

Sample::Sample(TString str){
	this->name = str;
};

bool Sample::CheckEvent(Event *event){

if(print_this_event) cout << " check for sample " << this->name << ": \n";

if(event->nPV != 1) return false;

	if (name == "central_trg"){
		if((event->CNTR == 1)&&(CheckDiJet15(event))){
			this->weight = event->CNTR_ps;
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "forward2_trg"){
		if((event->FWD2 == 1)&&(CheckDiJet15fwdEta(event, 2.))){
			this->weight = event->FWD2_ps;
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "forward3_trg"){
		if((event->FWD3 == 1)&&(CheckDiJet15fwdEta(event, 3.))){
			this->weight = event->FWD3_ps;
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased"){
		if(event->MB == 1){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased_central"){
		if((event->MB == 1)&&(CheckDiJet15(event))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased_forward2"){
		if((event->MB == 1)&&(CheckDiJet15fwdEta(event, 2.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased_forward3"){
		if((event->MB == 1)&&(CheckDiJet15fwdEta(event, 3.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else{
		cout << "Sample Error: Conditions for sample " << this->name << " not found\n";
		return false;
	}

/*
        Sample *low_pthat               = new Sample("low_pthat");
        Sample *high_pthat              = new Sample("high_pthat");
        Sample *central                 = new Sample("central");
        Sample *central_no_fwd          = new Sample("central_no_fwd");
        Sample *forward                 = new Sample("forward");
        Sample *merged                  = new Sample("merged");
*/

};

bool Sample::CheckDiJet15(Event *event){

//	int i_lead = event->GetNthPtIndex(1);
//	int i_sublead = event->GetNthPtIndex(2);

	int i_lead = find_Nth_value_index(event->pt, 1);
	int i_sublead = find_Nth_value_index(event->pt, 2);

	if(i_sublead > -1){

		if(print_this_event) cout << " leading jet " << i_lead << ": pt=" << event->pt[i_lead] << "\n";
		if(print_this_event) cout << " sublead jet " << i_sublead << ": pt=" << event->pt[i_sublead] << "\n";

		if((event->pt[i_sublead] > 15.)&&(event->pt[i_lead] > 15.)){
			return true;
		}else{
			return false;
		}

	}else{
		return false;
	}
};

bool Sample::CheckDiJet15fwdEta(Event *event, double Eta){

//	int i_lead = event->GetNthPtIndex(1);
//	int i_sublead = event->GetNthPtIndex(2);
	int i_lead = find_Nth_value_index(event->pt, 1);
	int i_sublead = find_Nth_value_index(event->pt, 2);

	if(i_sublead > -1){

		if(print_this_event) cout << " leading jet " << i_lead << ": pt=" << event->pt[i_lead] << " eta=" << event->eta[i_lead] << "\n";
		if(print_this_event) cout << " sublead jet " << i_sublead << ": pt=" << event->pt[i_sublead] << " eta=" << event->eta[i_sublead] << "\n";

		if(	  (event->pt[i_sublead] > 15.)
			&&(event->pt[i_lead] > 15.)
			&&(fabs(event->eta[i_sublead]) > 2.)
			&&(fabs(event->eta[i_lead]) > 2.)
			&&(((event->eta[i_lead])*(event->eta[i_sublead])) < 0.)
		){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
};
