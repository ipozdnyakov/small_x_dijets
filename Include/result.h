#include<TFile.h>
#include<TH1.h>
#include<TGraphAsymmErrors.h>

#ifndef RESULT_H
#define RESULT_H

using namespace std;

class Result {
	private:
		TH1D *result;
		TGraphAsymmErrors *syst;

	public:
		TString name;
		Result();
		void WriteToFile(TString );
};
#endif // RESULT_H
