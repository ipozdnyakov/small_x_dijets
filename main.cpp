#include<iostream>
#include"measurement.h"
#include"function.h"
//#include"trigger.h"
#include"object.h"
#include"result.h"
#include"dataset.h"
#include"bining.h"

using namespace std;

void EfficiencyCalculation();

void BasicDistributions();
void DeltaPhiDynamics();
void DeltaYDynamics();

//DECLARATION OF DATASETSS
// to add - listing should be added
// 	  - case should be added into constructor of class Dataset::Dataset() in dataset.cpp
	Dataset *data = new Dataset("13TeV_data_2015C_FSQJets3");
	Dataset *min_bias = new Dataset("13TeV_data_2015C_MinBias");
	Dataset *zerobias = new Dataset("13TeV_data_2015C_ZeroBias");
//DECLARATION OF OBJECTS
// to add - case should be added into function of class Object::LoadEvent() in object.cpp
	Object	 *incl = new Object("INCL", 35., 35., 35.);
	Object	 *mn = new Object("MN", 35., 35., 35.);
	Object	 *excl = new Object("EXCL", 35., 35., 35.);
//DECLARATION OF FUNCTIONS
// to add - case should be added into function of class Function::CalculateValues() in function.cpp
	Function *pt = new Function("pt", pt_bins, n_pt_bins);
	Function *cor = new Function("cor", pt_bins, n_pt_bins);
	Function *unc = new Function("unc", pt_bins, n_pt_bins);
	Function *eta = new Function("eta", eta_towers, n_eta_towers);
	Function *rap = new Function("rap", eta_towers, n_eta_towers);
	Function *phi = new Function("phi", phi_towers, n_phi_towers);
	Function *dphi0 = new Function("dphi0_9.4", fine_dphi_bins, n_fine_dphi_bins);
	Function *dphi1 = new Function("dphi0_3", dphi_bins, n_dphi_bins);
	Function *dphi2 = new Function("dphi3_6", dphi_bins, n_dphi_bins);
	Function *dphi3 = new Function("dphi6_9.4", dphi_bins, n_dphi_bins);
	Function *drap = new Function("drap", drap_bins, n_drap_bins);
	Function *cos_1 = new Function("cos_1(dy)", drap_bins, n_drap_bins);
	Function *cos_2 = new Function("cos_2(dy)", drap_bins, n_drap_bins);
	Function *cos_3 = new Function("cos_3(dy)", drap_bins, n_drap_bins);
	Function *cos2_1 = new Function("cos2_1(dy)", drap_bins, n_drap_bins);
	Function *cos2_2 = new Function("cos2_2(dy)", drap_bins, n_drap_bins);
	Function *cos2_3 = new Function("cos2_3(dy)", drap_bins, n_drap_bins);
	Function *cos_21 = new Function("cos_21(dy)", drap_bins, n_drap_bins);
	Function *cos_32 = new Function("cos_32(dy)", drap_bins, n_drap_bins);
//DECLARATION OF TRIGGERS
// to add - ???
	//Trigger *central = new Trigger("central");
//DECLARATION OF RESULTS
// to add - ???
	Result *dphi_mn_1 = new Result("dphi_low_mn");
	Result *dphi_mn_2 = new Result("dphi_med_mn");
	Result *dphi_mn_3 = new Result("dphi_hig_mn");


int main(int argc, char** argv) {

	EfficiencyCalculation();

	BasicDistributions();
	DeltaPhiDynamics();
	DeltaYDynamics();

	return (EXIT_SUCCESS);
};


void EfficiencyCalculation(){

	Measurement *eff = new Measurement("eff","_Min_Bias_2015C_data_13TeV_LowPU");

	eff->IncludeFunction(pt);
	eff->IncludeObject(incl);

};

void BasicDistributions(){

	Measurement *basics = new Measurement("basics","_FSQJets3_2015C_data_13TeV_LowPU");

	basics->IncludeFunction(pt);
	basics->IncludeFunction(cor);
	basics->IncludeFunction(unc);
	basics->IncludeFunction(eta);
	basics->IncludeFunction(rap);
	basics->IncludeFunction(phi);

	basics->IncludeObject(incl);

};

void DeltaPhiDynamics(){

	Measurement *delta_phi = new Measurement("delta_phi","_FSQJets3_2015C_data_13TeV_LowPU");

	delta_phi->IncludeFunction(dphi0);
	delta_phi->IncludeFunction(dphi1);
	delta_phi->IncludeFunction(dphi2);
	delta_phi->IncludeFunction(dphi3);

	delta_phi->IncludeObject(incl);
	delta_phi->IncludeObject(mn);
	delta_phi->IncludeObject(excl);

	delta_phi->IncludeResult(dphi_mn_1);
	delta_phi->IncludeResult(dphi_mn_2);
	delta_phi->IncludeResult(dphi_mn_3);

	delta_phi->ReadDataset(data);

	delta_phi->CalculateResults();
	delta_phi->WriteToFile("./delta_phi");
};

void DeltaYDynamics(){

	Measurement *delta_y = new Measurement("delta_y","_FSQJets3_2015C_data_13TeV_LowPU");

	delta_y->IncludeFunction(drap);
	delta_y->IncludeFunction(cos_1);
	delta_y->IncludeFunction(cos_2);
	delta_y->IncludeFunction(cos_3);
	delta_y->IncludeFunction(cos2_1);
	delta_y->IncludeFunction(cos2_2);
	delta_y->IncludeFunction(cos2_3);

	delta_y->IncludeObject(incl);
	delta_y->IncludeObject(mn);
	delta_y->IncludeObject(excl);

	delta_y->ReadDataset(data);

	delta_y->CalculateResults();

	delta_y->WriteToFile("./delta_y");

};

