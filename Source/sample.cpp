#include<fstream>
#include<iostream>
#include"sample.h"

using namespace std;


Sample::Sample(string str){

	name = str;

//NEW BRAMCHES SHOULD BE ALSO ADDED IN class Measurement::ReadFile()

	if (name == "13TeV_data_2015C_FSQJets3"){
	        this->tree_name         =	"JetTree/data";
        	this->run_num_name	=	"event_run";
	        this->lumi_num_name     =	"event_lumi";
        	this->event_num_name    =	"event_event";
	        this->nPV_name          =	"event_nPV";
        	this->CNTR_trg_name     =	"trgHLT_DiPFJet15_NoCaloMatched_v2";
	        this->CNTR_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet15_NoCaloMatched_v2";
        	this->FWD2_trg_name     =	"trgHLT_DiPFJet15_FBEta2_NoCaloMatched_v2";
	        this->FWD2_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet15_FBEta2_NoCaloMatched_v2";
        	this->pt_vector_name    =	"slimmedJetsPt10_pt";
	        this->rap_vector_name   =	"slimmedJetsPt10_rap";
        	this->eta_vector_name   =	"slimmedJetsPt10_eta";
	        this->phi_vector_name   =	"slimmedJetsPt10_phi";
        	this->cor_vector_name   =	"slimmedJetsPt10_cor";
	        this->unc_vector_name   =	"slimmedJetsPt10_unc";		
	}else if (name == "FSQJets_2015_2016"){
        	this->tree_name 	=	"JetCollection/jet_tree";
	        this->run_num_name 	=	"iRun";
        	this->event_num_name 	=	"iEvt";
	        this->nPV_name 		=       "nPV";
        	this->pt_name 		=       "pt";
	        this->rap_name 		=       "rap";
        	this->eta_name 		=       "eta";
	        this->phi_name 		=       "phi";
        	this->CNTR_trg_name 	=	"CNTR";
	        this->FWD2_trg_name 	=	"FWD2";
        	this->FWD3_trg_name 	=	"FWD3";
	        this->cor_name 		=        "cor";
	}else if (name == "7TeV_JetMETTau_Centr"){
	        this->tree_name 	=	"tr";
        	this->run_num_name 	= 	"irun";
	        this->event_num_name 	= 	"ievt";
        	this->nPV_name 		=       "nPV";
	        this->pt_name 		=       "pt";
        	this->rap_name 		=       "rap";
	        this->eta_name 		=       "eta";
        	this->phi_name 		=       "phi";
	        this->unc_name 		=       "uncert";
	}else{
		cout << "Name set for sample " << name << " not found\n";
	}

};
