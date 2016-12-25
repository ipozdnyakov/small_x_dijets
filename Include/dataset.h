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

	TString tree_name = "";
	TString run_num_name = "", lumi_num_name = "", event_num_name = "", nPV_name = "";
	TString CNTR_trg_name = "", FWD2_trg_name = "", FWD3_trg_name = "";
	TString CNTR_trg_ps_name = "", FWD2_trg_ps_name = "", FWD3_trg_ps_name = "";
	TString pt_name = "", phi_name = "", eta_name = "", rap_name = "";
	TString cor_name = "", unc_name = "";
	TString pt_vector_name = "", phi_vector_name = "", eta_vector_name = "", rap_vector_name = "";
	TString cor_vector_name = "", unc_vector_name = "";

	Dataset(string );
};
#endif	/* _Dataset_H */
