#include<iostream>
#include"sample.h"
#include"object.h"
#include"measurement.h"

using namespace std;

int main(int argc, char** argv) {

//	Measurement *jets = new Measurement("basic distributions","_FSQJets_2015_2016_data_13TeV_LowPU");
	Decorrelations *decorr = new Decorrelations("decorrelations","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV", 35., 35., 35.);
	Object *dijets = new Object(35., 35., 35.);
	Sample *data = new Sample("FSQJets_2015_2016");
	
		cout << decorr->specification << "\t" << decorr->n_events << "\t" << decorr->n_entries << "\n";

	data->ReadSample(decorr, dijets);

		cout << decorr->specification << "\t" << decorr->n_events << "\t" << decorr->n_entries << "\n";

	decorr->WriteToFile("./results");

	return (EXIT_SUCCESS);
}
