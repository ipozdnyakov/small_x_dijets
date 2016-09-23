#include<iostream>
#include"finder.h"
using namespace std;
#define pi 3.1415926

//////////////////
//FIND MN INDEX
vector<int> find_MN(vector<double> y_v_1, vector<double> y_v_2){
	vector<int> MN_index;
	MN_index.push_back(-1);
	MN_index.push_back(-1);

	int i = 0, j = 0;

	double dy = 0, dy_max = 0;

	for(i = 0; i < y_v_1.size(); i++){
		for(j = 0; j < y_v_2.size(); j++){
			dy = fabs(y_v_1[i] - y_v_2[j]);
			if(dy > dy_max){
				dy_max = dy;
				MN_index[0] = i;
				MN_index[1] = j;
			}
		}
	}
	return MN_index;
};

//////////////////
//FIND MN DY
double find_dy_MN(vector<double> y_v_1, vector<double> y_v_2){

	vector<int> MN_index = find_MN(y_v_1, y_v_2);
	double dy = fabs(y_v_1[MN_index[0]] - y_v_2[MN_index[1]]);

return dy;
}
//////////////////

//////////////////
//FIND MN DPHI
double find_dphi_MN(vector<double> y_v_1, vector<double> phi_v_1,
	              vector<double> y_v_2, vector<double> phi_v_2){

	vector<int> MN_index = find_MN(y_v_1, y_v_2);
	double dphi = fabs(phi_v_1[MN_index[0]] - phi_v_2[MN_index[1]]);                     
	if(dphi > pi){
               dphi = (2*pi - dphi);
        };

return dphi;
}
//////////////////



//////////////////
//FIND CLOSEST JET
int find_closest(double phi_v, double y_v, vector<double> phi_v_m, vector<double> y_v_m, double *dr, int except){
if( (y_v_m.size() != phi_v_m.size()) || (except > (int) phi_v_m.size()) ){
	cout << except << " beyond vector size " << (int) phi_v_m.size() << " :Error in <find_closest()> \n";
	return -1;
}

int 		i = 0,
		j = 0;
double	dr_i = 0.;
	
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
/////////////////

/////////////////////////
//FIND MAX DY IN A VECTOR
double find_dy(vector<double> y_v){
	double dy = 0;
	double dphi = 0;
	int i = 0, j = 0;
	i = find_i_min(y_v);
	j = find_i_max(y_v);        
	dy = fabs(y_v[j] - y_v[i]);	
	return dy;
};
/////////////////////////


////////////////////////////////
//FIND DPHI of dijet with max DY
double find_dphi(vector<double> y_v, vector<double> phi_v){
if(y_v.size() != phi_v.size()){
	cout << "Error in <find_dphi()> \n";
	return -100.;
}
	double dphi = 0;
	int i = 0, j = 0;
	i = find_i_min(y_v);
	j = find_i_max(y_v);
        
                      dphi = fabs(phi_v[j] - phi_v[i]);
                      if(dphi > pi){
                             dphi = (2*pi - dphi);
                      };
	return dphi;
};
////////////////////////////////

////////////////////////////////
//FIND INDEX ofjet with min Y
int find_i_min(vector<double> y_v){
int i = 0, j = 0;
double y_min = 10;
	for( j = 0; j < y_v.size(); j++){
		if(y_v[j] < y_min){
			y_min = y_v[j];
			i = j;
		}
	}
	return i;
};
////////////////////////////////


////////////////////////////////
//FIND INDEX of jet with max Y
int find_i_max(vector<double> y_v){
int i = 0, j = 0;
double y_max = -10;
	for( j = 0; j < y_v.size(); j++){
		if(y_v[j] > y_max){
			y_max = y_v[j];
			i = j;
		}
	}
	return i;
};
////////////////////////////////
