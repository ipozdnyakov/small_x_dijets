#include"TString.h"
#include"TH1.h"
#include"TH2.h"
#include"TSystem.h"
#include"TROOT.h"
#include"TFile.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {

public:
    string specification;
    int  n_event, n_dijets;
    int  n_event_cntr, n_event_fwd;	
    
    Observable(){}
};


class MN : virtual public Observable
{
public:
    Double_t pt_min_1; //pt_min_1 >= pt_min_2
    Double_t pt_min_2;
    Double_t pt_veto;

    int nk_bin, neta_bin, npt_bin, ndphi_bin;

    TH1D *pt, *y, *phi, *dphi[4], *dy;
    TH1D *w2_dy, *excl_dy, *k_factor;
    TH1D *cos_1, *cos_2, *cos_3, *cos2_1, *cos2_2, *cos2_3;
    TH2D *dphi_dy;

    void CalculateErrors();
    void WriteToFile(TString );

    MN(TString , TString, double , double , double);

/*    int NumberOfDijets();
    void CalculateDerivatives();

 private:

    TH1D *raw_cos_1, *raw_cos_2, *raw_cos_3, *raw_cos2_1, *raw_cos2_2, *raw_cos2_3;
    void CalculateCovMatrix();

*/
};

#endif // OBSERVABLE_H
