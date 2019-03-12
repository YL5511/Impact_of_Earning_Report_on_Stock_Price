#include "RetrieveData.h"
#include "SelectStock.h"
#include "Overloading.h"
#include "Stock.h"
#include "Value_Calculation.h"
#include "Excelplot.h"
#include "Exceldriver\stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

typedef vector<vector<double>> Matrix2D;
typedef vector<Matrix2D> Matrix3D;
typedef vector<Matrix3D> Matrix4D;
const int groupNumber = 3, dataNumber = 2, repeatNumber = 5, stockNumber = 100, dayNumber = 240;

vector<string> putSymbolInVector(map<string, map<string, double>> group)
{
    vector<string> name(group.size());
    int i = 0;
    for (map<string, map<string, double>>::iterator itr = group.begin();itr != group.end();itr++)
    {
        name[i] = itr->first;
        i++;
    }
    return name;
}

int main() {
    map<string, double> MktData;
    RetrieveMktData(MktData);
    
    map<string, vector<string>> StockInfo;
    RetrieveStockInfo(StockInfo);
    
    map<string, map<string, double>> AllStock;
    RetrieveAllData(AllStock, StockInfo);
    TrimData(AllStock, StockInfo);
    
    vector<map<string, map<string, double>>> information(groupNumber);
    GetGroupData(information[0], information[1], information[2], AllStock, StockInfo);
    
    vector<vector<string>> symbolMatrix(groupNumber);
    for (int i = 0; i < groupNumber; i++) symbolMatrix[i] = putSymbolInVector(information[i]);
    
    map<string, Stock> stockMap;
    Matrix3D finalMatrix(groupNumber);
    Matrix4D combinedMatrix(groupNumber);
    for (int i = 0; i < groupNumber; i++) combinedMatrix[i].resize(dataNumber);
    
    for (int i = 0; i < repeatNumber; i++)
    {
        for (int j = 0; j < groupNumber; j++)
        {
            vector<string> selected = SelectStock(symbolMatrix[j], stockNumber);
            Matrix2D AR(stockNumber);
            
            for (int k = 0; k < stockNumber; k++)
            {
                string symbol = selected[k];
                if (stockMap.count(symbol)) AR[k] = stockMap[symbol].AR(MktData);
                else {
                    Stock stock(symbol, information[j][symbol]);
                    stockMap[symbol] = stock;
                    AR[k] = stock.AR(MktData);
                }
            }
            vector<double> AAR = AAR_Calculation(AR);
            combinedMatrix[j][0].push_back(AAR);
            combinedMatrix[j][1].push_back(CAAR_Calculation(AAR));
        }
    }
    
    for (int i = 0; i < groupNumber; i++)
    {
        for (int j = 0; j < dataNumber; j++) {
            vector<double> average(dayNumber);
            for (int k = 0; k < dayNumber; k++)
            {
                for (int l = 0; l < repeatNumber; l++) average[k] += combinedMatrix[i][j][l][k];
                average[k] /= repeatNumber;
            }
            finalMatrix[i].push_back(average);
        }
    }
    
    while (true)
    {
        cout << endl << endl << "--------------------------------menu--------------------------------" << endl << endl
        << "Please press 1 to retrieve historical price data for all stocks." << endl
        << "Please press 2 to pull information for one stock from one group." << endl
        << "Please press 3 to show AAR or CAAR for one group." << endl
        << "Please press 4 to show the Excel graph with CAAR for all 3 groups." << endl
        << "Please press 5 to exit the program." << endl << endl;
        
        string response;
        cin >> response;
        if (response == "2")
        {
            string stockSymbol;
            cout << "Please enter the stock symbol:" << endl;
            cin >> stockSymbol;
            
            if (AllStock.count(stockSymbol) == 0) cout << endl << "Stock not included." << endl;
            else {
                vector<string> stockInf = StockInfo[stockSymbol];
                cout << endl << "Stock announcement date:   " << stockInf[0] << endl;
                cout << "Stock estimated EPS:   " << stockInf[1] << endl;
                cout << "Stock actual EPS:  " << stockInf[2] << endl;
                
                map<string, double> price = AllStock[stockSymbol];
                cout << endl << "stock price:" << endl;
                for (map<string, double>::iterator it = price.begin(); it != price.end(); it++)
                    cout << it->first << "   " << it->second << endl;
            }
        }
        else if (response == "3")
        {
            string dataType;
            cout << "Please enter the data type (AAR or CAAR):" << endl;
            cin >> dataType;
            
            if (dataType != "AAR" && dataType != "CAAR") cout << endl << "Wrong data type." << endl;
            else {
                int data;
                if (dataType == "AAR") data = 0;
                else data = 1;
                
                string groupName;
                cout << "Please enter the group name (beat, meet, or miss):" << endl;
                cin >> groupName;
                
                if (groupName != "beat" && groupName != "meet" && groupName != "miss") cout << endl << "Wrong group name." << endl;
                else {
                    int group;
                    if (groupName == "beat") group = 0;
                    else if (groupName == "meet") group = 1;
                    else group = 2;
                    
                    cout << endl << "The averaged " << dataType << " for group " << groupName << " is:" << endl;
                    for (int i = 0; i < dayNumber - 1; i++) cout << finalMatrix[group][data][i] << ",  ";
                    cout << finalMatrix[group][data][dayNumber - 1] << endl;
                }
            }
        }
        else if (response == "4") Excelplot(finalMatrix[0][1], finalMatrix[1][1], finalMatrix[2][1]);
        else if (response == "5") break;
    }
    return 0;
}
