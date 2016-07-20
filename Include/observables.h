#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>

#include"TString.h"
#include"TH1.h"
#include"TH2.h"
#include"TSystem.h"
#include"TROOT.h"
#include"TFile.h"

#ifndef OBSERVABLES_H
#define OBSERVABLES_H

using namespace std;

class Observables
{
 public:
    int  n_event, n_dijets;
    int  n_event_cntr, n_event_fwd;

    int nk_bin, neta_bin, npt_bin, ndphi_bin;

    TH1D *pt, *y, *phi, *dphi[4], *dy;
    TH1D *w2_dy, *excl_dy, *k_factor;
    TH1D *cos_1, *cos_2, *cos_3, *cos2_1, *cos2_2, *cos2_3;
    TH2D *dphi_dy;

    Observables(TString , TString);
    ~Observables();

    void CalculateErrors();
    void WriteToFile(TString name);

/*    int NumberOfDijets();
    void CalculateDerivatives();

 private:

    double dy_bins[16]={0,0.5,1.0,1.5,2.0,2.5,3.0,
                         3.5,4.0,4.5,5.0,5.5,6.0,
                         7.0,8.0,9.4};


    double pt_bins[14]={15,20,25,30,35,40,50,60,80,100,120,160,200,300};

    double dphi_bins[11]={0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.70, 0.8, 0.9, 1.};
    for(i = 0; i < 11; i++){
                        dphi_bins[i] = dphi_bins[i]*pi;
    }

    int ndy_bin = sizeof(dy_bins)/sizeof(dy_bins[0]);
    int npt_bin = sizeof(pt_bins)/sizeof(pt_bins[0]);
    int ndphi_bin = sizeof(dphi_bins)/sizeof(dphi_bins[0]);


    TH1D *raw_cos_1, *raw_cos_2, *raw_cos_3, *raw_cos2_1, *raw_cos2_2, *raw_cos2_3;
    void CalculateCovMatrix();

    const double eta_towers_bins[83]={
		-5.191,-4.889,-4.716,-4.538,-4.363,-4.191,
                -4.013,-3.839,-3.664,-3.489,-3.314,-3.139,
		-2.964,-2.853,-2.650,-2.500,-2.322,-2.172,
		-2.043,-1.930,-1.830,-1.740,-1.653,-1.566,
		-1.479,-1.392,-1.305,-1.218,-1.131,-1.044,
		-0.957,-0.870,-0.783,-0.696,-0.609,-0.522,
		-0.435,-0.348,-0.261,-0.174,-0.087, 0,
		0.087,0.174,0.261,0.348,0.435,0.522,0.609,
		0.696,0.783,0.870,0.957,1.044,1.131,1.218,
		1.305,1.392,1.479,1.566,1.653,1.740,1.830,
		1.930,2.043,2.172,2.322,2.500,2.650,2.853,
		2.964,3.139,3.314,3.489,3.664,3.839,4.013,
		4.191,4.363,4.538,4.716,4.889,5.191};
    const int neta_towers = 83;
    const double phi_towers_bins[72];
    const int nphi_towers = 72;*/
};

#endif // OBSERVABLES_H
