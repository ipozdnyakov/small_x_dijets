#include<vector>
#include<math.h>

using namespace std;

#ifndef _FINDER_H
#define	_FINDER_H
	vector<int> find_MN(vector<double> , vector<double>);

	double find_dy_MN(vector<double> , vector<double>);

	double find_dphi_MN(vector<double> , vector<double> , vector<double> , vector<double>);

	int find_closest(double , double , vector<double> , vector<double> , double *, int );

	double find_dy(vector<double> );

	double find_dphi(vector<double> , vector<double> );

	int find_i_min(vector<double> );

	int find_i_max(vector<double> );

#endif	/* _FINDER_H */

