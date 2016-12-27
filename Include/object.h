#include<fstream>
#include<TString.h>
#include"event.h"

#ifndef _OBJECT_H
#define	_OBJECT_H
using namespace std;

class Object {

	protected:
		TString specification = "";
		double pt_min_H = 0.;
		double pt_min_L = 0.;
		double pt_veto = 0.;

	public:
		string name;
		bool loaded = false;
	        bool veto = false;

		vector<int> i_jet1;
		vector<int> i_jet2;
		double weight;

		vector<double> pt, eta, rap, phi, corr, unc;
	        vector<double> pt_H, eta_H, rap_H, phi_H, corr_H, unc_H;
        	vector<double> pt_L, eta_L, rap_L, phi_L, corr_L, unc_L;


		Object(string , double , double , double);
		void LoadEvent(Event *);
		void LoadMN(Event *);
		void LoadINCL(Event *);
		void Print();
		void Clear();
};
#endif	/* _OBJECT_H */
