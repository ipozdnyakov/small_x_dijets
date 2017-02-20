#include<iostream>
#include<TFile.h>
#include<TTree.h>
#include<TString.h>
#include"measurement.h"

extern bool verbose, print_this_event;

using namespace std;

Measurement::Measurement(TString title, TString specification){
	this->specification = specification;
};

void Measurement::IncludeObject(Object *object){
	this->objects.push_back(object);

	vector<vector<Observable*>>	for_each_function;
	vector<Observable*> 		for_each_function_and_sample;

	for(int j = 0; j < this->functions.size(); j++){
		for(int k = 0; k < this->samples.size(); k++){
			for_each_function_and_sample.push_back(new Observable(object,functions[j],samples[k]));
		}
		for_each_function.push_back(for_each_function_and_sample);
		for_each_function_and_sample.clear();
	}

	this->observables.push_back(for_each_function);
};

void Measurement::IncludeFunction(Function *function){
	this->functions.push_back(function);

	vector<Observable*> for_each_object_and_sample;

	for(int i = 0; i < this->objects.size(); i++){
		for(int k = 0; k < this->samples.size(); k++){
			for_each_object_and_sample.push_back(new Observable(objects[i],function,samples[k]));
		}
		this->observables[i].push_back(for_each_object_and_sample);
		for_each_object_and_sample.clear();
	}

};

void Measurement::IncludeSample(Sample *sample){
	this->samples.push_back(sample);

	for(int i = 0; i < this->objects.size(); i++){
		for(int j = 0; j < this->functions.size(); j++){
		this->observables[i][j].push_back(new Observable(objects[i],functions[j],sample));
		}
	}

};

void Measurement::ReadDataset(Dataset *dataset){

cout << this->specification << "\t" << this->n_events << "\n";

        string file_name;

        ifstream data_files("./Docs/listing/" + dataset->name);
        cout << "\t-reading data files from set " << dataset->name << ":\n";
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, dataset);
        }
	cout << "\n";

cout << this->specification << "\t" << this->n_events << "\n";

};

void Measurement::ReadDatasetFast(Dataset *dataset){

cout << this->specification << "\t" << this->n_events << "\t verbose = "  << verbose << "\n";

        string file_name;

        ifstream data_files("./Docs/listing/" + dataset->name);
        cout << "\t-reading data files from set " << dataset->name << ":\n";
	int i = 0;
        while(getline(data_files, file_name)&&(i < 10)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, dataset);
		i++;
        }
	cout << "\n";

cout << this->specification << "\t" << this->n_events << "\n";

};

void Measurement::ReadFile(string name, Dataset *dataset){

	TString file_name = name;
	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get(dataset->tree_name);
	Int_t nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\t";

        Int_t iLumi = 0, iEvent = 0, iRun = 0, nPV = 0;
	Int_t CNTR = -1, FWD2 = -1, FWD3 = -1, MB = -1;
	Int_t CNTR_ps = -1, FWD2_ps = -1, FWD3_ps = -1, MB_ps = -1;
	double weight = 1.;
        double pt = 0., phi = 0., eta = 0., rap = 0., cor = 0., unc = 0.;
        vector<float> *pt_v = 0, *phi_v = 0, *eta_v = 0, *rap_v = 0, *cor_v = 0, *unc_v = 0;

	// Each of dataset's TTree (in each file) contains (generally) unique set of branch names
	// these branch names are listed in the class Dataset - separate list for each dataset name
	// if the branch does not exist in the dataset the name is empty ( == "" )
	// below the check of branch existens is performing for each potential branch and
	// if the branch exists, then assign it to the corresponding local variable

	if(dataset->min_bias_info) MB = 1;

	if(dataset->lumi_num_name != "") tree->SetBranchAddress(dataset->lumi_num_name, &iLumi);
	if(dataset->run_num_name != "") tree->SetBranchAddress(dataset->run_num_name, &iRun);
	if(dataset->event_num_name != "") tree->SetBranchAddress(dataset->event_num_name, &iEvent);
	if(dataset->nPV_name != "") tree->SetBranchAddress(dataset->nPV_name, &nPV);
	if(dataset->CNTR_trg_name != "") tree->SetBranchAddress(dataset->CNTR_trg_name, &CNTR);
	if(dataset->FWD2_trg_name != "") tree->SetBranchAddress(dataset->FWD2_trg_name, &FWD2);
	if(dataset->FWD3_trg_name != "") tree->SetBranchAddress(dataset->FWD3_trg_name, &FWD3);
	if(dataset->CNTR_trg_ps_name != "") tree->SetBranchAddress(dataset->CNTR_trg_ps_name, &CNTR_ps);
	if(dataset->FWD2_trg_ps_name != "") tree->SetBranchAddress(dataset->FWD2_trg_ps_name, &FWD2_ps);
	if(dataset->FWD3_trg_ps_name != "") tree->SetBranchAddress(dataset->FWD3_trg_ps_name, &FWD3_ps);

	if(dataset->pt_vector_name != "") tree->SetBranchAddress(dataset->pt_vector_name, &pt_v);
	if(dataset->rap_vector_name != "") tree->SetBranchAddress(dataset->rap_vector_name, &rap_v);
	if(dataset->eta_vector_name != "") tree->SetBranchAddress(dataset->eta_vector_name, &eta_v);
	if(dataset->phi_vector_name != "") tree->SetBranchAddress(dataset->phi_vector_name, &phi_v);
	if(dataset->cor_vector_name != "") tree->SetBranchAddress(dataset->cor_vector_name, &cor_v);
	if(dataset->unc_vector_name != "") tree->SetBranchAddress(dataset->unc_vector_name, &unc_v);

	// The branches below are scalar and corresponds to the samples obtained without CFF
	// in such samples there are one entry to the Tree per jet rather than per event

	if(dataset->pt_name != "") tree->SetBranchAddress(dataset->pt_name, &pt);
	if(dataset->rap_name != "") tree->SetBranchAddress(dataset->rap_name, &rap);
	if(dataset->eta_name != "") tree->SetBranchAddress(dataset->eta_name, &eta);
	if(dataset->phi_name != "") tree->SetBranchAddress(dataset->phi_name, &phi);
	if(dataset->cor_name != "") tree->SetBranchAddress(dataset->cor_name, &cor);
	if(dataset->unc_name != "") tree->SetBranchAddress(dataset->unc_name, &unc);



	tree->GetEntry(0);
	cout << "Run: " << iRun << " pt:" << pt_v << "\n";
	Int_t nEvent = iEvent;

	Event *event = new Event();

	if(pt_v != 0){
		for(int i = 0 ; i < nentries ; i++){
			tree->GetEntry(i);
			if(verbose){
				if((pt_v->size() == 5)&&(nPV == 1)&&(FWD2 == 1)){
					print_this_event = true;
				}
			}
			event->Init(iRun, iEvent, nPV, CNTR, FWD2, FWD3, MB, weight, CNTR_ps, FWD2_ps, FWD3_ps, MB_ps);
			event->AddJets(*pt_v, *eta_v, *phi_v, *rap_v, *cor_v, *unc_v);
			this->ReadEvent(event);
			event->Clear();
			if(verbose){
				if(print_this_event){
					verbose = false;
					print_this_event = false;
				}
			}
		}
	}else{
		event->Init(iRun, iEvent, nPV, CNTR, FWD2, FWD3, MB, weight, CNTR_ps, FWD2_ps, FWD3_ps, MB_ps);
		for(int i = 0 ; i < nentries ; i++){
			tree->GetEntry(i);
				//cout << iRun << " " << iEvent << " " << nPV << " " << CNTR << " " << FWD2 << " " << FWD3 
				//<< " " << pt << " " << eta << " " << rap << " " << phi << "\n";
			if(iEvent == nEvent){				//in Event
				event->AddJet(pt, eta, phi, rap, cor, -1.);
			}else{						//out Event
				//i = i-1;
				nEvent = iEvent;
				this->ReadEvent(event);
				event->Clear();
				event->Init(iRun, iEvent, nPV, CNTR, FWD2, FWD3, MB, weight, CNTR_ps, FWD2_ps, FWD3_ps, MB_ps);
	   		}
		}
	}
};

void Measurement::ReadEvent(Event *event){
	this->n_events++;

	if(print_this_event){event->Print();}

	for(int i = 0; i < this->objects.size(); i++){
		for(int j = 0; j < this->functions.size(); j++){
			for(int k = 0; k < this->samples.size(); k++){
				this->observables[i][j][k]->ReadEvent(event);
			}
		}
	}
};


Observable* Measurement::GetObservable(TString object_name, TString function_name, TString sample_name){

	for(int i = 0; i < this->objects.size(); i++){
		for(int j = 0; j < this->functions.size(); j++){
			for(int k = 0; k < this->samples.size(); k++){
				if(   (objects[i]->name == object_name)
				    &&(functions[j]->name == function_name)
				    &&(samples[k]->name == sample_name)){
					return this->observables[i][j][k];
				}
			}
		}
	}

	cout << "Observable for object " << object_name << " , function " << function_name << " and sample "<< sample_name <<" not found\n";
	return 0;
};

void Measurement::WriteToFile(TString prefix, int mode){

	TString name = prefix + this->specification + ".root";

	TFile *file = new TFile(name,"RECREATE");
	file->Close();

	if(mode > 1){
		for(int i = 0; i < this->objects.size(); i++){	
			for(int j = 0; j < this->functions.size(); j++){	
				for(int k = 0; k < this->samples.size(); k++){	
		        		this->observables[i][j][k]->WriteToFile(name);
				}
			}
		}
	}

	if(mode > 0){
		for(int i = 0; i < this->results.size(); i++){
			if(results[i]->calculated){
				results[i]->WriteToFile(name);
			}
		}
	}

};

void Measurement::CalculateResult(Result *result){

	this->results.push_back(result);

	if(result->name == "dphi_all_incl"){

		Observable* dphi = this->GetObservable("INCL","dphi_0","merged");
		dphi->data->Scale(1./dphi->data->Integral());
		result->result = dphi->data;

	}else if(result->name == "dphi_low_incl"){

		Observable* dphi = this->GetObservable("INCL","dphi_1","merged");
		dphi->data->Scale(1./dphi->data->Integral());
		result->result = dphi->data;

	}else if(result->name == "eff_pt_sublead_cntr_trg"){

		Observable* trg_bias = this->GetObservable("INCL","pt_sublead","central_trg");
		Observable* unbiased = this->GetObservable("INCL","pt_sublead","unbiased_central");
		delete result->result;
		result->result = new TH1D(*(trg_bias->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		result->calculated = result->result->Divide(trg_bias->data, unbiased->data, 1., 1., "b");

	}else if(result->name == "eff_pt_sublead_fwd3_cntr_trg"){

		Observable* trg_bias = this->GetObservable("INCL","pt_sublead_fwd3","central_trg");
		Observable* unbiased = this->GetObservable("INCL","pt_sublead_fwd3","unbiased_central");
		delete result->result;
		result->result = new TH1D(*(trg_bias->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		result->calculated = result->result->Divide(trg_bias->data, unbiased->data, 1., 1., "b");

	}else if(result->name == "eff_pt_sublead_fwd1d3_cntr_trg"){

		Observable* trg_bias = this->GetObservable("INCL","pt_sublead_fwd1d3","central_trg");
		Observable* unbiased = this->GetObservable("INCL","pt_sublead_fwd1d3","unbiased_central");
		delete result->result;
		result->result = new TH1D(*(trg_bias->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		result->calculated = result->result->Divide(trg_bias->data, unbiased->data, 1., 1., "b");

	}else if(result->name == "eff_pt_sublead_forward2_trg"){

		Observable* trg_bias = this->GetObservable("INCL","pt_sublead","forward2_trg");
		Observable* unbiased = this->GetObservable("INCL","pt_sublead","unbiased_forward2");
		delete result->result;
		result->result = new TH1D(*(trg_bias->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		result->calculated = result->result->Divide(trg_bias->data, unbiased->data, 1., 1., "b");

	}else if(result->name == "eff_pt_sublead_forward3_trg"){

		Observable* trg_bias = this->GetObservable("INCL","pt_sublead","forward3_trg");
		Observable* unbiased = this->GetObservable("INCL","pt_sublead","unbiased_forward3");
		delete result->result;
		result->result = new TH1D(*(trg_bias->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		result->calculated = result->result->Divide(trg_bias->data, unbiased->data, 1., 1., "b");

	}else if(result->name == "forward_incl_pt35_eta2.1_weight"){

		Observable* cntr = this->GetObservable("INCL","drap","central_pt35");
		Observable* cntr_no_fwd = this->GetObservable("INCL","drap","central_no_fwd_pt35_eta2.1");
		Observable* forward = this->GetObservable("INCL","drap","forward_pt35_eta2.1");
		delete result->result;
		result->result = new TH1D(*(cntr->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		
		TH1D *difference =  new TH1D(*(cntr->data));
		difference->Add(cntr_no_fwd->data,-1.);

		result->calculated = result->result->Divide(difference, forward->data, 1., 1., "b");

	}else if(result->name == "forward_mn_pt35_eta2.1_weight"){

		Observable* cntr = this->GetObservable("MN","drap","central_pt35");
		Observable* cntr_no_fwd = this->GetObservable("MN","drap","central_no_fwd_pt35_eta2.1");
		Observable* forward = this->GetObservable("MN","drap","forward_pt35_eta2.1");
		delete result->result;
		result->result = new TH1D(*(cntr->data));
		result->result->Sumw2();
		result->result->SetName(result->name);
		
		TH1D *difference =  new TH1D(*(cntr->data));
		difference->Add(cntr_no_fwd->data,-1.);

		result->calculated = result->result->Divide(difference, forward->data, 1., 1., "b");

	}else{
		cout << "Measurement Error: Case for result " << result->name << " not found\n";
	}

};

/*
        Result *pt_spectrum = new Result("pt_spectrum");
        Result *dphi_mn_1 = new Result("dphi_low_mn");
        Result *dphi_mn_2 = new Result("dphi_med_mn");
        Result *dphi_mn_3 = new Result("dphi_hig_mn");
        Result *cos_dphi = new Result("cos_dphi");



void Decorrelations::CalculateErrors(){

	Double_t w_ = 0., x_ = 0., y_ = 0., dx_ = 0., dy_ = 0., s_ = 0., ds_ = 0.;//k=s/x, s = x+y
	Double_t dcos = 0., dcos_2 = 0., dcos_3 = 0.;

//	k_factor->Divide(dy,excl_dy,1.,1.,"b");

	for(int i = 1; i < n_dy_bins; i++){

		//K-factor-Errors
		x_ = excl_dy->GetBinContent(i);
		dx_ = excl_dy->GetBinError(i);
		s_ = dy->GetBinContent(i);
		ds_ = dy->GetBinError(i);
		y_ = s_ - x_;
		w_ = y_/x_;
		dy_ = sqrt(pow(ds_,2) - pow(dx_,2));
		if(x_ != 0){k_factor->SetBinContent(i,s_/x_);}else{k_factor->SetBinContent(i,0);}
		k_factor->SetBinError(i,sqrt(fabs( ( dy_*dy_ + w_*w_*dx_*dx_ )/(x_*x_) )));

		//COS_Errors
		cos_1->SetBinContent(i,cos_1->GetBinContent(i)/s_);
		cos2_1->SetBinContent(i,cos2_1->GetBinContent(i)/s_);

		cos_2->SetBinContent(i,cos_2->GetBinContent(i)/s_);
		cos2_2->SetBinContent(i,cos2_2->GetBinContent(i)/s_);

		cos_3->SetBinContent(i,cos_3->GetBinContent(i)/s_);
		cos2_3->SetBinContent(i,cos2_3->GetBinContent(i)/s_);

		dcos = sqrt(
			(fabs(cos2_1->GetBinContent(i)
         		-
         		pow(cos_1->GetBinContent(i),2))
         		));
		cos_1->SetBinError(i,dcos*sqrt(w2_dy->GetBinContent(i))/s_);


		dcos_2 = sqrt(
			(fabs(cos2_2->GetBinContent(i)
			-
         		pow(cos_2->GetBinContent(i),2))
         		));
 		cos_2->SetBinError(i,dcos_2*sqrt(w2_dy->GetBinContent(i))/s_);

		dcos_3 = sqrt(
			(fabs(cos2_3->GetBinContent(i)
         		-
         		pow(cos_3->GetBinContent(i),2))
         		));
		cos_3->SetBinError(i,dcos_3*sqrt(w2_dy->GetBinContent(i))/s_);
	}

};
*/   

