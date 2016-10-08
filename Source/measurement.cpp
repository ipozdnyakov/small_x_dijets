#include<iostream>
#include<TFile.h>
#include"measurement.h"
#include"bining.h"
#include"finder.h"

using namespace std;

Measurement::Measurement(TString title, TString specification){

	this->specification = specification;

        pt = new Observable("pt", title, pt_bins, n_pt_bins);
        eta = new Observable("eta", title, eta_towers, n_eta_towers);
        rap = new Observable("rap", title, eta_towers, n_eta_towers);
        phi = new Observable("phi", title, phi_towers, n_phi_towers);

};

void Measurement::IncludeObject(Object *object){
	this->objects.push_back(object);
}

void Measurement::ReadEvent(Event *event){

	for(int i; i < this->objects.size(); i++){	
		this->objects[i]->LoadEvent(event);

		this->n_events++;

	        this->pt->CatchObject(this->objects[i], "pt");
        	this->eta->CatchObject(this->objects[i], "eta");
	        this->rap->CatchObject(this->objects[i], "rap");
        	this->phi->CatchObject(this->objects[i], "phi");

		this->objects[i]->Clear();
	}
};

void Measurement::AverageAndNormalize(){
        if(this->averaged_and_normalized){
                cout << "PROCESSING ERROR: Measurement already averaged and normalized!\n";
                return;
        }

        this->pt->AverageAndNormalize();
        this->eta->AverageAndNormalize();
        this->rap->AverageAndNormalize();
        this->phi->AverageAndNormalize();

        this->averaged_and_normalized = true;
};

void Measurement::WriteToFile(TString prefix){

	TString name = prefix + this->specification + ".root";

	TFile *file = new TFile(name,"RECREATE");
	file->Close();

	this->pt->WriteToFile(name);
	this->eta->WriteToFile(name);
	this->rap->WriteToFile(name);
	this->phi->WriteToFile(name);

};

Decorrelations::Decorrelations(TString dir_name, TString specification):Measurement(dir_name, specification){

	TString histname;

        histname = "dphi_0";  histname += specification;
        dphi[0] = new TH1D(histname, dir_name, n_dphi_bins, dphi_bins);
        dphi[0]->Sumw2();

        histname = "dphi_1";  histname += specification;
        dphi[1] = new TH1D(histname, dir_name, n_dphi_bins, dphi_bins);
        dphi[1]->Sumw2();

        histname = "dphi_2";  histname += specification;
        dphi[2] = new TH1D(histname, dir_name, n_dphi_bins, dphi_bins);
        dphi[2]->Sumw2();

        histname = "dphi_3";  histname += specification;
        dphi[3] = new TH1D(histname, dir_name, n_dphi_bins, dphi_bins);
        dphi[3]->Sumw2();

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

		double dy_MN, dphi_MN;

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

/*		                MN_index = find_MN(rap_H, rap_L);
                		this->pt->Fill(pt_H[MN_index[0]],event->weight);
		                this->rap->Fill(rap_H[MN_index[0]],event->weight);
		                this->phi->Fill(phi_H[MN_index[0]],event->weight);
		                this->pt->Fill(pt_L[MN_index[1]],event->weight);
		                this->rap->Fill(rap_L[MN_index[1]],event->weight);
		                this->phi->Fill(phi_L[MN_index[1]],event->weight);
*/

                			dy_MN = find_dy_MN(this->objects[i]->rap_H, this->objects[i]->rap_L);
			                dphi_MN = find_dphi_MN(this->objects[i]->rap_H, this->objects[i]->phi_H, this->objects[i]->rap_L, this->objects[i]->phi_L);

			                this->dphi[0]->Fill(dphi_MN,event->weight);
			                this->dy->Fill(dy_MN,event->weight);
       		         		this->w2_dy->Fill(dy_MN,event->weight*event->weight);
			                this->dphi_dy->Fill(dphi_MN,dy_MN,event->weight);

                			if((dy_MN > 0.)&&(dy_MN < 3.))  this->dphi[1]->Fill(dphi_MN,event->weight);
		                	if((dy_MN > 3.)&&(dy_MN < 6.))  this->dphi[2]->Fill(dphi_MN,event->weight);
	                		if((dy_MN > 6.)&&(dy_MN < 9.4)) this->dphi[3]->Fill(dphi_MN,event->weight);

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

	pt->WriteToFile(name);
	eta->WriteToFile(name);
	rap->WriteToFile(name);
	phi->WriteToFile(name);

	dphi[0]->Write();
	dphi[1]->Write();
	dphi[2]->Write();
	dphi[3]->Write();
	dphi_dy->Write();
	dy->Write();
	excl_dy->Write();
	k_factor->Write();
	w2_dy->Write();
	cos_1->Write();
	cos_2->Write();
	cos_3->Write();

};   

