#include<TH1.h>
#include<TH2.h>
#include<TROOT.h>
#include"event.h"
#include"dataset.h"
#include"observable.h"
#include"function.h"
#include"object.h"
#include"result.h"

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

using namespace std;

class Measurement {
	private:
		vector<vector<vector<Observable*>>> observables;
		//[i-object][j-function][k-sample]
		vector<Function*> functions;
		vector<Object*> objects;
		vector<Sample*> samples;
		vector<Result*> results;
	public:
		string specification;
		int  n_events = 0;

		Measurement(TString , TString);

		void IncludeFunction(Function *);
		void IncludeObject(Object *);
		void IncludeSample(Sample *);

		void ReadDataset(Dataset *);
		void ReadDatasetFast(Dataset *);
		void ReadFile(string , Dataset *);
		void ReadEvent(Event *);

		void CalculateResult(Result *);
		void WriteToFile(TString );

		Observable* GetObservable(TString , TString , TString );
};
#endif // MEASUREMENT_H
