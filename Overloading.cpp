#include "Overloading.h"
#include "Exceldriver\stdafx.h"

using namespace std;

vector<double> operator-(const vector<double>& v, const vector<double>& w)
{
	int s = v.size();
	vector<double> minus(s);

	for (int j = 0; j < s; j++) minus[j] = v[j] - w[j];

	return minus;
}
