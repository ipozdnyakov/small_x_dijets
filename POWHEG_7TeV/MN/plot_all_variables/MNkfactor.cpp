#include <TTree.h>
#include <stdlib.h>
#include <iostream>
#include <TH1.h>
#include "TKey.h"
#include "TFile.h"
#include "TMath.h"
#include <vector>
#include <math.h>

#include "readerfile.h"
#include "finder.h"
#define pi 3.1415926

using namespace std;

void treereader(Int_t *n_event,	TString name,
        TH1D *pt, TH1D *y, TH1D *phi, TH1D *dphi_0, TH1D *dphi_1, TH1D *dphi_2, TH1D *dphi_3,  TH1D *dy,
		  TH1D *w2_dy, TH1D *excl_dy,
        TH1D *cos_1, TH1D *cos_2, TH1D *cos_3, TH1D *cos2_1, TH1D *cos2_2, TH1D *cos2_3,
        TH2D *dphi_dy,
        Double_t pt_min, Double_t pt_veto
        ){

	vector<Double_t> pt_v, y_v, phi_v;
	vector<Double_t>::iterator m, n, q;

        Bool_t veto = true;
	Int_t nentries = 0, nEvent = 0;
        Double_t dy_MN = 0., dphi_MN = 0.;

        Double_t vard[6] = {0.,0.,0.,0.,0.,0.};
        Int_t vari[3] = {0,0,0};
        Double_t weight = 0.;

TFile Jfile(name);
TTree* tree;
tree = (TTree*) Jfile.Get("tree");
nentries = tree->GetEntries();
cout << "Entries: " << nentries << "\n";

tree->SetBranchAddress("pt",&vard[0]);
tree->SetBranchAddress("eta",&vard[1]);
tree->SetBranchAddress("phi",&vard[2]);
tree->SetBranchAddress("rap",&vard[3]);
tree->SetBranchAddress("weight",&vard[4]);
//tree->SetBranchAddress("nPV",&vari[0]);
tree->SetBranchAddress("ievt",&vard[5]);

tree->GetEntry(0);
nEvent = vard[5];

for(int i = 0 ; i < nentries ; ++i){
	weight = vard[4];
	tree->GetEntry(i);
	//nPV check disabled if(vari[0] > 1) continue;

//cout << "Event number: " << vard[5] << "\t" << nEvent << "\n";

	if(vard[5] == nEvent){						//in Event
		if((vard[0] > pt_min) && (fabs(vard[3]) < 4.7)){
		  pt_v.push_back(vard[0]);
		  phi_v.push_back(vard[2]);
		  y_v.push_back(vard[3]);
		}
		if((vard[0] < pt_min)&&(vard[0] > pt_veto)) veto = false;
	}else{								//out Event

	//back initialization PART-1
	nEvent = vard[5];
	i = (i-1);
	//-------------------------

	if(pt_v.size() < 2) continue;
	(*n_event)++;

   	for(int j = 0; j < pt_v.size(); j++){
    		pt->Fill(pt_v[j],weight);
    		y->Fill(y_v[j],weight);
    		phi->Fill(phi_v[j],weight);
	}

	dy_MN = find_dy(y_v);
	dphi_MN = find_dphi(y_v,phi_v);

	dphi_0->Fill(dphi_MN,weight);
	dy->Fill(dy_MN,weight);
	w2_dy->Fill(dy_MN,weight*weight);
	dphi_dy->Fill(dphi_MN,dy_MN,weight);

	if((dy_MN > 0.)&&(dy_MN < 3.))dphi_1->Fill(dphi_MN,weight);
	if((dy_MN > 3.)&&(dy_MN < 6.))dphi_2->Fill(dphi_MN,weight);
	if((dy_MN > 6.)&&(dy_MN < 9.4))dphi_3->Fill(dphi_MN,weight);

	cos_1->Fill(dy_MN, weight*cos(pi - dphi_MN) );
	cos2_1->Fill(dy_MN,weight*pow(cos(pi - dphi_MN),2));
	cos_2->Fill(dy_MN,weight*cos(2*(pi - dphi_MN)));
	cos2_2->Fill(dy_MN,weight*pow(cos(2*(pi - dphi_MN)),2));
	cos_3->Fill(dy_MN,weight*cos(3*(pi - dphi_MN)));
	cos2_3->Fill(dy_MN,weight*pow(cos(3*(pi - dphi_MN)),2));

	if((pt_v.size() == 2)&&veto){
		excl_dy->Fill(dy_MN,weight);
	}

	//back initialization PART-2
	veto = true;
	pt_v.clear();
	y_v.clear();
	phi_v.clear();
	dy_MN = 0.;
	dphi_MN = 0.;
   	}
}
//cout << *n_event << "\n";
};

