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
		if((event->CNTR == 1)&&(CheckDiJetPt(event, 15.))){
			this->weight = event->CNTR_ps;
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "forward2_trg"){
		if((event->FWD2 == 1)&&(CheckDiJetPtEta(event, 15., 2.))){
			this->weight = event->FWD2_ps;
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "forward3_trg"){
		if((event->FWD3 == 1)&&(CheckDiJetPtEta(event, 15., 3.))){
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
		if((event->MB == 1)&&(CheckDiJetPt(event, 15.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased_forward2"){
		if((event->MB == 1)&&(CheckDiJetPtEta(event, 15., 2.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "unbiased_forward3"){
		if((event->MB == 1)&&(CheckDiJetPtEta(event, 15., 3.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "central_pt35"){
		if((event->CNTR == 1)&&(CheckDiJetPt(event, 35.))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "forward_pt35_eta2.1"){
		if(((event->FWD2 == 1)||(event->FWD3 == 1))&&(CheckDiJetPtEta(event, 35., 2.1))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "central_no_fwd_pt35_eta2.1"){
		if((event->CNTR == 1)&&(CheckDiJetPt(event, 35.))&&(!CheckDiJetPtEta(event, 35., 2.1))){
			if(print_this_event) cout << " true\n";
			return true;
		}else{
			if(print_this_event) cout << " false\n";
			return false;
		}
	}else if (name == "merged_pt35_eta2.1"){
		if((event->CNTR == 1)&&(CheckDiJetPt(event, 35.))&&(!CheckDiJetPtEta(event, 35., 2.1))){
			if(print_this_event) cout << " true\n";
			this->weight = 1.;
			return true;
		}else if(((event->FWD2 == 1)||(event->FWD3 == 1))&&(CheckDiJetPtEta(event, 35., 2.1))){
			if(print_this_event) cout << " true\n";
			this->weight = 0.3;
			// 0.29 - pt=35 eta=2.1
			// 0.30 - pt=35 eta=3.1
			// 0.31 - pt=20 eta=3.1
			// 0.50 - pt=70 eta=3.1
			// the same weights for MN and INCL
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
*/

};

bool Sample::CheckDiJetPt(Event *event, double Pt){

	int i_lead = find_Nth_value_index(event->pt, 1);
	int i_sublead = find_Nth_value_index(event->pt, 2);

	if(i_sublead > -1){

		if(print_this_event) cout << " leading jet " << i_lead << ": pt=" << event->pt[i_lead] << "\n";
		if(print_this_event) cout << " sublead jet " << i_sublead << ": pt=" << event->pt[i_sublead] << "\n";

		if((event->pt[i_sublead] > Pt)&&(event->pt[i_lead] > Pt)){
			return true;
		}else{
			return false;
		}

	}else{
		return false;
	}
};

bool Sample::CheckDiJetPtEta(Event *event, double Pt, double Eta){

	int i_lead = find_Nth_value_index(event->pt, 1);
	int i_sublead = find_Nth_value_index(event->pt, 2);

	double eta_over_pt_max = -10., eta_over_pt_min = 10.;

	if(i_sublead > -1){

		if(print_this_event) cout << " leading jet " << i_lead << ": pt=" << event->pt[i_lead] << " eta=" << event->eta[i_lead] << "\n";
		if(print_this_event) cout << " sublead jet " << i_sublead << ": pt=" << event->pt[i_sublead] << " eta=" << event->eta[i_sublead] << "\n";

		if(	  (event->pt[i_lead] > Pt)
			&&(event->pt[i_sublead] > Pt)
		){
			for(int i = 0; i < event->pt.size(); i++){
				if(event->pt[i] > Pt){
					if(event->eta[i] > eta_over_pt_max) eta_over_pt_max = event->eta[i];
					if(event->eta[i] < eta_over_pt_min) eta_over_pt_min = event->eta[i];
				}
			}

			if(	//(eta_over_pt_max > Eta)
				//&&(eta_over_pt_min < -Eta)
				//&&
				(fabs(event->eta[i_lead]) > Eta)
                        	&&(fabs(event->eta[i_sublead]) > Eta)
				&&(event->eta[i_lead]*event->eta[i_sublead] < 0.)
			){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else{
		return false;
	}
};
