#include<iostream>
#include"object.h"

using namespace std;

Object::Object(double pt_min_1, double pt_min_2, double pt_veto){

	if(pt_min_1 > pt_min_2){
		this->pt_min_1 = pt_min_1;
		this->pt_min_2 = pt_min_2;
	}else{
		this->pt_min_1 = pt_min_2;
		this->pt_min_2 = pt_min_1;
	}

	if(pt_veto > this->pt_min_2) cout << "Error pt_veto > pt_cut !!!\n";

	this->pt_veto = pt_veto;

        TString Pt_min = "_pt";
                               	Pt_min += this->pt_min_1;
                                Pt_min += "_";
                                Pt_min += this->pt_min_2;
        TString Pt_veto = "_veto";
                                Pt_veto += this->pt_veto;

        this->specification = Pt_min + Pt_veto;

};

void Object::ReadEvent(Event *event){

};
