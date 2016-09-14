#include<iostream>
#include"sample.h"
#include"measurement.h"

using namespace std;

int main(int argc, char** argv) {

//	Measurement *jets = new Measurement("basic distributions","_FSQJets_2015_2016_data_13TeV_LowPU");
	Decorrelations *jets = new Decorrelations("decorrelations","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV", 35., 35., 35.);

	Sample *data = new Sample("FSQJets_2015_2016");
	
		cout << jets->specification << "\t" << jets->n_events << "\t" << jets->n_entries << "\n";

	data->ReadSample(jets);

		cout << jets->specification << "\t" << jets->n_events << "\t" << jets->n_entries << "\n";

	jets->WriteToFile("./results");

	return (EXIT_SUCCESS);
}
