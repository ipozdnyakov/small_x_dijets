#include<TString.h>

#ifndef _DATASET_H
#define	_DATASET_H

using namespace std;

class Dataset {

//Dataset is a set of *.root files listed in the file in ./Docs/listing
//the name of the file is the name of the dataset

protected:

public:
	string name;
	bool min_bias_info = false;
	int mc_info = -1; // 1 - herwigpp, 2 - pythia
	bool mc_cntr_info = false;
	bool mc_fb_info = false;
	bool mc_low_pthat_info = false;
	bool mc_high_pthat_info = false;
	TString tree_name = "";
	TString run_num_name = "", lumi_num_name = "", event_num_name = "", nPV_name = "";
	TString CNTR_trg_name = "", FWD2_trg_name = "", FWD3_trg_name = "";
	TString CNTR_trg_ps_name = "", FWD2_trg_ps_name = "", FWD3_trg_ps_name = "";
	TString pt_name = "", phi_name = "", eta_name = "", rap_name = "";
	TString cor_name = "", unc_name = "";
	TString pt_vector_name = "", phi_vector_name = "", eta_vector_name = "", rap_vector_name = "";
	TString gen_pt_vector_name = "", gen_phi_vector_name = "", gen_eta_vector_name = "", gen_rap_vector_name = "";
	TString cor_vector_name = "", unc_vector_name = "";

	Dataset(string );
};
#endif	/* _Dataset_H */
