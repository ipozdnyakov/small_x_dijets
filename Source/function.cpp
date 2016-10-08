#include<iostream>
#include"function.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Function::Function(TString name):name(name){
};

void Function::GetMyValues(Object *object, string name){
	this->values.push_back(1.);
};
