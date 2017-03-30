#include<iostream>
#include"dataset.h"
#include"bining.h"
#include"measurement.h"
#include"function.h"
#include"object.h"
#include"result.h"
#include"sample.h"

using namespace std;
bool verbose = false, print_this_event = false;

void EfficiencyCalculation();
void MergingWeightsCalculation();
void PileUpCalculation();

void BasicDistributions();
void DeltaPhiDynamics();
void DeltaYDynamics();

//DECLARATION OF DATASETS
// to add - listing should be added
// 	  - case should be added into constructor of class Dataset::Dataset() in dataset.cpp
	Dataset *data = new Dataset("13TeV_data_2015C_FSQJets3");
	Dataset *min_bias = new Dataset("13TeV_data_2015C_Min_Bias");
	Dataset *zerobias = new Dataset("13TeV_data_2015C_ZeroBias");
	Dataset *herwig_minbias = new Dataset("13TeV_mc_herwigpp_MinBias");
	Dataset *herwig_lowpthat = new Dataset("13TeV_mc_herwigpp_pt10to35");
	Dataset *herwig_lowpthat_fb = new Dataset("13TeV_mc_herwigpp_pt10to35_FB");
	Dataset *herwig_hightpthat = new Dataset("13TeV_mc_herwigpp_pt35toInf");
	Dataset *herwig_hightpthat_fb = new Dataset("13TeV_mc_herwigpp_pt35toInf_FB");

//DECLARATION OF OBJECTS
// to add - case should be added into function of class Object::LoadEvent() in object.cpp
	Object	 *empty = new Object("EMPTY", 0., 0., 0.);
	Object	 *all_incl = new Object("INCL", 0., 0., 0.);
	Object	 *all_mn = new Object("MN", 0., 0., 0.);
	Object	 *incl = new Object("INCL", 35., 35., 35.);
	Object	 *mn = new Object("MN", 35., 35., 35.);
	Object	 *excl = new Object("EXCL", 35., 35., 35.);

//DECLARATION OF FUNCTIONS
// to add - case should be added into function of class Function::CalculateValues() in function.cpp
// bining should be defined in binning.h
	Function *npv_distrib = new Function("npv_distrib", npv_bins, n_npv_bins);

	Function *pt = new Function("pt", pt_bins, n_pt_bins);
	Function *pt_lead = new Function("pt_lead", fine_pt_bins, n_fine_pt_bins);
	Function *pt_sublead = new Function("pt_sublead", fine_pt_bins, n_fine_pt_bins);
	Function *pt_sublead_fwd3 = new Function("pt_sublead_fwd3", fine_pt_bins, n_fine_pt_bins);
	Function *pt_sublead_fwd1d3 = new Function("pt_sublead_fwd1d3", fine_pt_bins, n_fine_pt_bins);
	Function *eta = new Function("eta", eta_towers, n_eta_towers);
	Function *rap = new Function("rap", eta_towers, n_eta_towers);
	Function *phi = new Function("phi", phi_towers, n_phi_towers);
	Function *cor = new Function("cor", pt_bins, n_pt_bins);
	Function *unc = new Function("unc", pt_bins, n_pt_bins);

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

//DECLARATION OF SAMPLES
// to add - case should be added into function of class Sample::CheckEvent() in sample.cpp
	Sample *plane	 		= new Sample("plane");
	Sample *unbiased 		= new Sample("unbiased");

	Sample *unbiased_central 	= new Sample("unbiased_central");
	Sample *unbiased_forward2	= new Sample("unbiased_forward2");
	Sample *unbiased_forward3	= new Sample("unbiased_forward3");
	Sample *central_trg 		= new Sample("central_trg");
	Sample *forward2_trg 		= new Sample("forward2_trg");
	Sample *forward3_trg		= new Sample("forward3_trg");

	Sample *central_pt35			= new Sample("central_pt35");
	Sample *central_no_fwd_pt35_eta2d1	= new Sample("central_no_fwd_pt35_eta2.1");
	Sample *fwd_pt35_eta2d1 		= new Sample("forward_pt35_eta2.1");
	Sample *merged_pt35_eta2d1	 	= new Sample("merged_pt35_eta2.1");
	Sample *low_pthat			= new Sample("low_pthat");
	Sample *high_pthat			= new Sample("high_pthat");

//DECLARATION OF RESULTS
// to add - case should be added into function of class Measurement::CalculateResult() in measurement.cpp
	Result *eff_pt_sublead_cntr_trg = new Result("eff_pt_sublead_cntr_trg");
	Result *eff_pt_sublead_fwd3_cntr_trg = new Result("eff_pt_sublead_fwd3_cntr_trg");
	Result *eff_pt_sublead_fwd1d3_cntr_trg = new Result("eff_pt_sublead_fwd1d3_cntr_trg");
	Result *eff_pt_sublead_forward2_trg = new Result("eff_pt_sublead_forward2_trg");
	Result *eff_pt_sublead_forward3_trg = new Result("eff_pt_sublead_forward3_trg");

	Result *forward_incl_pt35_eta2d1_weight = new Result("forward_incl_pt35_eta2.1_weight");
	Result *forward_mn_pt35_eta2d1_weight = new Result("forward_mn_pt35_eta2.1_weight");

	Result *pt_spectrum = new Result("pt_spectrum");
	Result *dphi_mn_1 = new Result("dphi_low_mn");
	Result *dphi_mn_2 = new Result("dphi_med_mn");
	Result *dphi_mn_3 = new Result("dphi_hig_mn");
	Result *cos_dphi = new Result("cos_dphi");


int main(int argc, char** argv) {

//	EfficiencyCalculation();
//	MergingWeightsCalculation();
//	PileUpCalculation();

	BasicDistributions();
//	DeltaPhiDynamics();
//	DeltaYDynamics();

	return (EXIT_SUCCESS);
};


void EfficiencyCalculation(){

	Measurement *eff = new Measurement("eff","_Min_Bias_2015C_data_13TeV_LowPU");

	eff->IncludeObject(all_incl);

	eff->IncludeFunction(pt_sublead);
	eff->IncludeFunction(pt_sublead_fwd3);
	eff->IncludeFunction(pt_sublead_fwd1d3);

	eff->IncludeSample(central_trg);
	eff->IncludeSample(forward2_trg);
	eff->IncludeSample(forward3_trg);
	eff->IncludeSample(unbiased_central);
	eff->IncludeSample(unbiased_forward2);
	eff->IncludeSample(unbiased_forward3);

	eff->ReadDataset(min_bias);

	eff->CalculateResult(eff_pt_sublead_cntr_trg);
	eff->CalculateResult(eff_pt_sublead_fwd3_cntr_trg);
	eff->CalculateResult(eff_pt_sublead_fwd1d3_cntr_trg);
	eff->CalculateResult(eff_pt_sublead_forward2_trg);
	eff->CalculateResult(eff_pt_sublead_forward3_trg);

	eff->WriteToFile("./eff", 1 /* 1 - only results, 2 - results and observables */);
};

void MergingWeightsCalculation(){

	Measurement *weight = new Measurement("weight","_FSQJets3_2015C_data_13TeV_LowPU");

	weight->IncludeObject(all_incl);
	weight->IncludeObject(all_mn);

	weight->IncludeFunction(drap);

	weight->IncludeSample(central_pt35);
	weight->IncludeSample(central_no_fwd_pt35_eta2d1);
	weight->IncludeSample(fwd_pt35_eta2d1);
	weight->IncludeSample(merged_pt35_eta2d1);

	weight->ReadDataset(data);

	weight->CalculateResult(forward_incl_pt35_eta2d1_weight);
	weight->CalculateResult(forward_mn_pt35_eta2d1_weight);

	weight->WriteToFile("./weight", 2 /* 1 - only results, 2 - results and observables */);
};

void PileUpCalculation(){

	Measurement *pu = new Measurement("pu","_FSQJets3_2015C_data_13TeV_LowPU");

	pu->IncludeObject(empty);

	pu->IncludeFunction(npv_distrib);

	pu->IncludeSample(plane);

	pu->ReadDataset(data);

	pu->WriteToFile("./pu", 2);
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

	basics->IncludeSample(merged_pt35_eta2d1);

	basics->ReadDataset(data);

	basics->CalculateResult(pt_spectrum);

	basics->WriteToFile("./basics_", 1 /* 1 - only results, 2 - results and observables */);

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

	delta_phi->IncludeSample(merged_pt35_eta2d1);

	delta_phi->ReadDataset(data);

	delta_phi->CalculateResult(dphi_mn_1);
	delta_phi->CalculateResult(dphi_mn_2);
	delta_phi->CalculateResult(dphi_mn_3);

	delta_phi->WriteToFile("./delta_phi", 1 /* 1 - only results, 2 - results and observables */);
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

	delta_y->IncludeSample(merged_pt35_eta2d1);

	delta_y->ReadDataset(data);

	delta_y->CalculateResult(cos_dphi);

	delta_y->WriteToFile("./delta_y", 1 /* 1 - only results, 2 - results and observables */);

};
