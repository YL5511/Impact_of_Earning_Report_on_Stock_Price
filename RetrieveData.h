//
//  RetrieveData.hpp
//  SimpleCurlMac
//
//  Created by Julia on 12/4/18.
//  Copyright © 2018 Song Tang. All rights reserved.
//

#ifndef RetrieveData_h
#define RetrieveData_h

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
using namespace std;

void RetrieveStockInfo(map<string, vector<string>> &StockInfo);
void PrintStockInfo(map<string, vector<string>> StockInfo);

int RetrieveAllData(map<string, map<string, double>>&Stock, map<string, vector<string>> StockInfo);
void TrimData(map<string, map<string, double>>&Stock, map<string, vector<string>> Stockinfo);


void GetGroupData(map<string, map<string, double> > &beat, map<string, map<string, double> > &meet, map<string, map<string, double> > &miss, map<string, map<string, double> > AllStock, map<string, vector<string>> StockInfo);
void PrintGroupInfo(map<string, map<string, double> > group, string filename);

int RetrieveMktData(map<string, double> &HistData);


#endif /* RetrieveData_h */


