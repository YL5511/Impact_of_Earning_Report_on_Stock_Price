
#ifndef SelectStock_h

#define SelectStock_h

#include <stdio.h>

#include <string>

#include <sstream>

#include <vector>

#include <locale>

#include <iomanip>

#include <iostream>

#include <fstream>  // for ifstream

#include <cassert>

#include <map>

#include <list>

using namespace std;





// Generate 40 different random integers

list<int> GenerateRandomInteger(vector<string> v, int n);



// Randomly select 40 stocks from each group

vector<string> SelectStock(vector<string> v, int m);



#endif


