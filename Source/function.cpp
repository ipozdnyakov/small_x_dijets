#include<iostream>
#include"function.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Function::Function(TString name, const double *b, int n):name(name),bins(b),n_bins(n){
};

void Function::CalculateValues(Object *object){

	if(!object->loaded) cout << "Function Error: event not loaded to the object yet, but values already requested!!!\n";

	if(this->name == "pt"){
		this->values = object->pt;
		this->SetPlainWeights(object);
	}

	if(this->name == "cor"){
		this->values = object->corr;
		this->SetPlainWeights(object);
	}

	if(this->name == "unc"){
		this->values = object->unc;
		this->SetPlainWeights(object);
	}

	if(this->name == "eta"){
		this->values = object->eta;
		this->SetPlainWeights(object);
	}

	if(this->name == "rap"){
		this->values = object->rap;
		this->SetPlainWeights(object);
	}

	if(this->name == "phi"){
		this->values = object->phi;
		this->SetPlainWeights(object);
	}

	if(this->name == "dphi0_9.4"){
		this->SetDphiInDrap(0., 9.4, object);
		this->SetPlainWeights(object);
	}

	if(this->name == "dphi0_3"){
		this->SetDphiInDrap(0., 3.0, object);
		this->SetPlainWeights(object);
	}

	if(this->name == "dphi3_6"){
		this->SetDphiInDrap(3.0, 6.0, object);
		this->SetPlainWeights(object);
	}

	if(this->name == "dphi6_9.4"){
		this->SetDphiInDrap(6.0, 9.4, object);
		this->SetPlainWeights(object);
	}

	if(this->name == "drap"){
		this->SetDrapInDphi(0., pi, object);
		this->SetPlainWeights(object);
	}

	if(this->name == "cos_1(dy)"){
		this->SetCosNPowerMvsDrap(1., 1., object);
	}

	if(this->name == "cos_2(dy)"){
		this->SetCosNPowerMvsDrap(2., 1., object);
	}

	if(this->name == "cos_3(dy)"){
		this->SetCosNPowerMvsDrap(3., 1., object);
	}

	if(this->name == "cos2_1(dy)"){
		this->SetCosNPowerMvsDrap(1., 2., object);
	}

	if(this->name == "cos2_2(dy)"){
		this->SetCosNPowerMvsDrap(2., 2., object);
	}

	if(this->name == "cos2_3(dy)"){
		this->SetCosNPowerMvsDrap(3., 2., object);
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
//        cout << "\nPrint function:\n values: ";
        for(int i = 0; i < this->values.size(); i++){
                cout << this->values[i] << "\t";
        }
//	cout << "\n weights: ";
        for(int i = 0; i < this->weights.size(); i++){
//                cout << this->weights[i] << "\t";
        }
	cout << "\n";
};
