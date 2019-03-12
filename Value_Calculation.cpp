#include "Value_Calculation.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include "Exceldriver\stdafx.h"
using namespace std;

vector<double> AAR_Calculation(vector<vector<double>> AR)
{

	vector<double> aar_vector;
	int n = AR.size();
	int m = AR[0].size();
	for (int i = 0; i < m; i++)
	{
		double aar = 0;
		for (int k = 0; k < n; k++)
		{
			aar = (k*aar + AR[k][i]) / (k + 1);
		}
		aar_vector.push_back(aar);
	}
	return aar_vector;
}

vector<double> CAAR_Calculation(vector<double> AAR)
{
	double caar = 0;
	vector <double>caar_vector;
	int n = AAR.size();
	for (int i = 0; i < n; i++)
	{
		caar = AAR[i] + caar;
		caar_vector.push_back(caar);
	}
	return caar_vector;
}
