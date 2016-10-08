#include<TFile.h>
#include<TH1.h>
#include<TGraphAsymmErrors.h>
#include"function.h"
#include"object.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {

	private:
		bool averaged_and_normalized = false;
		Object* object;
		Function* function;
		TH1D *sum_w;
		TH1D *sum_i;
		int n_events = 0;
	public:
		string name;

		Observable(Object *, Function *);
		void ReadEvent(Event *);
		void AverageAndNormalize();
		void WriteToFile(TString );
//-----------------------------------------
		void FillValues(vector<double> , vector<double>);
		Observable(TString , TString , const double *, int );
		void FillData(vector<vector<double>> , double);
};

#endif // OBSERVABLE_H
