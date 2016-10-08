#include<iostream>
#include"finder.h"
#include"object.h"

using namespace std;

Object::Object(string name, double pt_min_1, double pt_min_2, double pt_veto):name(name){

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

	//JEC PLUS
                if((event->pt[i]*(1+event->pt_unc[i]) > this->pt_min_H) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_H_jecunc_plus.push_back(event->pt[i]*(1+event->pt_unc[i]));
                  this->eta_H_jecunc_plus.push_back(event->eta[i]);
                  this->rap_H_jecunc_plus.push_back(event->rap[i]);
                  this->phi_H_jecunc_plus.push_back(event->phi[i]);
                }
                if((event->pt[i]*(1+event->pt_unc[i]) > this->pt_min_L) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_L_jecunc_plus.push_back(event->pt[i]*(1+event->pt_unc[i]));
                  this->eta_L_jecunc_plus.push_back(event->eta[i]);
                  this->rap_L_jecunc_plus.push_back(event->rap[i]);
                  this->phi_L_jecunc_plus.push_back(event->phi[i]);
                }
                if((event->pt[i]*(1+event->pt_unc[i]) < this->pt_min_L)&&(event->pt[i]*(1+event->pt_unc[i]) > this->pt_veto)) this->veto_jecunc_plus = true;

	//JEC MINUS
                if((event->pt[i]*(1-event->pt_unc[i]) > this->pt_min_H) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_H_jecunc_minus.push_back(event->pt[i]*(1-event->pt_unc[i]));
                  this->eta_H_jecunc_minus.push_back(event->eta[i]);
                  this->rap_H_jecunc_minus.push_back(event->rap[i]);
                  this->phi_H_jecunc_minus.push_back(event->phi[i]);
                }
                if((event->pt[i]*(1-event->pt_unc[i]) > this->pt_min_L) && (fabs(event->rap[i]) < 4.7)){
                  this->pt_L_jecunc_minus.push_back(event->pt[i]*(1-event->pt_unc[i]));
                  this->eta_L_jecunc_minus.push_back(event->eta[i]);
                  this->rap_L_jecunc_minus.push_back(event->rap[i]);
                  this->phi_L_jecunc_minus.push_back(event->phi[i]);
                }
                if((event->pt[i]*(1-event->pt_unc[i]) < this->pt_min_L)&&(event->pt[i]*(1-event->pt_unc[i]) > this->pt_veto)) this->veto_jecunc_minus = true;

        }
	
	if(this->name == "MN") this->LoadMN(event);
	if(this->name == "INCL") this->LoadINCL(event);

	this->weight = event->weight;
	this->loaded = true;

};

void Object::LoadMN(Event *event){

	vector<int> MN_index = find_MN(this->rap_H, this->rap_L);

	if((MN_index[0] != -1)&&(MN_index[1] != -1)){
		this->pt.push_back(this->pt_H[MN_index[0]]);
		this->eta.push_back(this->eta_H[MN_index[0]]);
		this->rap.push_back(this->rap_H[MN_index[0]]);
		this->phi.push_back(this->phi_H[MN_index[0]]);
		this->corr.push_back(this->corr_H[MN_index[0]]);
		this->unc.push_back(this->unc_H[MN_index[0]]);
		this->i_jet1.push_back(0);

		this->pt.push_back(this->pt_L[MN_index[1]]);
		this->eta.push_back(this->eta_L[MN_index[1]]);
		this->rap.push_back(this->rap_L[MN_index[1]]);
		this->phi.push_back(this->phi_L[MN_index[1]]);
		this->corr.push_back(this->corr_L[MN_index[1]]);
		this->unc.push_back(this->unc_L[MN_index[1]]);
		this->i_jet1.push_back(1);
	}
}

void Object::LoadINCL(Event *event){
	
}

void Object::Clear(){

	this->pt.clear();
	this->eta.clear();
	this->rap.clear();
	this->phi.clear();
	this->corr.clear();
	this->unc.clear();
	this->i_jet1.clear();
	this->i_jet2.clear();


	this->pt_H.clear();
	this->eta_H.clear();
	this->rap_H.clear();
	this->phi_H.clear();
	this->corr_H.clear();
	this->unc_H.clear();

	this->pt_H_jecunc_plus.clear();
	this->eta_H_jecunc_plus.clear();
	this->rap_H_jecunc_plus.clear();
	this->phi_H_jecunc_plus.clear();
	this->pt_H_jecunc_minus.clear();
	this->eta_H_jecunc_minus.clear();
	this->rap_H_jecunc_minus.clear();
	this->phi_H_jecunc_minus.clear();


	this->pt_L.clear();
	this->eta_L.clear();
	this->rap_L.clear();
	this->phi_L.clear();
	this->corr_L.clear();
	this->unc_L.clear();

	this->pt_L_jecunc_plus.clear();
	this->eta_L_jecunc_plus.clear();
	this->rap_L_jecunc_plus.clear();
	this->phi_L_jecunc_plus.clear();
	this->pt_L_jecunc_minus.clear();
	this->eta_L_jecunc_minus.clear();
	this->rap_L_jecunc_minus.clear();
	this->phi_L_jecunc_minus.clear();


	this->veto = false;
	this->veto_jecunc_plus = false;
	this->veto_jecunc_minus = false;

	this->loaded = false;

};
