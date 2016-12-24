#include<vector>

#ifndef _EVENT_H
#define	_EVENT_H
using namespace std;

class Event {

//Event is a set of jets and parameters

private:
	string jec_cond = "centr";

public:
	int number, run;
	int nPV;
	int CNTR, FWD, MB;
	double weight;

	vector<double> pt;	//corrected jet pt 	
	vector<double> pt_unc;	//JEC uncertainty	 	
	vector<double> pt_cor;	//JEC coefficient	 	
	vector<double> eta;	 	
	vector<double> phi;	 	
	vector<double> rap;	 	

	Event(): run(-1), number(-1), nPV(-1), CNTR(-1), FWD(-1), MB(-1), weight(0.) { }
	Event(int r, int n, int npv, int cntr, int fwd, int mb, double w): 
		run(r), number(n), nPV(npv), CNTR(cntr), FWD(fwd), MB(mb), weight(w) { }
	void Init(int , int , int , int , int , int , double );
	string RunPileUp();
	void JecUp();
	void JecDown();
	void JecCentr();
	void Print();
	void Clear();
	void AddJet(double , double , double , double , double, double);
	void AddJets(vector<float> , vector<float> , vector<float> , vector<float> , vector<float>, vector<float>);

};
#endif	/* _EVENT_H */
