#include"measurement.h"

#ifndef _SAMPLE_H
#define	_SAMPLE_H

using namespace std;

class Sample {

//Sample is a set of *.root files listed in the file in ./listing
//the name of the file is the name of the sample

protected:
	string name;
	TString tree_name;
	TString run_num_name, event_num_name, nPV_name;
	TString pt_name, phi_name, eta_name, rap_name;
	TString CNTR_trg_name, FWD2_trg_name, FWD3_trg_name;
	TString cor_name, unc_name;

public:
	Sample(): name("FSQJets_2015_2016") { }
	Sample(string str): name(str) { }

	void ReadSample(Measurement *);
	void Set13TeVNames();
	void Set7TeVNames();
	void ReadFile(string , Measurement *);

};
#endif	/* _SAMPLE_H */
