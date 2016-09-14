#include"sample.h"
#include"measurement.h"
#include"CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

//JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("./jec_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
//JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("./jec_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

using namespace std;

int main(int argc, char** argv) {

//	Measurement *jets = new Measurement("distributions","_FSQJets_2015_2016_data_13TeV_LowPU");
	MN *jets = new MN("distributions","_FSQJets_2015_2016_data_13TeV_LowPU_MN_35GeV", 35., 35., 35.);

	Sample *data = new Sample("FSQJets_2015_2016");
	
		cout << jets->specification << "\t" << jets->n_events << "\t" << jets->n_entries << "\n";

	data->ReadSample(jets);

		cout << jets->specification << "\t" << jets->n_events << "\t" << jets->n_entries << "\n";

	jets->WriteToFile("./results");

	return (EXIT_SUCCESS);
}
