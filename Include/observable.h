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
		TString name;
		Observable(Object *, Function *, TString);
		void ReadEvent(Event *);
		void FillValues(vector<double> , vector<double>);
		void AverageAndNormalize();
		void WriteToFile(TString );
};
#endif // OBSERVABLE_H
