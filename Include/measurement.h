#include<TH1.h>
#include<TH2.h>
#include<TROOT.h>
#include"observable.h"
#include"function.h"
#include"object.h"
#include"event.h"

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

using namespace std;

class Measurement {
	private:
		bool averaged_and_normalized = false;
		vector<vector<Observable*>> observables;
		vector<Object*> objects;
		vector<Function*> functions;
	public:
		string specification;
		int  n_events = 0;
		Measurement(TString , TString);
		void IncludeObject(Object *);
		void IncludeFunction(Function *);
		void ReadEvent(Event *);
		void AverageAndNormalize();
		void WriteToFile(TString );
};
#endif // MEASUREMENT_H
