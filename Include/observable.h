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

		TH1D *sum_w;
		TH1D *sum_w_jecunc_plus;
		TH1D *sum_w_jecunc_minus;

		TH1D *jec;
		TH1D *unc;
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
