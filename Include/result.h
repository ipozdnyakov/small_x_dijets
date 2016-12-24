#include<TFile.h>
#include<TH1.h>
#include<TGraphAsymmErrors.h>

#ifndef RESULT_H
#define RESULT_H

using namespace std;

class Result {
	private:

	public:
		TH1D *result;
		TGraphAsymmErrors *syst;
		TString name;
		Result(TString );
		void WriteToFile(TString );
};
#endif // RESULT_H
