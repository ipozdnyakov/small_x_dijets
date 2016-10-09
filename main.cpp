#include<iostream>
#include"measurement.h"
#include"function.h"
#include"object.h"
#include"sample.h"
#include"bining.h"

using namespace std;

int main(int argc, char** argv) {

//DECLARATION OF OBJECTS	
	Object	 *incl = new Object("INCL", 35., 35., 35.);
	Object	 *mn = new Object("MN", 35., 35., 35.);
	Object	 *excl = new Object("EXCL", 35., 35., 35.);

//DECLARATION OF SAMPLES
	Sample *data = new Sample("FSQJets_2015_2016");

//DECLARATION OF FUNCTIONS
	Function *pt = new Function("pt", pt_bins, n_pt_bins);
	Function *eta = new Function("eta", eta_towers, n_eta_towers);
	Function *rap = new Function("rap", eta_towers, n_eta_towers);
	Function *phi = new Function("phi", phi_towers, n_phi_towers);
	Function *dphi0 = new Function("dphi0_9.4", dphi_bins, n_dphi_bins);
	Function *dphi1 = new Function("dphi0_3", dphi_bins, n_dphi_bins);
	Function *dphi2 = new Function("dphi3_6", dphi_bins, n_dphi_bins);
	Function *dphi3 = new Function("dphi6_9.4", dphi_bins, n_dphi_bins);

//CONFIGURE AND PERFORM MEASUREMENTS
	Measurement *distr = new Measurement("basic_distributions","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV");
	distr->IncludeObject(incl);
	distr->IncludeFunction(pt);
	distr->IncludeFunction(eta);
	distr->IncludeFunction(rap);
	distr->IncludeFunction(phi);
	cout << distr->specification << "\t" << distr->n_events << "\n";
	data->ReadSample(distr);
	cout << distr->specification << "\t" << distr->n_events << "\n";
	distr->AverageAndNormalize();
	distr->WriteToFile("./results_distrib");

	Measurement *decorr = new Measurement("decorrelations","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV");
	decorr->IncludeObject(mn);
	decorr->IncludeFunction(dphi0);
	decorr->IncludeFunction(dphi1);
	decorr->IncludeFunction(dphi2);
	decorr->IncludeFunction(dphi3);
	cout << decorr->specification << "\t" << decorr->n_events << "\n";
	data->ReadSample(decorr);
	cout << decorr->specification << "\t" << decorr->n_events << "\n";
	distr->AverageAndNormalize();
	distr->WriteToFile("./results_decorr");

	return (EXIT_SUCCESS);
}
