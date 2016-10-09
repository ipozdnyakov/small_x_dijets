#include"object.h"

#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class Function {

	public:
		string name;
		const double *bins;
		int n_bins;
		vector<double> values;
		vector<double> weights;

		Function(TString , const double *, int );
		void CalculateValues(Object *);
		void SetPlainWeights(Object *);
		void SetDphiInDrap(double , double , Object *);
		void SetDrapInDphi(double , double , Object *);
		void SetCosNDphiVsDrap(double , Object*);
		void Print();
		void Clear();
};

#endif // FUNCTION_H
