#include"event.h"

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

	template<class M> void ReadSample(M *);

	template<class M> void ReadFile(string , M *);

};
#endif	/* _SAMPLE_H */
