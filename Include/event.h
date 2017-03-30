#include<vector>

#ifndef _EVENT_H
#define	_EVENT_H
using namespace std;

class Event {

//Event is a set of jets and parameters

private:
	string jec_cond = "centr";

public:
	int number = -1, run = -1;
	int nPV = -1;
	int CNTR = -1, FWD2 = -1, FWD3 = -1, MB = -1;
	int CNTR_ps = -1, FWD2_ps = -1, FWD3_ps = -1, MB_ps = -1;
	double weight = 1.;
	bool gen_level = false;

	vector<double> pt;	//corrected jet pt 	
	vector<double> pt_unc;	//JEC uncertainty	 	
	vector<double> pt_cor;	//JEC coefficient	 	
	vector<double> eta;	 	
	vector<double> phi;	 	
	vector<double> rap;	 	

	vector<double> gen_pt;	 	
	vector<double> gen_eta;	 	
	vector<double> gen_phi;	 	
	vector<double> gen_rap;	 	


	Event(){};
	void Init(int , int , int , int , int , int , int , double , int , int , int , int );
	void JecUp();
	void JecDown();
	void JecCentr();
	void Print();
	void Clear();
	void AddJet(double , double , double , double , double, double);
	void AddJets(vector<float> , vector<float> , vector<float> , vector<float> , vector<float>, vector<float>);
	void AddGenJets(vector<float> , vector<float> , vector<float> , vector<float>);

	string RunPileUp();
};
#endif	/* _EVENT_H */
