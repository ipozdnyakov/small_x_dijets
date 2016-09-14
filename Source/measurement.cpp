#include<TFile.h>
#include"measurement.h"
#include"bining.h"

using namespace std;
#define pi 3.1415926

Measurement::Measurement(TString dir_name, TString specification){

	this->specification = specification;

	TString histname;

	histname = "pt";  histname += specification;
        pt = new TH1D(histname, dir_name, n_pt_bins - 1, pt_bins);
        pt->Sumw2();

        histname = "eta";  histname += specification;
        eta = new TH1D(histname, dir_name, n_eta_towers - 1, eta_towers);
        eta->Sumw2();

        histname = "y";  histname += specification;
        y = new TH1D(histname, dir_name, n_eta_towers - 1, eta_towers);
        y->Sumw2();

        histname = "phi";  histname += specification;
        phi = new TH1D(histname, dir_name, n_phi_towers, -pi, pi);
        phi->Sumw2();
}

void Measurement::ReadEvent(Event *event){
	
	this->n_events++;

	for(int i = 0; i < event->pt.size(); i++){
                this->pt->Fill(event->pt[i]);
                this->eta->Fill(event->eta[i]);
                this->y->Fill(event->rap[i]);
                this->phi->Fill(event->phi[i]);
		this->n_entries++;
	}

}

void Measurement::WriteToFile(TString addres){

	TFile file_res(addres + this->specification + ".root","RECREATE");
	pt->Write();
	eta->Write();
	y->Write();
	phi->Write();

};

MN::MN(TString dir_name, TString specification, double pt_min_1, double pt_min_2, double pt_veto)
:Measurement(dir_name, specification){

	this->pt_min_1 = pt_min_1;
	this->pt_min_2 = pt_min_2;
	this->pt_veto = pt_veto;

	TString Pt_min = "_pt";
                           	Pt_min += pt_min_1;
                                Pt_min += "_";
                                Pt_min += pt_min_2;
	TString Pt_veto = "_veto";
                              	Pt_veto += pt_veto;


	this->specification = specification + Pt_min + Pt_veto; 

	TString histname;

	for(int i = 0; i < 11; i++){dphi_bins[i] = dphi_bins[i]*pi;}
    
        histname = "dphi_0";  histname += specification;
        dphi[0] = new TH1D(histname, dir_name, n_dphi_bins - 1, dphi_bins);
        dphi[0]->Sumw2();

        histname = "dphi_1";  histname += specification;
        dphi[1] = new TH1D(histname, dir_name, n_dphi_bins - 1, dphi_bins);
        dphi[1]->Sumw2();

        histname = "dphi_2";  histname += specification;
        dphi[2] = new TH1D(histname, dir_name, n_dphi_bins - 1, dphi_bins);
        dphi[2]->Sumw2();

        histname = "dphi_3";  histname += specification;
        dphi[3] = new TH1D(histname, dir_name, n_dphi_bins - 1, dphi_bins);
        dphi[3]->Sumw2();

        histname = "dy";  histname += specification;
        dy = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        dy->Sumw2();

        histname = "w2";  histname += specification;
        w2_dy = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        w2_dy->Sumw2();

        histname = "excl_dy";  histname += specification;
        excl_dy = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        excl_dy->Sumw2();

        histname = "k_factor";  histname += specification;
        k_factor = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        k_factor->Sumw2();

        histname = "cos_1";  histname += specification;
        cos_1 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos_1->Sumw2();

        histname = "cos_2";  histname += specification;
        cos_2 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos_2->Sumw2();

        histname = "cos_3";  histname += specification;
        cos_3 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos_3->Sumw2();

        histname = "cos2_1";  histname += specification;
        cos2_1 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos2_1->Sumw2();

        histname = "cos2_2";  histname += specification;
        cos2_2 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos2_2->Sumw2();

        histname = "cos2_3";  histname += specification;
        cos2_3 = new TH1D(histname, dir_name, n_dy_bins - 1, dy_bins);
        cos2_3->Sumw2();

        histname = "dphi_dy";  histname += specification;
        dphi_dy = new TH2D(histname, dir_name, n_dphi_bins - 1, dphi_bins, n_dy_bins - 1, dy_bins);
        dphi_dy->Sumw2();

}

void MN::CalculateErrors(){

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

void MN::ReadEvent(Event *event){

        vector<Double_t> pt_v_1, y_v_1, phi_v_1, eta_v_1;
        vector<Double_t> pt_v_2, y_v_2, phi_v_2, eta_v_2;
        vector<Double_t>::iterator m, n, q;
        vector<int> MN_index;

        Bool_t veto = true;
        Double_t dy_MN = 0., dphi_MN = 0.;

        for(int i = 0; i < event->pt.size(); i++){

                if((event->pt[i] > this->pt_min_1) && (fabs(event->rap[i]) < 4.7)){
                  pt_v_1.push_back(event->pt[i]);
                  phi_v_1.push_back(event->phi[i]);
                  y_v_1.push_back(event->rap[i]);
                  eta_v_1.push_back(event->eta[i]);
                }
                if((event->pt[i] > this->pt_min_2) && (fabs(event->rap[i]) < 4.7)){
                  pt_v_2.push_back(event->pt[i]);
                  phi_v_2.push_back(event->phi[i]);
                  y_v_2.push_back(event->rap[i]);
                  eta_v_2.push_back(event->eta[i]);
                }
                if((event->pt[i] < this->pt_min_2)&&(event->pt[i] > this->pt_veto)) veto = false;
        }
	if(event->nPV == 1){

	        if((pt_v_2.size() > 1)&&(pt_v_1.size() > 0)){

        	        if(event->CNTR > 0) this->n_event_cntr++;
                	if(event->FWD > 0) this->n_event_fwd++;

		        if(event->CNTR > 0){

				this->n_events++;
				this->n_entries++;
		                MN_index = find_MN(y_v_1, y_v_2);
                		this->pt->Fill(pt_v_1[MN_index[0]],event->weight);
		                this->y->Fill(y_v_1[MN_index[0]],event->weight);
		                this->phi->Fill(phi_v_1[MN_index[0]],event->weight);
		                this->pt->Fill(pt_v_2[MN_index[1]],event->weight);
		                this->y->Fill(y_v_2[MN_index[1]],event->weight);
		                this->phi->Fill(phi_v_2[MN_index[1]],event->weight);

                		dy_MN = find_dy_MN(y_v_1, y_v_2);
		                dphi_MN = find_dphi_MN(y_v_1, phi_v_1, y_v_2, phi_v_2);

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

                		if((pt_v_1.size() > 0)&&(pt_v_2.size() == 2)&&veto){
                        		this->excl_dy->Fill(dy_MN,event->weight);
                		}

        		}//only CNTR events
        	}//enough jets
        }//nPV == 1

}

void MN::WriteToFile(TString addres){

	TFile file_res(addres + this->specification + ".root","RECREATE");
	pt->Write();
	y->Write();
	phi->Write();
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

