#include<iostream>
#include"measurement.h"
#include"function.h"
#include"object.h"
#include"sample.h"
#include"bining.h"

using namespace std;

int main(int argc, char** argv) {

//DECLARATION OF SAMPLES
//	Sample *data = new Sample("FSQJets_2015_2016");
//	Sample *data = new Sample("datasets/FSQJets3_2015C_VdMaugust");
	Sample *data = new Sample("datasets/7TeV_JetMETTau_Centr");
//DECLARATION OF MEASUREMENTS
	//Measurement *dijets = new Measurement("dijets","_FSQJets_2015_2016_data_13TeV_LowPU");
	Measurement *dijets = new Measurement("dijets","_FSQJets_2010_data_7TeV_LowPU");
//DECLARATION OF FUNCTIONS
	Function *pt = new Function("pt", pt_bins, n_pt_bins);
	Function *eta = new Function("eta", eta_towers, n_eta_towers);
	Function *rap = new Function("rap", eta_towers, n_eta_towers);
	Function *phi = new Function("phi", phi_towers, n_phi_towers);
	Function *dphi0 = new Function("dphi0_9.4", fine_dphi_bins, n_fine_dphi_bins);
	Function *dphi1 = new Function("dphi0_3", dphi_bins, n_dphi_bins);
	Function *dphi2 = new Function("dphi3_6", dphi_bins, n_dphi_bins);
	Function *dphi3 = new Function("dphi6_9.4", dphi_bins, n_dphi_bins);
	Function *drap = new Function("drap", drap_bins, n_drap_bins);
	Function *cos_1 = new Function("cos_1(dy)", drap_bins, n_drap_bins);
//DECLARATION OF OBJECTS	
	Object	 *incl = new Object("INCL", 35., 35., 35.);
	Object	 *mn = new Object("MN", 35., 35., 35.);
	Object	 *excl = new Object("EXCL", 35., 35., 35.);


//CONFIGURE AND PERFORM MEASUREMENTS
	//dijets->IncludeObject(incl);
	dijets->IncludeObject(mn);
	//dijets->IncludeObject(excl);

	//dijets->IncludeFunction(pt);
	//dijets->IncludeFunction(eta);
	//dijets->IncludeFunction(rap);
	//dijets->IncludeFunction(phi);
	dijets->IncludeFunction(dphi0);
	//dijets->IncludeFunction(dphi1);
	//dijets->IncludeFunction(dphi2);
	//dijets->IncludeFunction(dphi3);
	dijets->IncludeFunction(drap);
	//dijets->IncludeFunction(cos_1);

	cout << dijets->specification << "\t" << dijets->n_events << "\n";
	data->ReadSample(dijets);
	cout << dijets->specification << "\t" << dijets->n_events << "\n";
	dijets->AverageAndNormalize();
	dijets->WriteToFile("./dijets");

	return (EXIT_SUCCESS);
}
