#include<vector>
#include"event.h"
using namespace std;

void Event::AddJet( 
		double jet_pt,
		double jet_eta,
		double jet_phi,
		double jet_rap
        ){
                this->pt.push_back(jet_pt);
                this->eta.push_back(jet_eta);
                this->phi.push_back(jet_phi);
                this->rap.push_back(jet_rap);
};
