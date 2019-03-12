#include "Stock.h"
#include "Overloading.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include "Exceldriver\stdafx.h"

using namespace std;



// Default constructor

Stock::Stock() : symbol("IWB")
{
	map<string, double> s1;
	price = s1;
}



// Constructor with arguments

Stock::Stock(string symbol_, map<string, double>price_) :symbol(symbol_), price(price_)

{}



// Copy constructor

Stock::Stock(const Stock& s) :symbol(s.symbol), price(s.price)

{}



// Destructor

Stock::~Stock()

{}





// Selectors

string Stock::Get_symbol() const

{

	return symbol;

}

string Stock::Get_announcement_date()
{
	map<string, double>::iterator itt;
	int i = 1;
	for (itt = price.begin(); itt != price.end(); itt++)
	{
		if (i == 121) return itt->first;
		i++;
	}
	return 0;
}



map<string, double> Stock::Get_price() const

{

	return price;

}


// Modifiers

void Stock::Set_symbol(string newsymbol)                 // Set symbol

{

	symbol = newsymbol;

}



void Stock::Set_price(map<string, double> newPrice)           // Set price

{

	price = newPrice;

}

// Compute AR.

vector<double> Stock::AR(map<string, double>IWB_price)
{
	double r = 0;
	double iwbr = 0;
	vector<double> v, v2;
	for (map<string, double>::iterator itr = price.begin(); itr != prev(price.end()); itr++)
	{
		r = (next(itr)->second - itr->second) / (itr->second);
		v.push_back(r);
		map<string, double>::iterator iter;
		map<string, double>::iterator next_iter;
		iter = IWB_price.find(itr->first);
		next_iter = IWB_price.find(next(itr)->first);
		if (iter != IWB_price.end() && next_iter != IWB_price.end())
		iwbr = (next_iter->second - iter->second) / (iter->second);
		//cout << "CNMCNMCNM:" << "r:" << r << "iwbr:" << iwbr << endl;
		v2.push_back(iwbr);
	}
	return v - v2;
}





