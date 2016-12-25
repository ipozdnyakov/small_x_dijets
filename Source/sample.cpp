#include<fstream>
#include<iostream>
#include"sample.h"

using namespace std;


Sample::Sample(TString str){
	this->name = str;
};

bool Sample::CheckEvent(Event *event){

if(event->nPV != 1) return false;

	if (name == "central_trg"){
		if(event->CNTR == 1){
			return true;
		}else{
			return false;
		}
	}else if (name == "forward2_trg"){
		if(event->FWD2 == 1){
			return true;
		}else{
			return false;
		}
	}else if (name == "forward3_trg"){
		if(event->FWD3 == 1){
			return true;
		}else{
			return false;
		}
	}else if (name == "unbiased"){
		if(event->MB == 1){
			return true;
		}else{
			return false;
		}
	}else{
		cout << "Conditions for sample " << this->name << " not found\n";
		return false;
	}
};
