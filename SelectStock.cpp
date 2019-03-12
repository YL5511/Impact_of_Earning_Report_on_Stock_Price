

#include "SelectStock.h"

#include <stdio.h>

#include <string>

#include <iostream>

#include <sstream>

#include <vector>

#include <locale>

#include <iomanip>

#include <iostream>

#include <map>

#include <list>

using namespace std;


list<int> GenerateRandomInteger(int b, int m)

{

	list<int> l;     // create a list object l to store the generated random number

	int a, n;       // the range of the random numbers is [a,b], n is the number of random numbers

	a = 0;

	n = m+1;            // modify to 100!

	// check for invalid range

	if ((b < 0) || (a < 0) || (a > b) || (n > b))  // The two bounds should >0, and the number of random integers should < b

	{

		cout << "The range is invalid......";

		cout << endl;

	}

	else

	{

		while (l.size() < n)

		{

			l.push_back(rand() % (b - a + 1) + a);

			l.sort();   // sorting

			l.unique(); // delete the first of two consecutive same integer

		}
	}


	return l;

}





vector<string> SelectStock(vector<string> v , int n)

{    
    srand(time(NULL));
    
    list<int> l;

	l = GenerateRandomInteger(v.size(), n);
	
	vector<string> m2(l.size());

	list<int>::iterator it;

	int i=0;

	for (it = l.begin(); it != l.end(); it++)

	{
		
		m2[i]=v[*it];
		i++;
	}

	return m2;

}
