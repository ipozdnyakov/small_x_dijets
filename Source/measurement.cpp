#include<iostream>
#include<TFile.h>
#include"measurement.h"

using namespace std;

Measurement::Measurement(TString title, TString specification){
	this->specification = specification;
};

void Measurement::IncludeObject(Object *object){

	this->objects.push_back(object);

	vector<Observable*> new_object_obs;

	for(int i = 0; i < this->functions.size(); i++){
		new_object_obs.push_back(new Observable(object,functions[i]));
	}

	this->observables.push_back(new_object_obs);
	
};

void Measurement::IncludeFunction(Function *function){
	this->functions.push_back(function);

	for(int i = 0; i < this->objects.size(); i++){
		this->observables[i].push_back(new Observable(objects[i],function));
	}

};

void Measurement::ReadEvent(Event *event){
	for(int i = 0; i < this->objects.size(); i++){	
		for(int j = 0; j < this->functions.size(); j++){	
			this->n_events++;
			this->observables[i][j]->ReadEvent(event);
		}
	}
};

void Measurement::AverageAndNormalize(){
        if(this->averaged_and_normalized){
                cout << "PROCESSING ERROR: Measurement already averaged and normalized!\n";
                return;
        }

	for(int i = 0; i < this->objects.size(); i++){	
		for(int j = 0; j < this->functions.size(); j++){	
		        this->observables[i][j]->AverageAndNormalize();
		}
	}

        this->averaged_and_normalized = true;
};

void Measurement::WriteToFile(TString prefix){

	TString name = prefix + this->specification + ".root";

	TFile *file = new TFile(name,"RECREATE");
	file->Close();

	for(int i = 0; i < this->objects.size(); i++){	
		for(int j = 0; j < this->functions.size(); j++){	
		        this->observables[i][j]->WriteToFile(name);
		}
	}

};

/*Decorrelations::Decorrelations(TString dir_name, TString specification):Measurement(dir_name, specification){

	TString histname;

        histname = "dy";  histname += specification;
        dy = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        dy->Sumw2();

        histname = "w2";  histname += specification;
        w2_dy = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        w2_dy->Sumw2();

        histname = "excl_dy";  histname += specification;
        excl_dy = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        excl_dy->Sumw2();

        histname = "k_factor";  histname += specification;
        k_factor = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        k_factor->Sumw2();

        histname = "cos_1";  histname += specification;
        cos_1 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos_1->Sumw2();

        histname = "cos_2";  histname += specification;
        cos_2 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos_2->Sumw2();

        histname = "cos_3";  histname += specification;
        cos_3 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos_3->Sumw2();

        histname = "cos2_1";  histname += specification;
        cos2_1 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos2_1->Sumw2();

        histname = "cos2_2";  histname += specification;
        cos2_2 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos2_2->Sumw2();

        histname = "cos2_3";  histname += specification;
        cos2_3 = new TH1D(histname, dir_name, n_dy_bins, dy_bins);
        cos2_3->Sumw2();

        histname = "dphi_dy";  histname += specification;
        dphi_dy = new TH2D(histname, dir_name, n_dphi_bins, dphi_bins, n_dy_bins, dy_bins);
        dphi_dy->Sumw2();

}

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

void Decorrelations::ReadEvent(Event *event){

	for(int i; i < this->objects.size(); i++){	

		this->objects[i]->LoadEvent(event);

		if(event->nPV == 1){

		        if((this->objects[i]->pt_L.size() > 1)&&(this->objects[i]->pt_H.size() > 0)){

        		        if(event->CNTR > 0) this->n_event_cntr++;
                		if(event->FWD > 0) this->n_event_fwd++;

			        if(event->CNTR > 0){

					this->n_events++;
					this->n_entries++;
	
				        this->pt->CatchObject(this->objects[i], "pt");
				        this->eta->CatchObject(this->objects[i], "eta");
				        this->rap->CatchObject(this->objects[i], "rap");
				        this->phi->CatchObject(this->objects[i], "phi");


                			dy_MN = find_dy_MN(this->objects[i]->rap_H, this->objects[i]->rap_L);
			                dphi_MN = find_dphi_MN(this->objects[i]->rap_H, this->objects[i]->phi_H, this->objects[i]->rap_L, this->objects[i]->phi_L);

			                this->dphi[0]->Fill(dphi_MN,event->weight);
			                this->dy->Fill(dy_MN,event->weight);
       		         		this->w2_dy->Fill(dy_MN,event->weight*event->weight);
			                this->dphi_dy->Fill(dphi_MN,dy_MN,event->weight);

			                this->cos_1->Fill(dy_MN, event->weight*cos(pi - dphi_MN));
                			this->cos2_1->Fill(dy_MN,event->weight*pow(cos(pi - dphi_MN),2));
		        	        this->cos_2->Fill(dy_MN,event->weight*cos(2*(pi - dphi_MN)));
                			this->cos2_2->Fill(dy_MN,event->weight*pow(cos(2*(pi - dphi_MN)),2));
	                		this->cos_3->Fill(dy_MN,event->weight*cos(3*(pi - dphi_MN)));
			                this->cos2_3->Fill(dy_MN,event->weight*pow(cos(3*(pi - dphi_MN)),2));

                			if((this->objects[i]->pt_H.size() > 0)&&(this->objects[i]->pt_L.size() == 2)&&(!(this->objects[i]->veto))){
                        			this->excl_dy->Fill(dy_MN,event->weight);
                			}

	        		}//only CNTR events
        		}//enough jets
        	}//nPV == 1

		this->objects[i]->Clear();
	}
}

void Decorrelations::WriteToFile(TString prefix){

	TString name = prefix + this->specification + ".root";

	TFile *file = new TFile(name,"RECREATE");
	file->Close();

	dphi_dy->Write();
	dy->Write();
	excl_dy->Write();
	k_factor->Write();
	w2_dy->Write();
	cos_1->Write();
	cos_2->Write();
	cos_3->Write();

};*/   

