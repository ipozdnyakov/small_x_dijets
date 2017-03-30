#include<vector>
#include<iomanip>
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include"event.h"

using namespace std;

JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("./Docs/jec_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("./Docs/jec_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

string Event::RunPileUp(){
	return "H";
};

void Event::JecUp(){
	if(this->jec_cond != "centr"){cout << "Event error: try to JecUp then jec_cond = " << this->jec_cond;
	}else{
		for(int i = 0; i < this->pt.size(); i++){
			this->pt[i] = (1.+this->pt_unc[i])*this->pt[i];
		}
		this->jec_cond = "up";
	}
};

void Event::JecDown(){
	if(this->jec_cond != "centr"){cout << "Event error: try to JecDown then jec_cond = " << this->jec_cond;
	}else{
		for(int i = 0; i < this->pt.size(); i++){
			this->pt[i] = (1.-this->pt_unc[i])*this->pt[i];
		}
		this->jec_cond = "down";
	}
};

void Event::JecCentr(){
	if(this->jec_cond == "centr"){cout << "Event error: try to JecCentr then already jec_cond = " << this->jec_cond;
	}else{
		for(int i = 0; i < this->pt.size(); i++){
			if(this->jec_cond == "up") this->pt[i] = this->pt[i]/(1.+this->pt_unc[i]);
			if(this->jec_cond == "down") this->pt[i] = this->pt[i]/(1.-this->pt_unc[i]);
		}
		this->jec_cond = "centr";
	}
};

void Event::Print(){

	cout << "===========================================================";
	cout << "\nEvent " << this->number;
	cout << "; run " << this->run;
	cout << "; nPV " << this->nPV;
	cout << "; CNTR " << this->CNTR;
	cout << "; FWD2 " << this->FWD2;
	cout << "; FWD3 " << this->FWD3;
	cout << "; MB " << this->MB;
	cout << "; weight " << this->weight;
	cout << "; CNTR_ps " << this->CNTR_ps;
	cout << "; FWD2_ps " << this->FWD2_ps;
	cout << "; FWD3_ps " << this->FWD3_ps;
	cout << "; MB_ps " << this->MB_ps;

	cout << "\nPrint event:\n pt:  ";
	for(int i = 0; i < this->pt.size(); i++){
		cout << setw(10) << this->pt[i] << " ";
	}
	cout << "\n eta: ";
	for(int i = 0; i < this->eta.size(); i++){
		cout << setw(10) << this->eta[i] << " ";
	}
	cout << "\n rap: ";
	for(int i = 0; i < this->rap.size(); i++){
		cout << setw(10) <<  this->rap[i] << " ";
	}
	cout << "\n phi: ";
	for(int i = 0; i < this->phi.size(); i++){
		cout << setw(10) << this->phi[i] << " ";
	}
	cout << "\n";
};

void Event::Init(int r, int n, int npv, int cntr, int fwd2, int fwd3, int mb, double w, int cntr_ps, int fwd2_ps, int fwd3_ps, int mb_ps){ 
	this->run = r;
	this->number = n;
	this->nPV = npv;
	this->CNTR = cntr;
	this->FWD2 = fwd2;
	this->FWD3 = fwd3;
	this->MB = mb;
	this->weight = w;
	this->CNTR_ps = cntr_ps;
	this->FWD2_ps = fwd2_ps;
	this->FWD3_ps = fwd3_ps;
	this->MB_ps = mb_ps;
};

void Event::Clear(){
	this->pt.clear();
	this->pt_unc.clear();
	this->pt_cor.clear();
	this->eta.clear();
	this->phi.clear();
	this->rap.clear();

	this->gen_pt.clear();
	this->gen_eta.clear();
	this->gen_phi.clear();
	this->gen_rap.clear();
};

void Event::AddJet(
		double jet_pt,
		double jet_eta,
		double jet_phi,
		double jet_rap,
		double jet_pt_cor,		
		double jet_pt_unc
        ){
	
	if(jet_pt_unc == -1.){
		if(this->run > 273000){
	        	jecUnc2016->setJetEta(jet_eta);
        		jecUnc2016->setJetPt(jet_pt);
        		jet_pt_unc = jecUnc2016->getUncertainty(true);
		}else{
	        	jecUnc2015->setJetEta(jet_eta);
        		jecUnc2015->setJetPt(jet_pt);
        		jet_pt_unc = jecUnc2015->getUncertainty(true);
		}
	}

        	this->pt.push_back(jet_pt);
                this->pt_cor.push_back(jet_pt_cor);
                this->pt_unc.push_back(jet_pt_unc);
	        this->eta.push_back(jet_eta);
        	this->phi.push_back(jet_phi);
	        this->rap.push_back(jet_rap);

};

void Event::AddJets(
		vector<float> jet_pt,
		vector<float> jet_eta,
		vector<float> jet_phi,
		vector<float> jet_rap,
		vector<float> jet_pt_cor,		
		vector<float> jet_pt_unc
        ){
        	this->pt = vector<double>(jet_pt.begin(), jet_pt.end());
        	this->pt_cor = vector<double>(jet_pt_cor.begin(), jet_pt_cor.end());
        	this->pt_unc = vector<double>(jet_pt_unc.begin(), jet_pt_unc.end());
        	this->eta = vector<double>(jet_eta.begin(), jet_eta.end());
        	this->phi = vector<double>(jet_phi.begin(), jet_phi.end());
        	this->rap = vector<double>(jet_rap.begin(), jet_rap.end());
};

void Event::AddGenJets(
		vector<float> gen_jet_pt,
		vector<float> gen_jet_eta,
		vector<float> gen_jet_phi,
		vector<float> gen_jet_rap
        ){
        	this->gen_pt = vector<double>(gen_jet_pt.begin(), gen_jet_pt.end());
        	this->gen_eta = vector<double>(gen_jet_eta.begin(), gen_jet_eta.end());
        	this->gen_phi = vector<double>(gen_jet_phi.begin(), gen_jet_phi.end());
        	this->gen_rap = vector<double>(gen_jet_rap.begin(), gen_jet_rap.end());

		this->gen_level = true;
};

