/* 
 * File:   printer.h
 * Author: ivanp
 *
 * Created on 29 Март 2011 г., 16:34
 */
#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<string>
#include"TCanvas.h"
#include"TString.h"
#include"TH1.h"
#include"TPaveText.h"
#include"TStyle.h"
#include"TSystem.h"
#include"TROOT.h"
#include"TEnv.h"
#include"TImage.h"
#include"TPad.h"
#include"TLatex.h"
#include<vector>
#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "readerfile.h"
#include "TH2.h"
#include "TProfile.h"
#include "TError.h"
#ifndef _FINDER_H
#define	_FINDER_H
using namespace std;

	Int_t find_closest(Double_t , Double_t , vector<Double_t> , vector<Double_t> , Double_t *, Int_t );

	Double_t find_dy(vector<Double_t> );

	Double_t find_dphi(vector<Double_t> , vector<Double_t> );

	Int_t find_i_min(vector<Double_t> );

	Int_t find_i_max(vector<Double_t> );

#endif	/* _FINDER_H */

