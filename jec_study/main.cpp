#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <vector>

#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

#include "reader.h"
#include "observables.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#define pi 3.1415926
using namespace std;

int main(int argc, char** argv) {
    char str[256];

    TString dir_name="jec_study";
    TString dir  = "/afs/cern.ch/work/i/ivanp/2015_Decorrelator/CMSSW_7_4_15/src/";
    TString list_name = "FSQJets_2015_2016";
    TString list = dir + "listing/" + list_name;
	dir = dir + dir_name + "/";
    Double_t pt_min_1 = 35.; //pt_min_1 >= pt_min_2
    Double_t pt_min_2 = 35.;
    Double_t pt_veto  = 35.;
    Double_t FWD_weight = 0.5;
    TString Pt_min = "_pt";
				Pt_min += pt_min_1;
				Pt_min += "_";
				Pt_min += pt_min_2;
    TString Pt_veto = "_veto";
				Pt_veto += pt_veto;
    TString specification = "_FSQJets_2015_2016_data_13TeV_LowPU_MN_CNTR_dy0_9.4" + Pt_min;//+Pt_veto;

    FILE *file;
    TString name;
    TString pict;
//------------------------------------OBSERVABLES---------------------------------------
    Observables *MN_jets = new Observables(dir_name, specification);

//------------------------------------JEC UNC-------------------------------------------
    JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("../JEC_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
    JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("../JEC_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

//------------------------------------PROCESSING----------------------------------------
    int j = 0;
    int i_file = 0;

    file = fopen(list,"r");

    while(!feof(file)){
        fgets(str, 256, file);
        if(feof(file)) break;
        while(((int)str[j]) != 10){name += str[j]; j++;}
        j = 0;
    	if(i_file % 10 == 0){cout << name << "\n"; i_file = 0;}
	treereader(name, MN_jets, pt_min_1, pt_min_2, FWD_weight, pt_veto, jecUnc2016);
	name = "";
	i_file++;
    };

    cout << "Events: cntr - " << MN_jets->n_event_cntr << " fwd - " << MN_jets->n_event_fwd << "\n";

//------------------------------------POST PROCESSING-----------------------------------
    MN_jets->CalculateErrors();
    MN_jets->WriteToFile(dir + "/results" + specification + ".root");

    return (EXIT_SUCCESS);
}
