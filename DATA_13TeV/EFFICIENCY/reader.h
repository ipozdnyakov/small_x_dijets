#include"TKey.h"
#include"TFile.h"
#include"TH1D.h"
#include"TH2D.h"
#include"TMath.h"
#include"TProfile.h"
#ifndef _READERFILE_H
#define	_READERFILE_H
using namespace std;
void treereader(Int_t *, Int_t *, TString ,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH2D *, TH2D *,
        TH2D *, TH2D *,
        TH2D *, TH2D *,
        TH2D *, TH2D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *, TH1D *,
        TH1D *, TH1D *,
        Double_t 
	 );
#endif	/* _READERFILE_H */
