#include"finder.h"
#include"TLegend.h"
using namespace std;
#define pi 3.1415926

Int_t find_closest(Double_t phi_v, Double_t y_v, vector<Double_t> phi_v_m, vector<Double_t> y_v_m, Double_t *dr, Int_t except){
if( (y_v_m.size() != phi_v_m.size()) || (except > (Int_t) phi_v_m.size()) ){
	cout << except << " beyond vector size " << (Int_t) phi_v_m.size() << " :Error in <find_closest()> \n";
	return -1;
}

Int_t 		i = 0,
		j = 0;
Double_t	dr_i = 0.;
	
	(*dr) = 100.;
	for( i = 0; i < phi_v_m.size(); i++){
		dr_i = sqrt(pow(phi_v - phi_v_m[i],2.) + pow(y_v - y_v_m[i],2.));
		if((dr_i < (*dr))&&(i != except)){
			(*dr) = dr_i;
			j = i;	
		}
	}

	return j;
};

Double_t find_dy(vector<Double_t> y_v){

	Double_t dy = 0;
	Double_t dphi = 0;
	Int_t i = 0, j = 0;
	i = find_i_min(y_v);
	j = find_i_max(y_v);
        
	              dy = fabs(y_v[j] - y_v[i]);
	
	return dy;
};

Double_t find_dphi(vector<Double_t> y_v, vector<Double_t> phi_v){
if(y_v.size() != phi_v.size()){
	cout << "Error in <find_dphi()> \n";
	return -100.;
}
	Double_t dphi = 0;
	Int_t i = 0, j = 0;
	i = find_i_min(y_v);
	j = find_i_max(y_v);
        
                      dphi = fabs(phi_v[j] - phi_v[i]);
                      if(dphi > pi){
                             dphi = (2*pi - dphi);
                      };
	
	return dphi;

};

Int_t find_i_min(vector<Double_t> y_v){
Int_t i = 0, j = 0;
Double_t y_min = 10;
	for( j = 0; j < y_v.size(); j++){
		if(y_v[j] < y_min){
			y_min = y_v[j];
			i = j;
		}
	}

	return i;
};

Int_t find_i_max(vector<Double_t> y_v){
Int_t i = 0, j = 0;
Double_t y_max = -10;
	for( j = 0; j < y_v.size(); j++){
		if(y_v[j] > y_max){
			y_max = y_v[j];
			i = j;
		}
	}

	return i;
};


