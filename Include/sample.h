#include"event.h"
#include"observable.h"
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#ifndef _SAMPLE_H
#define	_SAMPLE_H
using namespace std;

class Sample {

//Sample is a set of *.root files listed in the file in ./listing
//the name of the file is the name of the sample

protected:
	string name;

public:
	Sample(): name("FSQJets_2015_2016") { }
	Sample(string str): name(str) { }

	template <class Obs> void ReadSample(Obs *);

	template <class Obs> void ReadFile(string , Obs *);

	void ReadFile(string , MN *);

};
#endif	/* _SAMPLE_H */
