#include<iostream>
#include<TFile.h>
#include<TTree.h>
#include<TString.h>
#include"measurement.h"

using namespace std;

Measurement::Measurement(TString title, TString specification){
	this->specification = specification;
};

void Measurement::IncludeObject(Object *object){

	this->objects.push_back(object);

	vector<Observable*> new_central;
	vector<Observable*> new_central_no_fwd;
	vector<Observable*> new_forward;
	vector<Observable*> new_minimum_bias;

	for(int i = 0; i < this->functions.size(); i++){
		new_central.push_back(new Observable(object,functions[i],"CNTR"));
		new_central_no_fwd.push_back(new Observable(object,functions[i],"CNTRnoFWD"));
		new_forward.push_back(new Observable(object,functions[i],"FWD"));
		new_minimum_bias.push_back(new Observable(object,functions[i],"MINBIAS"));
	}

	this->central.push_back(new_central);
	this->central_no_fwd.push_back(new_central_no_fwd);
	this->forward.push_back(new_forward);
	this->minimum_bias.push_back(new_minimum_bias);
	
};

void Measurement::IncludeFunction(Function *function){
	this->functions.push_back(function);

	for(int i = 0; i < this->objects.size(); i++){
		this->central[i].push_back(new Observable(objects[i],function,"CNTR"));
		this->central_no_fwd[i].push_back(new Observable(objects[i],function,"CNTRnoFWD"));
		this->forward[i].push_back(new Observable(objects[i],function,"FWD"));
		this->minimum_bias[i].push_back(new Observable(objects[i],function,"MINBIAS"));
	}

};

void Measurement::IncludeResult(Result *result){
	this->results.push_back(result);
};

void Measurement::ReadSample(Sample *sample){

        string file_name;

        ifstream data_files("./Docs/listing/" + sample->name);
        cout << "\t-reading data files from set " << sample->name << ":\n";
        while(getline(data_files, file_name)){
                cout << "\t" << file_name << "\t";
                this->ReadFile(file_name, sample);
        }
	cout << "\n";

};

void Measurement::ReadFile(string name, Sample *sample){

	TString file_name = name;
	TFile Jfile(file_name);
	TTree* tree;
	tree = (TTree*) Jfile.Get(sample->tree_name);
	Int_t nentries = tree->GetEntries();
	cout << "Entries: " << nentries << "\t";

        Int_t iLumi = 0, iEvent = 0, iRun = 0, nPV = 0;
	Int_t CNTR = 1, FWD2 = -1, FWD3 = -1;
	Int_t CNTR_ps = 1, FWD2_ps = -1, FWD3_ps = -1;
        double pt = 0., phi = 0., eta = 0., rap = 0., cor = 0., unc = 0.;
        vector<float> *pt_v = 0, *phi_v = 0, *eta_v = 0, *rap_v = 0, *cor_v = 0, *unc_v = 0;

	if(sample->lumi_num_name != "") tree->SetBranchAddress(sample->lumi_num_name, &iLumi);
	if(sample->run_num_name != "") tree->SetBranchAddress(sample->run_num_name, &iRun);
	if(sample->event_num_name != "") tree->SetBranchAddress(sample->event_num_name, &iEvent);
	if(sample->nPV_name != "") tree->SetBranchAddress(sample->nPV_name, &nPV);
	if(sample->CNTR_trg_name != "") tree->SetBranchAddress(sample->CNTR_trg_name, &CNTR);
	if(sample->FWD2_trg_name != "") tree->SetBranchAddress(sample->FWD2_trg_name, &FWD2);
	if(sample->FWD3_trg_name != "") tree->SetBranchAddress(sample->FWD3_trg_name, &FWD3);
	if(sample->CNTR_trg_ps_name != "") tree->SetBranchAddress(sample->CNTR_trg_ps_name, &CNTR_ps);
	if(sample->FWD2_trg_ps_name != "") tree->SetBranchAddress(sample->FWD2_trg_ps_name, &FWD2_ps);
	if(sample->FWD3_trg_ps_name != "") tree->SetBranchAddress(sample->FWD3_trg_ps_name, &FWD3_ps);

	if(sample->pt_name != "") tree->SetBranchAddress(sample->pt_name, &pt);
	if(sample->rap_name != "") tree->SetBranchAddress(sample->rap_name, &rap);
	if(sample->eta_name != "") tree->SetBranchAddress(sample->eta_name, &eta);
	if(sample->phi_name != "") tree->SetBranchAddress(sample->phi_name, &phi);
	if(sample->cor_name != "") tree->SetBranchAddress(sample->cor_name, &cor);
	if(sample->unc_name != "") tree->SetBranchAddress(sample->unc_name, &unc);

	if(sample->pt_vector_name != "") tree->SetBranchAddress(sample->pt_vector_name, &pt_v);
	if(sample->rap_vector_name != "") tree->SetBranchAddress(sample->rap_vector_name, &rap_v);
	if(sample->eta_vector_name != "") tree->SetBranchAddress(sample->eta_vector_name, &eta_v);
	if(sample->phi_vector_name != "") tree->SetBranchAddress(sample->phi_vector_name, &phi_v);
	if(sample->cor_vector_name != "") tree->SetBranchAddress(sample->cor_vector_name, &cor_v);
	if(sample->unc_vector_name != "") tree->SetBranchAddress(sample->unc_vector_name, &unc_v);

	tree->GetEntry(0);
	cout << "Run: " << iRun << " pt:" << pt_v << "\n";
	Int_t nEvent = iEvent;

	Event *event = new Event();

	if(pt_v != 0){
		for(int i = 0 ; i < nentries ; i++){
			tree->GetEntry(i);
			event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
			event->AddJets(*pt_v, *eta_v, *phi_v, *rap_v, *cor_v, *unc_v);
			this->ReadEvent(event);
			event->Clear();
		}
	}else{
		event->Init(iRun, iEvent, nPV, CNTR, FWD2, -1, 1.);
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
				event->Init(iRun, iEvent, nPV, CNTR, FWD3, -1, 1.);
	   		}
		}
	}
};

void Measurement::ReadEvent(Event *event){
	this->n_events++;
	for(int i = 0; i < this->objects.size(); i++){
		for(int j = 0; j < this->functions.size(); j++){
			if(event->CNTR > 0){
				this->central[i][j]->ReadEvent(event);
				if(event->FWD == 0.) this->central_no_fwd[i][j]->ReadEvent(event);
			}
			if(event->FWD > 0) this->forward[i][j]->ReadEvent(event);
			if(event->MB > 0) this->minimum_bias[i][j]->ReadEvent(event);
		}
	}
};


Observable* Measurement::GetObservableCentral(TString object_name, TString function_name){

	for(int i = 0; i < this->objects.size(); i++){
		for(int j = 0; j < this->functions.size(); j++){
			if((objects[i]->name == object_name)&&(functions[i]->name == function_name)){
				return this->central[i][j];
			}
		}
	}

	cout << "Observable for object " << object_name << " and function " << function_name << "not found\n";
	return 0;
};

void Measurement::Merge(){
        if(this->merged){
                cout << "Measurement Error: Measurement already merged\n";
                return;
        }

	for(int i = 0; i < this->objects.size(); i++){	
		for(int j = 0; j < this->functions.size(); j++){	
		        this->central[i][j]->AverageAndNormalize();
		        this->central_no_fwd[i][j]->AverageAndNormalize();
		        this->forward[i][j]->AverageAndNormalize();
		        this->minimum_bias[i][j]->AverageAndNormalize();
		}
	}

        this->merged = true;
};

void Measurement::WriteToFile(TString prefix){

	TString name = prefix + this->specification + ".root";

	TFile *file = new TFile(name,"RECREATE");
	file->Close();

	for(int i = 0; i < this->objects.size(); i++){	
		for(int j = 0; j < this->functions.size(); j++){	
		        this->central[i][j]->WriteToFile(name);
		        this->central_no_fwd[i][j]->WriteToFile(name);
		        this->forward[i][j]->WriteToFile(name);
		        this->minimum_bias[i][j]->WriteToFile(name);
		}
	}

};

void Measurement::CalculateResults(){
        if(this->results_calculated){
                cout << "Measurement Error:results already calculated\n";
                return;
        }

	for(int i = 0; i < this->results.size(); i++){
		if(results[i]->name == "dphi_all_incl"){
			Observable* dphi = this->GetObservableCentral("INCL","dphi_0");
			dphi->data->Scale(1./dphi->data->Integral());
			results[i]->result = dphi->data;
		}else if(results[i]->name == "dphi_low_incl"){
			Observable* dphi = this->GetObservableCentral("INCL","dphi_1");
			dphi->data->Scale(1./dphi->data->Integral());
			results[i]->result = dphi->data;
		}else{
			cout << "Instructions for result " << results[i]->name << "not found";
		}
	}

        this->results_calculated = true;
};

/*

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

