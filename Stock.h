#ifndef Stock_h
#define Stock_h

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Stock
{
private:
	string symbol;
	map<string, double>price;

public:
	Stock();
	Stock(string symbol_, map<string, double>price_);
	Stock(const Stock& s);
	~Stock();

	// Selectors
	string Get_symbol() const;
	map<string, double> Get_price() const;
	string Get_announcement_date();

	// Modifiers
	void Set_symbol(string newsymbol);
	void Set_price(map<string, double>newprice);

	//Compute AR
	vector<double>AR(map<string, double>IWB_price);
};
#endif
