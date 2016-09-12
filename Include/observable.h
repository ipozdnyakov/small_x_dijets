#include<TH1.h>
#include<TH2.h>
#include<TROOT.h>
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include"event.h"
#include"finder.h"


#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {

	private:
		TH1D *pt, *eta, *y, *phi;

	protected:

	public:
		string specification;
		int  n_events = 0, n_entries = 0;
		Observable(TString , TString);
		void ReadEvent(Event *);
		void WriteToFile(TString );
};


class MN : virtual public Observable
{
	private:

	public:
		Double_t pt_min_1; //pt_min_1 >= pt_min_2
		Double_t pt_min_2;
		Double_t pt_veto;
		//TH1D *raw_cos_1, *raw_cos_2, *raw_cos_3, *raw_cos2_1, *raw_cos2_2, *raw_cos2_3;
		//void CalculateCovMatrix();

		int  n_event_cntr, n_event_fwd;	

		TH1D *pt, *y, *phi, *dphi[4], *dy;
		TH1D *w2_dy, *excl_dy, *k_factor;
		TH1D *cos_1, *cos_2, *cos_3, *cos2_1, *cos2_2, *cos2_3;
		TH2D *dphi_dy;

		void CalculateErrors();
		void WriteToFile(TString );

		MN(TString , TString , double , double , double);
		void ReadEvent(Event *);

		//int NumberOfDijets();
		//void CalculateDerivatives();

};

#endif // OBSERVABLE_H
