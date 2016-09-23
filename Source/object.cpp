#include<iostream>
#include"object.h"

using namespace std;

Object::Object(double pt_min_1, double pt_min_2, double pt_veto){

	if(pt_min_1 > pt_min_2){
		this->pt_min_H = pt_min_1;
		this->pt_min_L = pt_min_2;
	}else{
		this->pt_min_H = pt_min_2;
		this->pt_min_L = pt_min_1;
	}

	if(pt_veto > this->pt_min_L) cout << "Error pt_veto > pt_cut !!!\n";

	this->pt_veto = pt_veto;

        TString Pt_min = "_pt";
                               	Pt_min += this->pt_min_H;
                                Pt_min += "_";
                                Pt_min += this->pt_min_L;
        TString Pt_veto = "_veto";
                                Pt_veto += this->pt_veto;

        this->specification = Pt_min + Pt_veto;

};

void Object::LoadEvent(Event *event){

	if(this->loaded){
		cout << "PROCESSING ERROR: Event already loaded to the Object but not readed and those Object not cleared";
		return;
	}

        for(int i = 0; i < event->pt.size(); i++){

                if((event->pt[i] > this->pt_min_H) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_H.push_back(event->pt[i]);
                  this->eta_H.push_back(event->eta[i]);
                  this->rap_H.push_back(event->rap[i]);
                  this->phi_H.push_back(event->phi[i]);
                  this->corr_H.push_back(event->pt_cor[i]);
                  this->unc_H.push_back(event->pt_unc[i]);
                }
                if((event->pt[i] > this->pt_min_L) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_L.push_back(event->pt[i]);
                  this->eta_L.push_back(event->eta[i]);
                  this->rap_L.push_back(event->rap[i]);
                  this->phi_L.push_back(event->phi[i]);
                  this->corr_L.push_back(event->pt_cor[i]);
                  this->unc_L.push_back(event->pt_unc[i]);
                }
                if((event->pt[i] < this->pt_min_L)&&(event->pt[i] > this->pt_veto)) this->veto = true;

        }
	
	this->weight = event->weight;
	this->loaded = true;

};

void Object::Clear(){

	this->pt_H.clear();
	this->eta_H.clear();
	this->rap_H.clear();
	this->phi_H.clear();
	this->corr_H.clear();
	this->unc_H.clear();

	this->pt_L.clear();
	this->eta_L.clear();
	this->rap_L.clear();
	this->phi_L.clear();
	this->corr_L.clear();
	this->unc_L.clear();

	this->veto = false;

	this->loaded = false;

};

vector<vector<double>> Object::GetJetsData(string data_name){

	vector<vector<double>> jets;

	jets.push_back(this->corr_L);
	jets.push_back(this->unc_L);

	if(data_name == "pt"){
		jets.push_back(this->pt_L);
	}
	else if(data_name == "eta"){
		jets.push_back(this->eta_L);
	}
	else if(data_name == "rap"){
		jets.push_back(this->rap_L);
	}
	else if(data_name == "phi"){
		jets.push_back(this->phi_L);
	}
	else{
		cout << "PROCESSING ERROR: There are no jets data in the Object for name " << data_name << "\n";
		jets.clear();
	}

	return jets;

};

vector<double> Object::GetCorr(){
	return this->corr_L;
};

vector<double> Object::GetUnc(){
	return this->unc_L;
};
