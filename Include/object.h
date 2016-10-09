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
		vector<double> pt;
		vector<double> eta;
		vector<double> rap;
		vector<double> phi;
		vector<double> corr;
		vector<double> unc;

		vector<int> i_jet1;
		vector<int> i_jet2;
		double weight;

	        vector<double> pt_H, eta_H, rap_H, phi_H, corr_H, unc_H;
	        vector<double> pt_H_jecunc_plus, eta_H_jecunc_plus, rap_H_jecunc_plus, phi_H_jecunc_plus;
	        vector<double> pt_H_jecunc_minus, eta_H_jecunc_minus, rap_H_jecunc_minus, phi_H_jecunc_minus;

        	vector<double> pt_L, eta_L, rap_L, phi_L, corr_L, unc_L;
        	vector<double> pt_L_jecunc_plus, eta_L_jecunc_plus, rap_L_jecunc_plus, phi_L_jecunc_plus;
        	vector<double> pt_L_jecunc_minus, eta_L_jecunc_minus, rap_L_jecunc_minus, phi_L_jecunc_minus;

	        Bool_t veto = false;
	        Bool_t veto_jecunc_plus = false;
	        Bool_t veto_jecunc_minus = false;

		Object(string , double , double , double);
		void LoadEvent(Event *);
		void LoadMN(Event *);
		void LoadINCL(Event *);
		void Print();
		void Clear();
};
#endif	/* _OBJECT_H */
