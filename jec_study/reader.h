#include"TKey.h"
#include"TFile.h"
#include"TH1D.h"
#include"TH2D.h"
#include"TMath.h"
#include"TProfile.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#ifndef _READERFILE_H
#define	_READERFILE_H
using namespace std;
void treereader(Int_t *, Int_t *, TString ,
        TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *,
        TH1D *, TH1D *,TH1D *, TH1D *, TH1D *,TH1D *,
        TH2D *, 
        Double_t , Double_t , Double_t , Double_t , 
	JetCorrectionUncertainty *
	 );
#endif	/* _READERFILE_H */
