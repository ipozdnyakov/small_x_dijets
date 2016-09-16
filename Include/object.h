#include<fstream>
#include"event.h"

#ifndef _OBJECT_H
#define	_OBJECT_H
using namespace std;

class Object {

	protected:

		double pt_min_1 = 0.;
		double pt_min_2 = 0.;
		double pt_veto = 0.;

	public:

		vector<double> pt;
		vector<double> eta;
		vector<double> rap;
		vector<double> phi;

		vector<double> dphi;
		vector<double> dy;
	
		Object(double , double , double);

};
#endif	/* _OBJECT_H */
