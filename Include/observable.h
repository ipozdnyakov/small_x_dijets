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
		int n_events = 0;
		Object* object;
		Function* function;
		TH1D *data,*jecp,*jecm,*hpu,*lpu;

		void FillValues(string , vector<double> , vector<double>);

	public:
		TString name;
		Observable(Object *, Function *, TString);
		void ReadEvent(Event *);
		void AverageAndNormalize();
		void WriteToFile(TString );
};
#endif // OBSERVABLE_H
