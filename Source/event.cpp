#include<vector>
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include"event.h"

using namespace std;

JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("./jec_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("./jec_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

void Event::Print(){

	cout << "===========================================================";
	cout << "Event " << this->number;
	cout << "\nrun " << this->run;
	cout << "; nPV " << this->nPV;
	cout << "; CNTR " << this->CNTR;
	cout << "; FWD " << this->FWD;
	cout << "; MB " << this->MB;
	cout << "; weight " << this->weight;

	cout << "\nPrint event:\n pt: ";
	for(int i = 0; i < this->pt.size(); i++){
		cout << this->pt[i] << "\t";
	}
	cout << "\n eta: ";
	for(int i = 0; i < this->eta.size(); i++){
		cout << this->eta[i] << "\t";
	}
	cout << "\n rap: ";
	for(int i = 0; i < this->rap.size(); i++){
		cout << this->rap[i] << "\t";
	}
	cout << "\n phi: ";
	for(int i = 0; i < this->phi.size(); i++){
		cout << this->phi[i] << "\t";
	}
	cout << "\n";
};

void Event::Init(int r, int n, int npv, int cntr, int fwd, int mb, double w){ 
	this->run = r;
	this-> number = n;
	this->nPV = npv;
	this->CNTR = cntr;
	this->FWD = fwd;
	this->MB = mb;
	this->weight = w;
};

void Event::Clear(){
	this->pt.clear();
	this->pt_unc.clear();
	this->pt_cor.clear();
	this->eta.clear();
	this->phi.clear();
	this->rap.clear();
};

void Event::AddJet( 
		double jet_pt,
		double jet_eta,
		double jet_phi,
		double jet_rap,
		double jet_pt_cor
        ){
	
		double jet_pt_unc = 0.;

		if(this->run > 273000){
	        	jecUnc2016->setJetEta(jet_eta);
        		jecUnc2016->setJetPt(jet_pt);
        		jet_pt_unc = jecUnc2016->getUncertainty(true);
		}else{
	        	jecUnc2015->setJetEta(jet_eta);
        		jecUnc2015->setJetPt(jet_pt);
        		jet_pt_unc = jecUnc2015->getUncertainty(true);
		}

                this->pt.push_back(jet_pt);
                this->pt_cor.push_back(jet_pt_cor);
                this->pt_unc.push_back(jet_pt_unc);
                this->eta.push_back(jet_eta);
                this->phi.push_back(jet_phi);
                this->rap.push_back(jet_rap);

};
