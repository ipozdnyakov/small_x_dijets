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
    bool check_trigger;

    TString dir_name="DATA_13TeV";
    TString dir  = "/afs/cern.ch/work/i/ivanp/2015_Decorrelator/CMSSW_7_4_15/src/" + dir_name + "/";

    //TString list_name = "/FSQJets3_VdMscan_list";
    TString list_name = "/FSQJets3_LowPU_list";
    check_trigger = true;
	
    //TString list_name = "/MinBias_VdMscan_list";
    //TString list_name = "/MinBias_LowPU_list";
    //check_trigger = false; 

    TString list = dir + "listing" + list_name;
    Double_t pt_min_1 = 55.; // pt_1 >= pt_2
    Double_t pt_min_2 = 35.;
    Double_t eta_merging = 2.5;
    Double_t pt_veto  = 35.;
    Double_t FWD_weight = 0.47;
	//~0.3 for 2 eta 30-30 GeV INCL
	//~0.32 for 2 eta 20-20 GeV INCL
	//~0.47 for 2.5 eta 20-20 GeV INCL
	//~0.49 for 2.5 eta 35-35 GeV INCL
	//~0.50 for 2.5 eta 35-45 GeV INCL
	//~0.51 for 2.5 eta 35-55 GeV INCL

    TString Pt_min = "_pt";
				Pt_min += pt_min_1;
				Pt_min += "_";
				Pt_min += pt_min_2;
				Pt_min += "_merg";
				Pt_min += eta_merging;
    TString Pt_veto = "_veto";
				Pt_veto += pt_veto;
    TString specification = "_data_13TeV_FSQJets3_LowPU_dy0_9.4_MERGING" + Pt_min;//+Pt_veto;

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

    double ptbins[21]={15,16,17,18,19,20,21,23,25,27,30,35,40,50,60,80,100,120,160,200,300};

    double dphi_bins[11]={0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.70, 0.8, 0.9, 1.};
    for(i = 0; i < 11; i++){dphi_bins[i] = dphi_bins[i]*pi;}

    int nk_bin = sizeof(kfacbins)/sizeof(kfacbins[0]);
    int neta_bin = sizeof(etabins)/sizeof(etabins[0]);
    int npt_bin = sizeof(ptbins)/sizeof(ptbins[0]);
    int ndphi_bin = sizeof(dphi_bins)/sizeof(dphi_bins[0]);
//------------------------------------HISTOS---------------------------------------
    TH1D *pt, *eta, *phi;
    TH1D *dy_cntr_MN, *dy_fwd_MN;
    TH1D *dy_cntr, *dy_fwd;
    TH1D *dy_cntr_minus_fwd_MN;
    TH1D *dy_cntr_minus_fwd;
    TH1D *pt_cntr;
    TH1D *pt_fwd;
    TH1D *eta_cntr;
    TH1D *eta_fwd;
   
        histname = "pt";  histname += specification;
        pt = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt->Sumw2();

        histname = "eta";  histname += specification;
        eta = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta->Sumw2();

        histname = "phi";  histname += specification;
        phi = new TH1D(histname, dir_name, 36, -pi, pi);
        phi->Sumw2();

        histname = "dy_cntr";  histname += specification;
        dy_cntr = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_cntr->Sumw2();

        histname = "dy_fwd";  histname += specification;
        dy_fwd = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_fwd->Sumw2();

        histname = "dy_cntr_MN";  histname += specification;
        dy_cntr_MN = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_cntr_MN->Sumw2();

        histname = "dy_fwd_MN";  histname += specification;
        dy_fwd_MN = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_fwd_MN->Sumw2();

        histname = "dy_cntr_minus_fwd_MN";  histname += specification;
        dy_cntr_minus_fwd_MN = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_cntr_minus_fwd_MN->Sumw2();

        histname = "dy_cntr_minus_fwd";  histname += specification;
        dy_cntr_minus_fwd = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_cntr_minus_fwd->Sumw2();

        histname = "pt_cntr";  histname += specification;
        pt_cntr = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_cntr->Sumw2();

        histname = "pt_fwd";  histname += specification;
        pt_fwd = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt_fwd->Sumw2();

        histname = "eta_cntr";  histname += specification;
        eta_cntr = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_cntr->Sumw2();

        histname = "eta_fwd";  histname += specification;
        eta_fwd = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        eta_fwd->Sumw2();

    TH1D *phi_cntr_1, *phi_cntr_2, *phi_cntr_3;
    TH1D *phi_fwd_1, *phi_fwd_2, *phi_fwd_3;

        histname = "phi_cntr_1";  histname += specification;
        phi_cntr_1 = new TH1D(histname, dir_name, 72, -pi, pi);
        phi_cntr_1->Sumw2();

        histname = "phi_cntr_2";  histname += specification;
        phi_cntr_2 = new TH1D(histname, dir_name, 36, -pi, pi);
        phi_cntr_2->Sumw2();

        histname = "phi_cntr_3";  histname += specification;
        phi_cntr_3 = new TH1D(histname, dir_name, 36, -pi, pi);
        phi_cntr_3->Sumw2();

        histname = "phi_fwd_1";  histname += specification;
        phi_fwd_1 = new TH1D(histname, dir_name, 72, -pi, pi);
        phi_fwd_1->Sumw2();

        histname = "phi_fwd_2";  histname += specification;
        phi_fwd_2 = new TH1D(histname, dir_name, 36, -pi, pi);
        phi_fwd_2->Sumw2();

        histname = "phi_fwd_3";  histname += specification;
        phi_fwd_3 = new TH1D(histname, dir_name, 36, -pi, pi);
        phi_fwd_3->Sumw2();

    TH1D *nPV_fwd, *nPV_cntr;
   
        histname = "nPV_cntr";  histname += specification;
        nPV_cntr = new TH1D(histname, dir_name, 5, 0.5, 5.5);
        nPV_cntr->Sumw2();

        histname = "nPV_fwd";  histname += specification;
        nPV_fwd = new TH1D(histname, dir_name, 5, 0.5, 5.5);
        nPV_fwd->Sumw2();

    TH1D *dy, *dy_MN;

        histname = "dy";  histname += specification;
        dy = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy->Sumw2();

        histname = "dy_MN";  histname += specification;
        dy_MN = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy_MN->Sumw2();


//------------------------------------PROCESSING---------------------------------------
int j = 0;
int i_file = 0;
Int_t n_event_cntr = 0;
Int_t n_event_fwd = 0;
Int_t n_event_overlap = 0;

    file = fopen(list,"r");

    while(!feof(file))
    {
         fgets(str, 256, file);
         if(feof(file)) break;
         while(((int)str[j]) != 10){name += str[j]; j++;}
         j = 0;
    		if(i_file % 10 == 0){  cout << name << "\n"; i_file = 0;}
			treereader(&n_event_cntr, &n_event_fwd, &n_event_overlap, name,
				 pt, eta, phi,
				 dy_cntr_MN, dy_fwd_MN,
				 dy_cntr, dy_fwd,
				 dy_cntr_minus_fwd_MN,
				 dy_cntr_minus_fwd,
				 dy,
				 dy_MN,
				 pt_cntr,
    				 pt_fwd,
    				 eta_cntr,
    				 eta_fwd,
				 phi_cntr_1, phi_cntr_2, phi_cntr_3,
				 phi_fwd_1, phi_fwd_2, phi_fwd_3,
				 nPV_cntr, nPV_fwd,
				 eta_merging, pt_min_1, pt_min_2, FWD_weight, pt_veto, 
				 check_trigger);
			name = "";
			i_file++;
	  };
cout << "Events: cntr - " << n_event_cntr << " fwd - " << n_event_fwd << " overlap - " << n_event_overlap << "\n";

//------------------------------------PRINTING---------------------------------------

TH1D *weight_dy_MN, *weight_dy;

        histname = "wight_sample_dy_MN";  histname += specification;
        weight_dy_MN = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        weight_dy_MN->Sumw2();

        histname = "wight_sample_dy";  histname += specification;
        weight_dy = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        weight_dy->Sumw2();

for(i = 1; i <= npt_bin; i++){
	if(dy_fwd_MN->GetBinContent(i) > 0){
		weight_dy_MN->SetBinContent(i, (dy_cntr_MN->GetBinContent(i) 
						- dy_cntr_minus_fwd_MN->GetBinContent(i))
						/dy_fwd_MN->GetBinContent(i));
	}
}

for(i = 1; i <= npt_bin; i++){
	if(dy_fwd->GetBinContent(i) > 0){
		weight_dy->SetBinContent(i, (dy_cntr->GetBinContent(i) 
						- dy_cntr_minus_fwd->GetBinContent(i))
						/dy_fwd->GetBinContent(i));
	}
}

TFile file_res(dir + "/results" + specification + ".root","RECREATE");

//nPV_cntr->Write();
//nPV_fwd->Write();

weight_dy_MN->Write();
weight_dy->Write();

/*pt->Write();
for(i = 1; i <= npt_bin; i++){
pt->SetBinContent(i,pt->GetBinContent(i)/pt->GetBinWidth(i));
pt->SetBinError(i,pt->GetBinError(i)/pt->GetBinWidth(i));
}
histname = pt->GetName(); histname += "_bin_width_norm";
pt->SetName(histname);
pt->Write();*/

pt_cntr->Write();
for(i = 1; i <= npt_bin; i++){
pt_cntr->SetBinContent(i,pt_cntr->GetBinContent(i)/pt_cntr->GetBinWidth(i));
pt_cntr->SetBinError(i,pt_cntr->GetBinError(i)/pt_cntr->GetBinWidth(i));
}
histname = pt_cntr->GetName(); histname += "_bin_width_norm";
pt_cntr->SetName(histname);
pt_cntr->Write();

pt_fwd->Write();
for(i = 1; i <= npt_bin; i++){
pt_fwd->SetBinContent(i,pt_fwd->GetBinContent(i)/pt_fwd->GetBinWidth(i));
pt_fwd->SetBinError(i,pt_fwd->GetBinError(i)/pt_fwd->GetBinWidth(i));
}
histname = pt_fwd->GetName(); histname += "_bin_width_norm";
pt_fwd->SetName(histname);
pt_fwd->Write();


/*eta->Write();
for(i = 1; i <= neta_bin; i++){
eta->SetBinContent(i,eta->GetBinContent(i)/eta->GetBinWidth(i));
eta->SetBinError(i,eta->GetBinError(i)/eta->GetBinWidth(i));
}
histname = eta->GetName(); histname += "_bin_width_norm";
eta->SetName(histname);
eta->Write();*/

eta_cntr->Write();
for(i = 1; i <= neta_bin; i++){
eta_cntr->SetBinContent(i,eta_cntr->GetBinContent(i)/eta_cntr->GetBinWidth(i));
eta_cntr->SetBinError(i,eta_cntr->GetBinError(i)/eta_cntr->GetBinWidth(i));
}
histname = eta_cntr->GetName(); histname += "_bin_width_norm";
eta_cntr->SetName(histname);
eta_cntr->Write();

eta_fwd->Write();
for(i = 1; i <= neta_bin; i++){
eta_fwd->SetBinContent(i,eta_fwd->GetBinContent(i)/eta_fwd->GetBinWidth(i));
eta_fwd->SetBinError(i,eta_fwd->GetBinError(i)/eta_fwd->GetBinWidth(i));
}
histname = eta_fwd->GetName(); histname += "_bin_width_norm";
eta_fwd->SetName(histname);
eta_fwd->Write();


dy_cntr->Write();
for(i = 1; i <= nk_bin; i++){
dy_cntr->SetBinContent(i,dy_cntr->GetBinContent(i)/dy_cntr->GetBinWidth(i));
dy_cntr->SetBinError(i,dy_cntr->GetBinError(i)/dy_cntr->GetBinWidth(i));
}
histname = dy_cntr->GetName(); histname += "_bin_width_norm";
dy_cntr->SetName(histname);
dy_cntr->Write();

dy_fwd->Write();
for(i = 1; i <= nk_bin; i++){
dy_fwd->SetBinContent(i,dy_fwd->GetBinContent(i)/dy_fwd->GetBinWidth(i));
dy_fwd->SetBinError(i,dy_fwd->GetBinError(i)/dy_fwd->GetBinWidth(i));
}
histname = dy_fwd->GetName(); histname += "_bin_width_norm";
dy_fwd->SetName(histname);
dy_fwd->Write();

dy_cntr_MN->Write();
for(i = 1; i <= nk_bin; i++){
dy_cntr_MN->SetBinContent(i,dy_cntr_MN->GetBinContent(i)/dy_cntr_MN->GetBinWidth(i));
dy_cntr_MN->SetBinError(i,dy_cntr_MN->GetBinError(i)/dy_cntr_MN->GetBinWidth(i));
}
histname = dy_cntr_MN->GetName(); histname += "_bin_width_norm";
dy_cntr_MN->SetName(histname);
dy_cntr_MN->Write();

dy_fwd_MN->Write();
for(i = 1; i <= nk_bin; i++){
dy_fwd_MN->SetBinContent(i,dy_fwd_MN->GetBinContent(i)/dy_fwd_MN->GetBinWidth(i));
dy_fwd_MN->SetBinError(i,dy_fwd_MN->GetBinError(i)/dy_fwd_MN->GetBinWidth(i));
}
histname = dy_fwd_MN->GetName(); histname += "_bin_width_norm";
dy_fwd_MN->SetName(histname);
dy_fwd_MN->Write();


dy_cntr_minus_fwd_MN->Write();
for(i = 1; i <= nk_bin; i++){
dy_cntr_minus_fwd_MN->SetBinContent(i,dy_cntr_minus_fwd_MN->GetBinContent(i)/dy_cntr_minus_fwd_MN->GetBinWidth(i));
dy_cntr_minus_fwd_MN->SetBinError(i,dy_cntr_minus_fwd_MN->GetBinError(i)/dy_cntr_minus_fwd_MN->GetBinWidth(i));
}
histname = dy_cntr_minus_fwd_MN->GetName(); histname += "_bin_width_norm";
dy_cntr_minus_fwd_MN->SetName(histname);
dy_cntr_minus_fwd_MN->Write();

dy_cntr_minus_fwd->Write();
for(i = 1; i <= nk_bin; i++){
dy_cntr_minus_fwd->SetBinContent(i,dy_cntr_minus_fwd->GetBinContent(i)/dy_cntr_minus_fwd->GetBinWidth(i));
dy_cntr_minus_fwd->SetBinError(i,dy_cntr_minus_fwd->GetBinError(i)/dy_cntr_minus_fwd->GetBinWidth(i));
}
histname = dy_cntr_minus_fwd->GetName(); histname += "_bin_width_norm";
dy_cntr_minus_fwd->SetName(histname);
dy_cntr_minus_fwd->Write();


dy->Write();
for(i = 1; i <= nk_bin; i++){
dy->SetBinContent(i,dy->GetBinContent(i)/dy->GetBinWidth(i));
dy->SetBinError(i,dy->GetBinError(i)/dy->GetBinWidth(i));
}
histname = dy->GetName(); histname += "_bin_width_norm";
dy->SetName(histname);
dy->Write();

dy_MN->Write();
for(i = 1; i <= nk_bin; i++){
dy_MN->SetBinContent(i,dy_MN->GetBinContent(i)/dy_MN->GetBinWidth(i));
dy_MN->SetBinError(i,dy_MN->GetBinError(i)/dy_MN->GetBinWidth(i));
}
histname = dy_MN->GetName(); histname += "_bin_width_norm";
dy_MN->SetName(histname);
dy_MN->Write();

/*phi->Write();
for(i = 1; i <= phi->GetNbinsX(); i++){
phi->SetBinContent(i,phi->GetBinContent(i)/phi->GetBinWidth(i));
phi->SetBinError(i,phi->GetBinError(i)/phi->GetBinWidth(i));
}
histname = phi->GetName(); histname += "_bin_width_norm";
phi->SetName(histname);
phi->Write();*/

phi_cntr_1->Write();
for(i = 1; i <= phi_cntr_1->GetNbinsX(); i++){
phi_cntr_1->SetBinContent(i,phi_cntr_1->GetBinContent(i)/phi_cntr_1->GetBinWidth(i));
phi_cntr_1->SetBinError(i,phi_cntr_1->GetBinError(i)/phi_cntr_1->GetBinWidth(i));
}
histname = phi_cntr_1->GetName(); histname += "_bin_width_norm";
phi_cntr_1->SetName(histname);
phi_cntr_1->Write();

phi_cntr_2->Write();
for(i = 1; i <= phi_cntr_2->GetNbinsX(); i++){
phi_cntr_2->SetBinContent(i,phi_cntr_2->GetBinContent(i)/phi_cntr_2->GetBinWidth(i));
phi_cntr_2->SetBinError(i,phi_cntr_2->GetBinError(i)/phi_cntr_2->GetBinWidth(i));
}
histname = phi_cntr_2->GetName(); histname += "_bin_width_norm";
phi_cntr_2->SetName(histname);
phi_cntr_2->Write();

phi_cntr_3->Write();
for(i = 1; i <= phi_cntr_3->GetNbinsX(); i++){
phi_cntr_3->SetBinContent(i,phi_cntr_3->GetBinContent(i)/phi_cntr_3->GetBinWidth(i));
phi_cntr_3->SetBinError(i,phi_cntr_3->GetBinError(i)/phi_cntr_3->GetBinWidth(i));
}
histname = phi_cntr_3->GetName(); histname += "_bin_width_norm";
phi_cntr_3->SetName(histname);
phi_cntr_3->Write();

phi_fwd_1->Write();
for(i = 1; i <= phi_fwd_1->GetNbinsX(); i++){
phi_fwd_1->SetBinContent(i,phi_fwd_1->GetBinContent(i)/phi_fwd_1->GetBinWidth(i));
phi_fwd_1->SetBinError(i,phi_fwd_1->GetBinError(i)/phi_fwd_1->GetBinWidth(i));
}
histname = phi_fwd_1->GetName(); histname += "_bin_width_norm";
phi_fwd_1->SetName(histname);
phi_fwd_1->Write();

phi_fwd_2->Write();
for(i = 1; i <= phi_fwd_2->GetNbinsX(); i++){
phi_fwd_2->SetBinContent(i,phi_fwd_2->GetBinContent(i)/phi_fwd_2->GetBinWidth(i));
phi_fwd_2->SetBinError(i,phi_fwd_2->GetBinError(i)/phi_fwd_2->GetBinWidth(i));
}
histname = phi_fwd_2->GetName(); histname += "_bin_width_norm";
phi_fwd_2->SetName(histname);
phi_fwd_2->Write();

phi_fwd_3->Write();
for(i = 1; i <= phi_fwd_3->GetNbinsX(); i++){
phi_fwd_3->SetBinContent(i,phi_fwd_3->GetBinContent(i)/phi_fwd_3->GetBinWidth(i));
phi_fwd_3->SetBinError(i,phi_fwd_3->GetBinError(i)/phi_fwd_3->GetBinWidth(i));
}
histname = phi_fwd_3->GetName(); histname += "_bin_width_norm";
phi_fwd_3->SetName(histname);
phi_fwd_3->Write();

    return (EXIT_SUCCESS);
}
