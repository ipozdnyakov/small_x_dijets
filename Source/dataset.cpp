#include<fstream>
#include<iostream>
#include"dataset.h"

using namespace std;


Dataset::Dataset(string str){

	name = str;

//NEW BRANCHES SHOULD BE ALSO ADDED IN class Measurement::ReadFile()

	if ((name == "13TeV_data_2016H_FSQ_Jets")||(name == "13TeV_data_2016H_Min_Bias")){
	        this->tree_name         =	"JetTree/data";
        	this->run_num_name	=	"event_run";
	        this->lumi_num_name     =	"event_lumi";
        	this->event_num_name    =	"event_event";
	        this->nPV_name          =	"event_nPV";
        	this->CNTR_trg_name     =	"trgHLT_DiPFJet15_NoCaloMatched_v5";
	        this->CNTR_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet15_NoCaloMatched_v5";
        	//this->CNTR_trg_name     =	"trgHLT_DiPFJet25_NoCaloMatched_v5";
	        //this->CNTR_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet25_NoCaloMatched_v5";
        	this->FWD3_trg_name     =	"trgHLT_DiPFJet15_FBEta3_NoCaloMatched_v6";
	        this->FWD3_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet15_FBEta3_NoCaloMatched_v6";
        	//this->FWD3_trg_name     =	"trgHLT_DiPFJet25_FBEta3_NoCaloMatched_v6";
	        //this->FWD3_trg_ps_name  =	"trgHLTPS_HLT_DiPFJet25_FBEta3_NoCaloMatched_v6";
        	this->pt_vector_name    =	"slimmedJetsPt10_pt";
	        this->rap_vector_name   =	"slimmedJetsPt10_rap";
        	this->eta_vector_name   =	"slimmedJetsPt10_eta";
	        this->phi_vector_name   =	"slimmedJetsPt10_phi";
        	this->cor_vector_name   =	"slimmedJetsPt10_cor";
	        this->unc_vector_name   =	"slimmedJetsPt10_unc";
		if ((name == "13TeV_data_2016H_Min_Bias")){
			this->min_bias_info = true;
		}
	}else if ((name == "13TeV_data_2015C_FSQJets3")||(name == "13TeV_data_2015C_Min_Bias")||(name == "13TeV_data_2015C_ZeroBias")){
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
		if ((name == "13TeV_data_2015C_Min_Bias")||(name == "13TeV_data_2015C_ZeroBias")){
			this->min_bias_info = true;
		}
	}else if ((name == "13TeV_mc_herwig_MinBias")||(name == "13TeV_mc_herwig_pt10to35")||(name == "13TeV_mc_herwig_pt35toInf")
	||(name == "13TeV_mc_herwig_pt10to35_FB")||(name == "13TeV_mc_herwig_pt35toInf_FB")){
	        this->tree_name         =	"JetTree/data";
        	this->run_num_name	=	"event_run";
	        this->lumi_num_name     =	"event_lumi";
        	this->event_num_name    =	"event_event";
	        this->nPV_name          =	"event_nPV";
        	this->pt_vector_name    =	"slimmedJetsPt10_pt";
	        this->rap_vector_name   =	"slimmedJetsPt10_rap";
        	this->eta_vector_name   =	"slimmedJetsPt10_eta";
	        this->phi_vector_name   =	"slimmedJetsPt10_phi";
        	this->cor_vector_name   =	"slimmedJetsPt10_cor";
	        this->unc_vector_name   =	"slimmedJetsPt10_unc";
        	this->gen_pt_vector_name    =	"slimmedJetsPt10_gen_pt";
	        this->gen_rap_vector_name   =	"slimmedJetsPt10_gen_rap";
        	this->gen_eta_vector_name   =	"slimmedJetsPt10_gen_eta";
	        this->gen_phi_vector_name   =	"slimmedJetsPt10_gen_phi";

		this->mc_info = 1;

		if ((name == "13TeV_mc_herwig_MinBias")||(name == "13TeV_mc_pythia_MinBias")){
			this->min_bias_info = true;
		}

		if ((name == "13TeV_mc_herwig_pt10to35")||(name == "13TeV_mc_pythia_pt10to35")
		||(name == "13TeV_mc_herwig_pt35toInf")||(name == "13TeV_mc_pythia_pt35toInf")){
			this->mc_cntr_info = true;
		}

		if ((name == "13TeV_mc_herwig_pt10to35_FB")||(name == "13TeV_mc_pythia_pt10to35_FB")
		||(name == "13TeV_mc_herwig_pt35toInf_FB")||(name == "13TeV_mc_pythia_pt35toInf_FB")){
			this->mc_fb_info = true;
		}

		if ((name == "13TeV_mc_herwig_pt10to35")||(name == "13TeV_mc_pythia_pt10to35")
		||(name == "13TeV_mc_herwig_pt10to35_FB")||(name == "13TeV_mc_pythia_pt10to35_FB")){
			this->mc_low_pthat_info = true;
		}

		if ((name == "13TeV_mc_herwig_pt35toInf")||(name == "13TeV_mc_pythia_pt35toInf")
		||(name == "13TeV_mc_herwig_pt35toInf_FB")||(name == "13TeV_mc_pythia_pt35toInf_FB")){
			this->mc_high_pthat_info = true;
		}

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
		cout << "Name set for dataset " << name << " not found\n";
	}

};
