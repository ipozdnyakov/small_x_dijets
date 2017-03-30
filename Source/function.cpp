#include<iostream>
#include<iomanip>
#include"bining.h"
#include"finder.h"
#include"function.h"

using namespace std;
#define pi 3.1415926

Function::Function(TString name, const double *b, int n):name(name),bins(b),n_bins(n){
};

void Function::CalculateValues(Object *object){

	if(!object->loaded) cout << "Function Error: event not loaded to the object yet, but values already requested!!!\n";

	if(this->name == "npv_distrib"){
		this->values.push_back(object->event->nPV);
		this->SetPlainWeights(object);
	}else if(this->name == "pt"){
		this->values = object->pt;
		this->SetPlainWeights(object);
	}else if(this->name == "pt_lead"){
        	int i = find_Nth_value_index(object->pt_L, 1);
		double pt = object->pt_L[i];
		if(pt > 0.) this->values.push_back(pt);
		this->SetPlainWeights(object);
	}else if(this->name == "pt_sublead"){
        	int i = find_Nth_value_index(object->pt_L, 2);
		double pt = object->pt_L[i];
		if(pt > 0.) this->values.push_back(pt);
		this->SetPlainWeights(object);
	}else if(this->name == "pt_sublead_fwd3"){
        	int i = find_Nth_value_index(object->pt_L, 2);
		double pt = object->pt_L[i];
		double eta = object->eta_L[i];
		if((pt > 0.)&&(fabs(eta) > 3.)) this->values.push_back(pt);
		this->SetPlainWeights(object);
	}else if(this->name == "pt_sublead_fwd1d3"){
        	int i = find_Nth_value_index(object->pt_L, 2);
		double pt = object->pt_L[i];
		double eta = object->eta_L[i];
		if((pt > 0.)&&(fabs(eta) < 1.3)) this->values.push_back(pt);
		this->SetPlainWeights(object);
	}else if(this->name == "cor"){
		this->values = object->corr;
		this->SetPlainWeights(object);
	}else if(this->name == "unc"){
		this->values = object->unc;
		this->SetPlainWeights(object);
	}else if(this->name == "eta"){
		this->values = object->eta;
		this->SetPlainWeights(object);
	}else if(this->name == "rap"){
		this->values = object->rap;
		this->SetPlainWeights(object);
	}else if(this->name == "phi"){
		this->values = object->phi;
		this->SetPlainWeights(object);
	}else if(this->name == "dphi0_9.4"){
		this->SetDphiInDrap(0., 9.4, object);
		this->SetPlainWeights(object);
	}else if(this->name == "dphi0_3"){
		this->SetDphiInDrap(0., 3.0, object);
		this->SetPlainWeights(object);
	}else if(this->name == "dphi3_6"){
		this->SetDphiInDrap(3.0, 6.0, object);
		this->SetPlainWeights(object);
	}else if(this->name == "dphi6_9.4"){
		this->SetDphiInDrap(6.0, 9.4, object);
		this->SetPlainWeights(object);
	}else if(this->name == "drap"){
		this->SetDrapInDphi(0., pi, object);
		this->SetPlainWeights(object);
	}else if(this->name == "cos_1(dy)"){
		this->SetCosNPowerMvsDrap(1., 1., object);
	}else if(this->name == "cos_2(dy)"){
		this->SetCosNPowerMvsDrap(2., 1., object);
	}else if(this->name == "cos_3(dy)"){
		this->SetCosNPowerMvsDrap(3., 1., object);
	}else if(this->name == "cos2_1(dy)"){
		this->SetCosNPowerMvsDrap(1., 2., object);
	}else if(this->name == "cos2_2(dy)"){
		this->SetCosNPowerMvsDrap(2., 2., object);
	}else if(this->name == "cos2_3(dy)"){
		this->SetCosNPowerMvsDrap(3., 2., object);
	}else if(this->name == "cos_21(dy)"){
		this->SetCosNMvsDrap(2., 1., object);
	}else if(this->name == "cos_32(dy)"){
		this->SetCosNMvsDrap(3., 2., object);
	}else{
              	cout << "Function Error: Case for function " << this->name << " not found\n";
	}

};

void Function::Clear(){
	this->values.clear();
	this->weights.clear();
};

void Function::SetPlainWeights(Object* object){
	for(int i = 0; i < values.size(); i++){
		this->weights.push_back(object->weight);
	}
};

void Function::SetCosNMvsDrap(double n, double m, Object* object){

	double rap1 = 0., rap2 = 0., phi1 = 0, phi2 = 0;
	double drap = 0., dphi = 0.;
	if(object->i_jet1.size() != object->i_jet2.size()){
		cout << "Object Error: two index vectors of dijets components (jets) have different lenght!!!\n";
	}
	for(int i = 0; i < object->i_jet1.size(); i++){
		rap1 = object->rap[object->i_jet1[i]];
		rap2 = object->rap[object->i_jet2[i]];
		phi1 = object->phi[object->i_jet1[i]];
		phi2 = object->phi[object->i_jet2[i]];
	
		drap = fabs(rap1 - rap2);

        	dphi = fabs(phi1 - phi2);
	        if(dphi > pi) dphi = (2*pi - dphi);

		this->values.push_back(drap);
		this->weights.push_back((object->weight)*cos(n*(pi - dphi))*cos(m*(pi - dphi)));
	}

};

void Function::SetCosNPowerMvsDrap(double n, double m, Object* object){

	double rap1 = 0., rap2 = 0., phi1 = 0, phi2 = 0;
	double drap = 0., dphi = 0.;
	if(object->i_jet1.size() != object->i_jet2.size()){
		cout << "Object Error: two index vectors of dijets components (jets) have different lenght!!!\n";
	}
	for(int i = 0; i < object->i_jet1.size(); i++){
		rap1 = object->rap[object->i_jet1[i]];
		rap2 = object->rap[object->i_jet2[i]];
		phi1 = object->phi[object->i_jet1[i]];
		phi2 = object->phi[object->i_jet2[i]];
	
		drap = fabs(rap1 - rap2);

        	dphi = fabs(phi1 - phi2);
	        if(dphi > pi) dphi = (2*pi - dphi);

		this->values.push_back(drap);
		this->weights.push_back((object->weight)*pow(cos(n*(pi - dphi)),m));
	}

};

void Function::SetDphiInDrap(double drap_min, double drap_max, Object *object){

	double rap1 = 0., rap2 = 0., phi1 = 0, phi2 = 0;
	double drap = 0., dphi = 0.;
	if(object->i_jet1.size() != object->i_jet2.size()){
		cout << "Object Error: two index vectors of dijets components (jets) have different lenght!!!\n";
	}
	for(int i = 0; i < object->i_jet1.size(); i++){
		rap1 = object->rap[object->i_jet1[i]];
		rap2 = object->rap[object->i_jet2[i]];
		phi1 = object->phi[object->i_jet1[i]];
		phi2 = object->phi[object->i_jet2[i]];
	
		drap = fabs(rap1 - rap2);

        	dphi = fabs(phi1 - phi2);
	        if(dphi > pi) dphi = (2*pi - dphi);

		if((drap > drap_min)&&(drap < drap_max)){
			this->values.push_back(dphi);
		}
	}
};

void Function::SetDrapInDphi(double dphi_min, double dphi_max, Object *object){

	double rap1 = 0., rap2 = 0., phi1 = 0, phi2 = 0;
	double drap = 0., dphi = 0.;
	if(object->i_jet1.size() != object->i_jet2.size()){
		cout << "Object Error: two index vectors of dijets components (jets) have different lenght!!!\n";
	}
	for(int i = 0; i < object->i_jet1.size(); i++){
		rap1 = object->rap[object->i_jet1[i]];
		rap2 = object->rap[object->i_jet2[i]];
		phi1 = object->phi[object->i_jet1[i]];
		phi2 = object->phi[object->i_jet2[i]];
	
		drap = fabs(rap1 - rap2);

        	dphi = fabs(phi1 - phi2);
	        if(dphi > pi) dphi = (2*pi - dphi);

		if((dphi > dphi_min)&&(dphi < dphi_max)){
			this->values.push_back(drap);
		}
	}
};

void Function::Print(){
        cout << " Print function "<< this->name << ":\n values: ";
        for(int i = 0; i < this->values.size(); i++){
                cout << setw(10) << this->values[i] << " ";
        }
	cout << "\n weights: ";
        for(int i = 0; i < this->weights.size(); i++){
                cout << setw(10) << this->weights[i] << " ";
        }
	cout << "\n";
};
