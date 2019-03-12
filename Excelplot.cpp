#include "Exceldriver\stdafx.h"
#include "Exceldriver\BitsAndPieces\StringConversions.hpp"
#include "Exceldriver\ExcelDriver.hpp"
#include "Exceldriver\ExcelMechanisms.hpp"
#include "Exceldriver\VectorsAndMatrices\NumericMatrix.cpp"
#include "Exceldriver\ExceptionClasses\DatasimException.hpp"
#include <iostream>
#include "Excelplot.h"

#include <string>
using namespace std;

int Excelplot(const vector<double>& CAAR1,		// CAAR beat vector
	const vector<double>& CAAR2,       //CAAR meet array vector
	const vector<double>& CAAR3       //CAAR miss array vector
)
{

	long N = CAAR1.size(); long M = CAAR1.size();

	Vector<double, long> xarr(N);
	Vector<double, long> yarr(N);
	Vector<double, long> yarr2(N;
	Vector<double, long> yarr3(N);

	double h1 = 1;
	xarr[xarr.MinIndex()] = -120;
	for (long i = xarr.MinIndex() + 1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i - 1] + h1;
		//cout << xarr[i] << endl;
	}
	int i = 0;

	for (long j = yarr.MinIndex(); j <= yarr.MaxIndex(); j++)
	{

		yarr[j] = CAAR1[i];
		yarr2[j] = CAAR2[i];
		yarr3[j] = CAAR3[i];
		//cout <<i <<" "<< CAAR1[i]<<" "<<yarr[j]<<endl;
		i++;
	}

	//list<std::string> rowlabels = convertToString(xarr);
	//list<std::string> columnlabels = convertToString(yarr);
	list<std::string> labels;
	labels.push_back("beat");
	labels.push_back("meet");
	labels.push_back("miss");
	list<Vector<double, long>> list1;
	list1.push_back(yarr);
	list1.push_back(yarr2);
	list1.push_back(yarr3);
	string title = "CAAR Trend of three groups";
	string horizontal = "Time";
	string vertical = "CAAR";


	std::string sheetName("First");

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!

	//excel.AddMatrix(sheetName, matrix, rowlabels, columnlabels);

	try
	{
		// Difference of vectors
		//printDifferenceInExcel(xarr, yarr2, yarr);
		printInExcel(xarr, labels, list1, title, vertical, horizontal);
	}
	catch (DatasimException& e)
	{
		e.print();
	}
	/*catch (...)
	{
		// Catches everything else
	}*/

	getchar();
	return 0;
}
