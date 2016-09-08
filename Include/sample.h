#include "observable.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#ifndef _SAMPLE_H
#define	_SAMPLE_H
using namespace std;

class Sample {

protected:
	string list_name;

public:
	Sample(): list_name("FSQJets_2015_2016") { }
	Sample(string str): list_name(str) { }

	void read_list(
                Observable *,
                Double_t , Double_t , Double_t , Double_t ,
                JetCorrectionUncertainty *
	);

	void read_file(
		string ,
		Observable *, 
        	Double_t , Double_t , Double_t , Double_t , 
		JetCorrectionUncertainty *
	);
};
#endif	/* _SAMPLE_H */
