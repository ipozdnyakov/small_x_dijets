#include<fstream>
#include<TString.h>
#include"event.h"

#ifndef _OBJECT_H
#define	_OBJECT_H
using namespace std;

class Object {

	protected:
		TString specification = "";
		double pt_min_1 = 0.;
		double pt_min_2 = 0.;
		double pt_veto = 0.;

	public:

	        vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
        	vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
	        Bool_t veto = true;

		vector<double> pt;
		vector<double> eta;
		vector<double> rap;
		vector<double> phi;

		vector<double> dphi;
		vector<double> dy;
	
		Object(double , double , double);
		void ReadEvent(Event *);
};
#endif	/* _OBJECT_H */
