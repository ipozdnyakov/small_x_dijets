#include"observable.h"
using namespace std;
#define pi 3.1415926

Observable::Observable(TString dir_name, TString specification){
TString histname;
//------------------------------------BINING---------------------------------------
    double kfacbins[16]={0,0.5,1.0,1.5,2.0,2.5,3.0,
                         3.5,4.0,4.5,5.0,5.5,6.0,
                         7.0,8.0,9.4};

    double etabins[83]={-5.191,-4.889,-4.716,-4.538,-4.363,-4.191,
                -4.013,-3.839,-3.664,-3.489,-3.314,-3.139,-2.964,
                -2.853,-2.650,-2.500,-2.322,-2.172,-2.043,-1.930,
                -1.830,-1.740,-1.653,-1.566,-1.479,-1.392,-1.305,
                -1.218,-1.131,-1.044,-0.957,-0.870,-0.783,-0.696,
                -0.609,-0.522,-0.435,-0.348,-0.261,-0.174,-0.087,
                0,0.087,0.174,0.261,0.348,0.435,0.522,0.609,0.696,
                0.783,0.870,0.957,1.044,1.131,1.218,1.305,1.392,
                1.479,1.566,1.653,1.740,1.830,1.930,2.043,2.172,
                2.322,2.500,2.650,2.853,2.964,3.139,3.314,3.489,
                3.664,3.839,4.013,4.191,4.363,4.538,4.716,4.889,5.191};

    double ptbins[14]={15,20,25,30,35,40,50,60,80,100,120,160,200,300};

    double dphi_bins[11]={0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.70, 0.8, 0.9, 1.};
    for(int i = 0; i < 11; i++){
                        dphi_bins[i] = dphi_bins[i]*pi;
    }
    
	nk_bin = sizeof(kfacbins)/sizeof(kfacbins[0]);
	neta_bin = sizeof(etabins)/sizeof(etabins[0]);
	npt_bin = sizeof(ptbins)/sizeof(ptbins[0]);
	ndphi_bin = sizeof(dphi_bins)/sizeof(dphi_bins[0]);

        histname = "pt";  histname += specification;
        pt = new TH1D(histname, dir_name, npt_bin - 1, ptbins);
        pt->Sumw2();

        histname = "y";  histname += specification;
        y = new TH1D(histname, dir_name, neta_bin - 1, etabins);
        y->Sumw2();

        histname = "phi";  histname += specification;
        phi = new TH1D(histname, dir_name, 1000, -pi, pi);
        phi->Sumw2();

        histname = "dphi_0";  histname += specification;
        dphi[0] = new TH1D(histname, dir_name, ndphi_bin - 1, dphi_bins);
        dphi[0]->Sumw2();

        histname = "dphi_1";  histname += specification;
        dphi[1] = new TH1D(histname, dir_name, ndphi_bin - 1, dphi_bins);
        dphi[1]->Sumw2();

        histname = "dphi_2";  histname += specification;
        dphi[2] = new TH1D(histname, dir_name, ndphi_bin - 1, dphi_bins);
        dphi[2]->Sumw2();

        histname = "dphi_3";  histname += specification;
        dphi[3] = new TH1D(histname, dir_name, ndphi_bin - 1, dphi_bins);
        dphi[3]->Sumw2();

        histname = "dy";  histname += specification;
        dy = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        dy->Sumw2();

        histname = "w2";  histname += specification;
        w2_dy = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        w2_dy->Sumw2();

        histname = "excl_dy";  histname += specification;
        excl_dy = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        excl_dy->Sumw2();

        histname = "k_factor";  histname += specification;
        k_factor = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        k_factor->Sumw2();

        histname = "cos_1";  histname += specification;
        cos_1 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos_1->Sumw2();

        histname = "cos_2";  histname += specification;
        cos_2 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos_2->Sumw2();

        histname = "cos_3";  histname += specification;
        cos_3 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos_3->Sumw2();

        histname = "cos2_1";  histname += specification;
        cos2_1 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos2_1->Sumw2();

        histname = "cos2_2";  histname += specification;
        cos2_2 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos2_2->Sumw2();

        histname = "cos2_3";  histname += specification;
        cos2_3 = new TH1D(histname, dir_name, nk_bin - 1, kfacbins);
        cos2_3->Sumw2();

        histname = "dphi_dy";  histname += specification;
        dphi_dy = new TH2D(histname, dir_name, ndphi_bin - 1, dphi_bins, nk_bin - 1, kfacbins);
        dphi_dy->Sumw2();

}

Observable::~Observable(){
}

void Observable::CalculateErrors(){
//Errors calculation
Double_t w_ = 0., x_ = 0., y_ = 0., dx_ = 0., dy_ = 0., s_ = 0., ds_ = 0.;//k=s/x, s = x+y
Double_t dcos = 0., dcos_2 = 0., dcos_3 = 0.;

//                k_factor->Divide(dy,excl_dy,1.,1.,"b");

for(int i = 1; i < nk_bin; i++){
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

}

void Observable::WriteToFile(TString name){
TFile file_res(name,"RECREATE");
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
}   

