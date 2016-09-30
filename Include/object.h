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
		bool loaded = false;

	public:

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

/*		vector<double> pt;
		vector<double> eta;
		vector<double> rap;
		vector<double> phi;

		vector<double> dphi;
		vector<double> dy;
*/	
		Object(double , double , double);
		void LoadEvent(Event *);
		void Clear();
		vector<vector<double>> GetJetsData(string);
		vector<double> GetCorr();
		vector<double> GetUnc();
};
#endif	/* _OBJECT_H */
