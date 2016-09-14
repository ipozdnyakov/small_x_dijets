#include<TH1.h>
#include<TGraphAsymmErrors.h>
#include"event.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {

	private:

	protected:
		TH1D *sum_of_weights;
		TH1D *sum_of_square_weights;
		TGraphAsymmErrors *values_and_stats;
		TGraphAsymmErrors *syst_jec;
		TGraphAsymmErrors *syst_jer;
		TGraphAsymmErrors *syst_pile_up;
		TGraphAsymmErrors *syst_merging;
		TGraphAsymmErrors *syst_efficiency;
		TGraphAsymmErrors *syst_total;

	public:
		string name;
		int n_events = 0;
		int n_entries = 0;

		Observable(TString , TString , double *, int );

		void catchEvent(Event *);
		void writeToFile(TString );
		void plotToFile(TString );
};

#endif // OBSERVABLE_H
