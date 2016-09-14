#include<fstream>
#include"event.h"

#ifndef _OBJECT_H
#define	_OBJECT_H
using namespace std;

class Object {

//Event is a set of jets and parameters

	public:
		Event event;
		string type;
	
		Object(Event , string);

};
#endif	/* _OBJECT_H */
