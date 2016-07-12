#include <stdlib.h>
#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "reader.h"
#include "TLatex.h"
#include "TPaveText.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <TCanvas.h>
#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#define pi 3.1415926
using namespace std;

int main(int argc, char** argv) {
    char str[256];

    TString dir_name="DATA_13TeV";
    TString dir  = "/afs/cern.ch/work/i/ivanp/2015_Decorrelator/CMSSW_7_4_15/src/" + dir_name + "/";
    //TString list_name = "/MinBias_VdMscan_list";
    //TString list_name = "/FSQJets3_VdMscan_list";
    TString list_name = "/MinBias_LowPU_list";
    TString list = dir + "listing" + list_name;
    Double_t FWD_weight = 1.;
    TString specification = "_data_13TeV_EFFICIENCY";

    FILE *file;
    TString name, histname;
    Int_t i = 0;
    TString pict;

//------------------------------------BINING---------------------------------------
    double kfacbins[16]={0,0.5,1.0,1.5,2.0,2.5,3.0,
			 3.5,4.0,4.5,5.0,5.5,6.0,
			 7.0,8.0,9.4};

    double etabins[83]={-5.191,-4.889,-4.716,-4.538,-4.363,-4.191,
		-4.013,-3.839,-3.664,-3.489,-3.314,-3.139,-2.964,
		-2.853,-2.650,-2.500,-2.322,-2.172,-2.043,-1.930,
		-1.830,-1.740,-1.653,-1.566,-1.479,-1.392,-1.305,
		-1.218,-1.131,-1.044,-0.957,-0.870,-0.783,-0.696,
		-0.609,-0.522,-0.435,-0.348,-0.261,-0.174,-0.087,
		0,0.087,0.174,0.261,0.348,0.435,0.522,0.609,0.696,
		0.783,0.870,0.957,1.044,1.131,1.218,1.305,1.392,
		1.479,1.566,1.653,1.740,1.830,1.930,2.043,2.172,
		2.322,2.500,2.650,2.853,2.964,3.139,3.314,3.489,
		3.664,3.839,4.013,4.191,4.363,4.538,4.716,4.889,5.191};

    double ptbins[36]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,45,50,55,60,80,100,120,160,200,300};

    double dphi_bins[11]={0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.70, 0.8, 0.9, 1.};
    for(i = 0; i < 11; i++){
			dphi_bins[i] = dphi_bins[i]*pi;
    }

    int nk_bin = sizeof(kfacbins)/sizeof(kfacbins[0]);
    int neta_bin = sizeof(etabins)/sizeof(etabins[0]);
    int npt_bin = sizeof(ptbins)/sizeof(ptbins[0]);
    int ndphi_bin = sizeof(dphi_bins)/sizeof(dphi_bins[0]);
//------------------------------------HISTOS---------------------------------------
    TH1D *pt_cntr, *eta_cntr, *phi_cntr;
    TH1D *pt_cntr_mb, *eta_cntr_mb, *phi_cntr_mb;
    TH1D *pt_fwd, *eta_fwd, *phi_fwd;
    TH1D *pt_fwd_mb, *eta_fwd_mb, *phi_fwd_mb;

        histname = "pt_cntr";  histname += specification;
        pt_cntr = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_cntr->Sumw2();

        histname = "eta_cntr";  histname += specification;
        eta_cntr = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr->Sumw2();

        histname = "phi_cntr";  histname += specification;
        phi_cntr = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_cntr->Sumw2();

        histname = "pt_cntr_mb";  histname += specification;
        pt_cntr_mb = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_cntr_mb->Sumw2();

        histname = "eta_cntr_mb";  histname += specification;
        eta_cntr_mb = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_mb->Sumw2();

        histname = "phi_cntr_mb";  histname += specification;
        phi_cntr_mb = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_cntr_mb->Sumw2();

        histname = "pt_fwd";  histname += specification;
        pt_fwd = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_fwd->Sumw2();

        histname = "eta_fwd";  histname += specification;
        eta_fwd = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd->Sumw2();

        histname = "phi_fwd";  histname += specification;
        phi_fwd = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_fwd->Sumw2();

        histname = "pt_fwd_mb";  histname += specification;
        pt_fwd_mb = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_fwd_mb->Sumw2();

        histname = "eta_fwd_mb";  histname += specification;
        eta_fwd_mb = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_mb->Sumw2();

        histname = "phi_fwd_mb";  histname += specification;
        phi_fwd_mb = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_fwd_mb->Sumw2();


    TH2D *pt_cntr_2D, *pt_cntr_mb_2D;
    TH2D *pt_fwd_2D, *pt_fwd_mb_2D;
    TH2D *eta_cntr_2D, *eta_cntr_mb_2D;
    TH2D *eta_fwd_2D, *eta_fwd_mb_2D;
   
        histname = "pt_cntr_2D";  histname += specification;
        pt_cntr_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_cntr_2D->Sumw2();

        histname = "pt_fwd_2D";  histname += specification;
        pt_fwd_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_fwd_2D->Sumw2();

        histname = "pt_cntr_mb_2D";  histname += specification;
        pt_cntr_mb_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_cntr_mb_2D->Sumw2();

        histname = "pt_fwd_mb_2D";  histname += specification;
        pt_fwd_mb_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_fwd_mb_2D->Sumw2();

        histname = "eta_cntr_2D";  histname += specification;
        eta_cntr_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_cntr_2D->Sumw2();

        histname = "eta_fwd_2D";  histname += specification;
        eta_fwd_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_fwd_2D->Sumw2();

        histname = "eta_cntr_mb_2D";  histname += specification;
        eta_cntr_mb_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_cntr_mb_2D->Sumw2();

        histname = "eta_fwd_mb_2D";  histname += specification;
        eta_fwd_mb_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_fwd_mb_2D->Sumw2();

    TH1D *eta_cntr_1, *eta_cntr_2, *eta_cntr_3;
    TH1D *eta_cntr_mb_1, *eta_cntr_mb_2, *eta_cntr_mb_3;
    TH1D *eta_fwd_1, *eta_fwd_2, *eta_fwd_3;
    TH1D *eta_fwd_mb_1, *eta_fwd_mb_2, *eta_fwd_mb_3;

        histname = "eta_cntr_1";  histname += specification;
        eta_cntr_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_1->Sumw2();

        histname = "eta_cntr_2";  histname += specification;
        eta_cntr_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_2->Sumw2();

        histname = "eta_cntr_3";  histname += specification;
        eta_cntr_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_3->Sumw2();

        histname = "eta_cntr_mb_1";  histname += specification;
        eta_cntr_mb_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_mb_1->Sumw2();

        histname = "eta_cntr_mb_2";  histname += specification;
        eta_cntr_mb_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_mb_2->Sumw2();

        histname = "eta_cntr_mb_3";  histname += specification;
        eta_cntr_mb_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_mb_3->Sumw2();

        histname = "eta_fwd_1";  histname += specification;
        eta_fwd_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_1->Sumw2();

        histname = "eta_fwd_2";  histname += specification;
        eta_fwd_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_2->Sumw2();

        histname = "eta_fwd_3";  histname += specification;
        eta_fwd_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_3->Sumw2();

        histname = "eta_fwd_mb_1";  histname += specification;
        eta_fwd_mb_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_mb_1->Sumw2();

        histname = "eta_fwd_mb_2";  histname += specification;
        eta_fwd_mb_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_mb_2->Sumw2();

        histname = "eta_fwd_mb_3";  histname += specification;
        eta_fwd_mb_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_mb_3->Sumw2();

    TH1D *ps_fwd, *ps_cntr;

        histname = "ps_cntr";  histname += specification;
        ps_cntr = new TH1D(histname, dir_name, 10, 0.5, 10.5);
        ps_cntr->Sumw2();

        histname = "ps_fwd";  histname += specification;
        ps_fwd = new TH1D(histname, dir_name, 10, 0.5, 10.5);
        ps_fwd->Sumw2();


//------------------------------------PROCESSING---------------------------------------
int j = 0;
int i_file = 0;
Int_t n_event_cntr = 0;
Int_t n_event_fwd = 0;

    file = fopen(list,"r");

    while(!feof(file))
    {
         fgets(str, 256, file);
         if(feof(file)) break;
         while(((int)str[j]) != 10){name += str[j]; j++;}
         j = 0;
    		//if(i_file % 2 == 1){ i_file++; name = ""; continue;}
    		//if(i_file > 400){ i_file++; name = ""; continue;}		
    		if(i_file % 10 == 0){ cout << name << "\n";}
			treereader(&n_event_cntr, &n_event_fwd, name,
				 pt_cntr, eta_cntr, phi_cntr,
				 pt_cntr_mb, eta_cntr_mb, phi_cntr_mb,
				 pt_fwd, eta_fwd, phi_fwd,
				 pt_fwd_mb, eta_fwd_mb, phi_fwd_mb,

				 pt_cntr_2D, pt_cntr_mb_2D,
    				 pt_fwd_2D, pt_fwd_mb_2D,
    				 eta_cntr_2D, eta_cntr_mb_2D,
    				 eta_fwd_2D, eta_fwd_mb_2D,

         			 eta_cntr_1, eta_cntr_2, eta_cntr_3,
         			 eta_cntr_mb_1, eta_cntr_mb_2, eta_cntr_mb_3,
        			 eta_fwd_1, eta_fwd_2, eta_fwd_3,
	        		 eta_fwd_mb_1, eta_fwd_mb_2, eta_fwd_mb_3,

				 ps_cntr, ps_fwd,
				 FWD_weight);
			name = "";
			i_file++;
	  };
cout << "Files: " << i_file << " Events from MB: cntr - " << n_event_cntr << " fwd - " << n_event_fwd << "\n";

//------------------------------------PRINTING---------------------------------------
TH1D *pt_fwd_eff, *pt_cntr_eff;
TH1D *eta_fwd_eff, *eta_cntr_eff;
TH1D *phi_fwd_eff, *phi_cntr_eff;

        histname = "pt_cntr_eff";  histname += specification;
        pt_cntr_eff = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_cntr_eff->Divide(pt_cntr,pt_cntr_mb,1.,1.,"b");

        histname = "pt_fwd_eff";  histname += specification;
        pt_fwd_eff = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_fwd_eff->Divide(pt_fwd,pt_fwd_mb,1.,1.,"b");

        histname = "eta_cntr_eff";  histname += specification;
        eta_cntr_eff = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_eff->Divide(eta_cntr,eta_cntr_mb,1.,1.,"b");

        histname = "eta_fwd_eff";  histname += specification;
        eta_fwd_eff = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_eff->Divide(eta_fwd,eta_fwd_mb,1.,1.,"b");

        histname = "phi_cntr_eff";  histname += specification;
        phi_cntr_eff = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_cntr_eff->Divide(phi_cntr,phi_cntr_mb,1.,1.,"b");

        histname = "phi_fwd_eff";  histname += specification;
        phi_fwd_eff = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi_fwd_eff->Divide(phi_fwd,phi_fwd_mb,1.,1.,"b");

TH2D *pt_fwd_eff_2D, *pt_cntr_eff_2D;
TH2D *eta_fwd_eff_2D, *eta_cntr_eff_2D;

        histname = "pt_cntr_eff_2D";  histname += specification;
        pt_cntr_eff_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_cntr_eff_2D->Divide(pt_cntr_2D,pt_cntr_mb_2D,1.,1.,"b");

        histname = "pt_fwd_eff_2D";  histname += specification;
        pt_fwd_eff_2D = new TH2D(histname, dir_name, npt_bin - 1, ptbins, npt_bin - 1, ptbins);
        pt_fwd_eff_2D->Divide(pt_fwd_2D,pt_fwd_mb_2D,1.,1.,"b");

        histname = "eta_cntr_eff_2D";  histname += specification;
        eta_cntr_eff_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_cntr_eff_2D->Divide(eta_cntr_2D,eta_cntr_mb_2D,1.,1.,"b");

        histname = "eta_fwd_eff_2D";  histname += specification;
        eta_fwd_eff_2D = new TH2D(histname, dir_name, neta_bin - 1, etabins, neta_bin - 1, etabins);
        eta_fwd_eff_2D->Divide(eta_fwd_2D,eta_fwd_mb_2D,1.,1.,"b");

TH1D *eta_cntr_eff_1, *eta_cntr_eff_2, *eta_cntr_eff_3;
TH1D *eta_fwd_eff_1, *eta_fwd_eff_2, *eta_fwd_eff_3;

        histname = "eta_cntr_eff_1";  histname += specification;
        eta_cntr_eff_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_eff_1->Divide(eta_cntr_1,eta_cntr_mb_1,1.,1.,"b");

        histname = "eta_cntr_eff_2";  histname += specification;
        eta_cntr_eff_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_eff_2->Divide(eta_cntr_2,eta_cntr_mb_2,1.,1.,"b");

        histname = "eta_cntr_eff_3";  histname += specification;
        eta_cntr_eff_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr_eff_3->Divide(eta_cntr_3,eta_cntr_mb_3,1.,1.,"b");

        histname = "eta_fwd_eff_1";  histname += specification;
        eta_fwd_eff_1 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_eff_1->Divide(eta_fwd_1,eta_fwd_mb_1,1.,1.,"b");

        histname = "eta_fwd_eff_2";  histname += specification;
        eta_fwd_eff_2 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_eff_2->Divide(eta_fwd_2,eta_fwd_mb_2,1.,1.,"b");

        histname = "eta_fwd_eff_3";  histname += specification;
        eta_fwd_eff_3 = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd_eff_3->Divide(eta_fwd_3,eta_fwd_mb_3,1.,1.,"b");


TFile file_res(dir + "/results" + specification + ".root","RECREATE");
pt_cntr->Write();
pt_cntr_mb->Write();
pt_fwd->Write();
pt_fwd_mb->Write();
eta_cntr->Write();
eta_cntr_mb->Write();
eta_fwd->Write();
eta_fwd_mb->Write();
phi_cntr->Write();
phi_cntr_mb->Write();
phi_fwd->Write();
phi_fwd_mb->Write();

pt_fwd_eff->Write();
pt_cntr_eff->Write();
eta_fwd_eff->Write();
eta_cntr_eff->Write();
phi_fwd_eff->Write();
phi_cntr_eff->Write();

pt_cntr_2D->Write();
pt_cntr_mb_2D->Write();
pt_fwd_2D->Write();
pt_fwd_mb_2D->Write();
eta_cntr_2D->Write();
eta_cntr_mb_2D->Write();
eta_fwd_2D->Write();
eta_fwd_mb_2D->Write();

pt_fwd_eff_2D->Write();
pt_cntr_eff_2D->Write();
eta_fwd_eff_2D->Write();
eta_cntr_eff_2D->Write();

eta_cntr_eff_1->Write();
eta_cntr_eff_2->Write();
eta_cntr_eff_3->Write();
eta_fwd_eff_1->Write();
eta_fwd_eff_2->Write();
eta_fwd_eff_3->Write();

eta_cntr_mb_1->Write();
eta_cntr_mb_2->Write();
eta_cntr_mb_3->Write();
eta_fwd_mb_1->Write();
eta_fwd_mb_2->Write();
eta_fwd_mb_3->Write();

eta_cntr_1->Write();
eta_cntr_2->Write();
eta_cntr_3->Write();
eta_fwd_1->Write();
eta_fwd_2->Write();
eta_fwd_3->Write();

ps_cntr->Write();
ps_fwd->Write();
    return (EXIT_SUCCESS);
}
