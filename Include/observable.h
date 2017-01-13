#include<TFile.h>
#include<TH1.h>
#include<TGraphAsymmErrors.h>
#include"sample.h"
#include"function.h"
#include"object.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

using namespace std;

class Observable {
	private:
		int n_events = 0;
		Object* object;
		Function* function;
		Sample* sample;

		void FillValues(string , vector<double> , vector<double>);

	public:
		TH1D *data,*jecp,*jecm,*hpu,*lpu;

		TString name;
		Observable(Object *, Function *, Sample *);
		void ReadEvent(Event *);
		void WriteToFile(TString );
};
#endif // OBSERVABLE_H
