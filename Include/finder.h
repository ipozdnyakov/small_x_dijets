#include<vector>
#include"TROOT.h"

using namespace std;

#ifndef _FINDER_H
#define	_FINDER_H
	vector<int> find_MN(vector<Double_t> , vector<Double_t>);

	Double_t find_dy_MN(vector<Double_t> , vector<Double_t>);

	Double_t find_dphi_MN(vector<Double_t> , vector<Double_t> , vector<Double_t> , vector<Double_t>);

	Int_t find_closest(Double_t , Double_t , vector<Double_t> , vector<Double_t> , Double_t *, Int_t );

	Double_t find_dy(vector<Double_t> );

	Double_t find_dphi(vector<Double_t> , vector<Double_t> );

	Int_t find_i_min(vector<Double_t> );

	Int_t find_i_max(vector<Double_t> );

#endif	/* _FINDER_H */

