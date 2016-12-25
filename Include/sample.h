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

	Sample(TString );
	bool CheckEvent(Event *);
};
#endif	/* _SAMPLE_H */
