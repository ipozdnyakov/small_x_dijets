#include<TString.h>
#include"event.h"

#ifndef _SAMPLE_H
#define	_SAMPLE_H

using namespace std;

class Sample {

//Sample is a set of events, on which observable can be measured

protected:

public:
	TString name;
	double weight = 1.;

	Sample(TString );
	bool CheckEvent(Event *);
	bool CheckDiJetPt(Event *, double);
	bool CheckDiJetPtEta(Event *, double, double);

};
#endif	/* _SAMPLE_H */
