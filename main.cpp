#include "sample.h"
#include "observable.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

using namespace std;

int main(int argc, char** argv) {

cout << "Start main programm:\n";

    TString work_dir  = "/afs/cern.ch/work/i/ivanp/2015_Decorrelator/CMSSW_7_4_15/src/";
    Double_t FWD_weight = 0.5;

//------------------------------------OBSERVABLES---------------------------------------
    MN *MN_jets_35 = new MN("measurement", "_FSQJets_2015_2016_data_13TeV_LowPU_MN_CNTR_dy0_9.4", 35., 35., 35.);

//------------------------------------JEC UNC-------------------------------------------
    JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("./jec_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
    JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("./jec_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

//------------------------------------READING-and-PROCESSING----------------------------

    Sample *data = new Sample("FSQJets_2015_2016");

    data->ReadSample(MN_jets_35, FWD_weight, jecUnc2016);

    cout << "Events: cntr - " << MN_jets_35->n_event_cntr << " fwd - " << MN_jets_35->n_event_fwd << "\n";

//------------------------------------POST PROCESSING-----------------------------------
    MN_jets_35->CalculateErrors();
    MN_jets_35->WriteToFile(work_dir + "results");

    return (EXIT_SUCCESS);
}
