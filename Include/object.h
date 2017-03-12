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

		Event *event;

		bool loaded = false;
	        bool veto = false;

		vector<int> i_jet1;
		vector<int> i_jet2;
		double weight;

		vector<double> pt, eta, rap, phi, corr, unc;	// all jets from each dijet labeled in i_jet1 and i_jet2 
								// N/B - multi entries are possible in case of INCL object
	        vector<double> pt_H, eta_H, rap_H, phi_H, corr_H, unc_H; // all jets from event with pt > pt_min_H
        	vector<double> pt_L, eta_L, rap_L, phi_L, corr_L, unc_L; // all	jets from event	with pt	> pt_min_L


		Object(string , double , double , double);
		void LoadEvent(Event *);
		void LoadEMPTY(Event *);
		void LoadMN(Event *);
		void LoadINCL(Event *);
		void Print();
		void Clear();
};
#endif	/* _OBJECT_H */
