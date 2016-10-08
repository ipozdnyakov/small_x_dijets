#include<iostream>
#include"measurement.h"
#include"object.h"
#include"sample.h"

using namespace std;

int main(int argc, char** argv) {

//	Decorrelations *decorr = new Decorrelations("decorrelations","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV");
	Object *dijets = new Object(35., 35., 35.);

	Measurement *distr = new Measurement("basic_distributions","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV");
	distr->IncludeObject(dijets);

	Sample *data = new Sample("FSQJets_2015_2016");
	
		cout << distr->specification << "\t" << distr->n_events << "\t" << distr->n_entries << "\n";

	data->ReadSample(distr);

		cout << distr->specification << "\t" << distr->n_events << "\t" << distr->n_entries << "\n";

	distr->AverageAndNormalize();
	distr->WriteToFile("./results");

	return (EXIT_SUCCESS);
}
