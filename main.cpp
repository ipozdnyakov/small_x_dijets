#include "sample.h"
#include "observable.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

using namespace std;

int main(int argc, char** argv) {

cout << "Start main programm:\n";

    TString work_dir  = "/afs/cern.ch/work/i/ivanp/2015_Decorrelator/CMSSW_7_4_15/src/";

    Double_t pt_min_1 = 35.; //pt_min_1 >= pt_min_2
    Double_t pt_min_2 = 35.;
    Double_t pt_veto  = 35.;
    Double_t FWD_weight = 0.5;
    TString Pt_min = "_pt";
				Pt_min += pt_min_1;
				Pt_min += "_";
				Pt_min += pt_min_2;
    TString Pt_veto = "_veto";
				Pt_veto += pt_veto;
    TString pict;

//------------------------------------OBSERVABLES---------------------------------------
    TString dir_name="jec_study";
    TString specification = "_FSQJets_2015_2016_data_13TeV_LowPU_MN_CNTR_dy0_9.4" + Pt_min;//+Pt_veto;
    Observable *MN_jets = new Observable(dir_name, specification);

//------------------------------------JEC UNC-------------------------------------------
    JetCorrectionUncertainty *jecUnc2015 = new JetCorrectionUncertainty("./jec_txt/2015/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
    JetCorrectionUncertainty *jecUnc2016 = new JetCorrectionUncertainty("./jec_txt/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt");

//------------------------------------READING-and-PROCESSING----------------------------

    Sample *data = new Sample("FSQJets_2015_2016");
    data->ReadSample(MN_jets, pt_min_1, pt_min_2, FWD_weight, pt_veto, jecUnc2016);
    cout << "Events: cntr - " << MN_jets->n_event_cntr << " fwd - " << MN_jets->n_event_fwd << "\n";

//------------------------------------POST PROCESSING-----------------------------------
    MN_jets->CalculateErrors();
    MN_jets->WriteToFile(work_dir + "results" + specification + ".root");

    return (EXIT_SUCCESS);
}
