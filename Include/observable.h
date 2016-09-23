#include<TFile.h>
#include<TH1.h>
#include<TGraphAsymmErrors.h>
#include"object.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {

	protected:
		bool averaged_and_normalized = false;

		TH1D *sum_of_weights;
		TH1D *sum_of_square_weights;
		TH1D *jec;
		TH1D *unc;
		TGraphAsymmErrors *values_and_stats;
		TGraphAsymmErrors *syst_jec;
		TGraphAsymmErrors *syst_jer;
		TGraphAsymmErrors *syst_pile_up;
		TGraphAsymmErrors *syst_merging;
		TGraphAsymmErrors *syst_efficiency;
		TGraphAsymmErrors *syst_total;

		TH1D *average_jec;
		TH1D *average_unc;
	public:
		string name;
		int n_events = 0;
		int n_entries = 0;

		Observable(TString , TString , const double *, int );

		void CatchObject(Object *, string );
		void FillData(vector<vector<double>> , double);
		void WriteToFile(TString );
		void PlotToFile(TString );
		void AverageAndNormalize();
};

#endif // OBSERVABLE_H
