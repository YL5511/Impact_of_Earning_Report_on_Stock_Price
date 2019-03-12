#ifndef Excelplot_h
#define Excelplot_h

#include "Exceldriver\stdafx.h"
#include "Exceldriver\BitsAndPieces\StringConversions.hpp"
#include "Exceldriver\ExcelDriver.hpp"
#include "Exceldriver\ExcelMechanisms.hpp"
#include "Exceldriver\VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "Exceldriver\ExceptionClasses\DatasimException.hpp"
#include <iostream>

#include <string>
using namespace std;

int Excelplot(const vector<double>& CAAR1,		// CAAR beat vector
	const vector<double>& CAAR2,       //CAAR meet array vector
	const vector<double>& CAAR3       //CAAR miss array vector
);

#endif
