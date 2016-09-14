#include<TH1.h>
#include<TH2.h>
#include<TROOT.h>
#include"event.h"

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

using namespace std;

class Measurement {

	private:

	protected:
		TH1D *pt, *eta, *y, *phi;

	public:
		string specification;
		int  n_events = 0, n_entries = 0;

		Measurement(TString , TString);

		void ReadEvent(Event *);
		void WriteToFile(TString );
};


class MN : virtual public Measurement
{
	private:

	public:
		Double_t pt_min_1; //pt_min_1 >= pt_min_2
		Double_t pt_min_2;
		Double_t pt_veto;
		//TH1D *raw_cos_1, *raw_cos_2, *raw_cos_3, *raw_cos2_1, *raw_cos2_2, *raw_cos2_3;
		//void CalculateCovMatrix();

		int  n_event_cntr, n_event_fwd;	

		TH1D *dphi[4], *dy;
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

#endif // MEASUREMENT_H
