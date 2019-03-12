//
//  RetrieveData.cpp
//  SimpleCurlMac
//
//  Created by Julia on 12/4/18.
//  Copyright © 2018 Song Tang. All rights reserved.
//

#include "RetrieveData.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include "curl.h"
#include <map>
using namespace std;


void RetrieveStockInfo(map<string, vector<string>> &StockInfo)
{

	ifstream fin("Russell3.csv"); //打开文件流操作
	string line;

	map<double, string> StockGroup;

	getline(fin, line); //the first line: Stock,Announcement Date,Estimate EPS,Actual EPS Adjusted,diff,

	while (getline(fin, line)) //begin from the second line
	{   //line:  "COP UN Equity,20170727,-0.018,0.14,-8.777777778,"
		//symbol
		string symbol = line.substr(0, line.find(' '));
		line.erase(0, line.find(',') + 1); // line: "20170727,-0.018,0.14,-8.777777778,"


		//announcedate
		string anndate = line.substr(0, line.find(',')); // anndate ="20170727" ---> "2017-07-27"
		if (anndate.size() == 8) {
			anndate.insert(4, "-");
			anndate.insert(7, "-");
		}
		else cout << anndate;
		line.erase(0, line.find(',') + 1); //line: "-0.018,0.14,-8.777777778,"
		StockInfo[symbol].push_back(anndate);

		//estimate eps
		string estEPS = line.substr(0, line.find(','));
		line.erase(0, line.find(',') + 1); ////line: "0.14,-8.777777778,"
		StockInfo[symbol].push_back(estEPS);

		//actual eps
		string actEPS = line.substr(0, line.find(','));
		line.erase(0, line.find(',') + 1);
		StockInfo[symbol].push_back(actEPS);

		//diff
		string diffEPS = line.substr(0, line.find(','));
		StockInfo[symbol].push_back(diffEPS);

	}
}


void PrintStockInfo(map<string, vector<string>> StockInfo) {
	ofstream fout;
	fout.open("StockInfo.txt");


	for (auto it = StockInfo.begin(); it != StockInfo.end();it++)
	{
		fout << it->first << "  ";
		for (auto itr = (it->second).begin();itr != (it->second).end();itr++)
			fout << *itr << "  ";
		fout << endl;
	}
	fout << "the size of stock is " << StockInfo.size();

	fout.close();
}



void GetGroupData(map<string, map<string, double> > &beat, map<string, map<string, double> > &meet, map<string, map<string, double> > &miss, map<string, map<string, double> > AllStock, map<string, vector<string>> StockInfo)
{
	for (auto it = AllStock.begin();it != AllStock.end();it++)
	{
		string seps = StockInfo[it->first][3];

		double deps;
		stringstream sstr(seps);
		sstr >> deps;

		if (deps > 7)
		{
			beat[it->first] = AllStock[it->first];
		}
		else if (deps < 0)
		{
			miss[it->first] = AllStock[it->first];
		}
		else
		{
			meet[it->first] = AllStock[it->first];
		}
	}

	cout << "size of beat" << beat.size() << endl
		<< "size of meet" << meet.size() << endl
		<< "size of miss" << miss.size() << endl;

}








void PrintGroupInfo(map<string, map<string, double> > group, string filename) {
	ofstream fout;
	fout.open(filename);
	for (auto it = group.begin();it != group.end();it++)
	{
		fout << it->first << "  size of history data is : " << (it->second).size() << endl;
		for (auto itr = it->second.begin();itr != it->second.end();itr++)
			fout << itr->first << "  " << itr->second << "  " << endl;

	}
	fout.close();

}




struct MemoryStruct {
	char *memory;
	size_t size;
};



void *myrealloc(void *ptr, size_t size)
{
	/* There might be a realloc() out there that doesn't like reallocing
	 NULL pointers, so we take care of it here */
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}


size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

string getTimeinSeconds(string Time)
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
	{
		//cout << std::put_time(&t, "%c %Z") << "\n"<< std::mktime(&t) << "\n";
		sprintf(time, "%ld", mktime(&t));
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}


string EndTime(string Time) {
	tm t = { 0 };
	istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> get_time(&t, "%Y-%m-%d"))
	{
		auto timet = mktime(&t);
		//cout << std::put_time(&t, "%c %Z") << "\n" << std::mktime(&t) << "\n";
		timet += (200 * 86400); //200天 1day=86400seconds
		// cout<<timet<<endl;
		sprintf(time, "%ld", timet);
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}

string StartTime(string Time) {
	tm t = { 0 };
	istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> get_time(&t, "%Y-%m-%d"))
	{
		auto timet = mktime(&t);
		//cout << std::put_time(&t, "%c %Z") << "\n" << std::mktime(&t) << "\n";
		timet -= (200 * 86400); //200天 1day=86400seconds
		// cout<<timet<<endl;
		sprintf(time, "%ld", timet);
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}



int  RetrieveMktData(map<string, double> &HistData)
{
	string symbol = "IWB";
	string startTime = getTimeinSeconds("2015-01-01T00:00:00");
	string endTime = getTimeinSeconds("2018-12-31T00:00:00");
	cout << startTime << " - " << endTime << endl;
	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	//file pointer to create file that store the data
	FILE *fp;
	/* declaration of an object CURL */
	CURL *handle;

	/* result of the whole process */
	CURLcode result;
	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
	if (handle)
	{

		static string sCookies, sCrumb;
		if (sCookies.length() == 0 || sCrumb.length() == 0)
		{
			curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");

			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);  //peer certification cannot be authenticated  with known ca certification
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_ENCODING, "");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

			/* perform, then store the expected code in 'result'*/
			result = curl_easy_perform(handle);

			/* Check for errors */
			if (result != CURLE_OK)
			{
				/* if errors have occured, tell us what is wrong with 'result'*/
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			char cKey[] = "CrumbStore\":{\"crumb\":\"";
			char *ptr1 = strstr(data.memory, cKey);
			char *ptr2 = ptr1 + strlen(cKey);
			char *ptr3 = strstr(ptr2, "\"}");
			if (ptr3 != NULL)
				*ptr3 = NULL;

			sCrumb = ptr2;
			fp = fopen("cookies.txt", "r");
			char cCookies[100];
			if (fp) {
				while (fscanf(fp, "%s", cCookies) != EOF);
				fclose(fp);
			}
			else
				cerr << "cookies.txt does not exists" << endl;

			sCookies = cCookies;
			free(data.memory);
			data.memory = NULL;
			data.size = 0;


		}

		string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
		string urlB = "?period1=";
		string urlC = "&period2=";
		string urlD = "&interval=1d&events=history&crumb=";
		string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
		const char * cURL = url.c_str();
		const char * cookies = sCookies.c_str();
		curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
		curl_easy_setopt(handle, CURLOPT_URL, cURL);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
		result = curl_easy_perform(handle);

		/* Check for errors */
		if (result != CURLE_OK)
		{
			/* if errors have occurred, tell us what is wrong with 'result'*/
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}

		stringstream sData;
		sData.str(data.memory);
		string line;
		getline(sData, line); //read the first line
		for (; getline(sData, line); ) //read from the second line to the last line;
		{
			string date = line.substr(0, line.find(","));
			line.erase(line.find_last_of(","), line.size());
			string price_ = line.substr(line.find_last_of(",") + 1, line.size());
			double price;
			stringstream sstr(price_);
			sstr >> price;
			HistData[date] = price;
		}

		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	/* cleanup since you've used curl_easy_init */
	curl_easy_cleanup(handle);

	/* this function releases resources acquired by curl_global_init() */
	curl_global_cleanup();

	ofstream fout;
	fout.open("MktData.txt");
	for (auto it = HistData.begin();it != HistData.end();it++) {
		fout << it->first << "  " << it->second << endl;
	}
	fout.close();
	return 0;
}




int RetrieveAllData(map<string, map<string, double>>&Stock, map<string, vector<string>> StockInfo)
{
	static int count = 0;
	auto itr = StockInfo.begin();

	//file pointer to create file that store the data
	FILE *fp;
	/* declaration of an object CURL */
	CURL *handle;
	/* result of the whole process */
	CURLcode result;
	/* the first functions */
	/* set up the program environment that libcurl needs */
	curl_global_init(CURL_GLOBAL_ALL);
	/* curl_easy_init() returns a CURL easy handle that you're gonna reuse in other easy functions*/
	handle = curl_easy_init();

	/* if everything's all right with the easy handle... */
	if (handle)
	{
		while (true)
		{
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;

			static string sCookies, sCrumb;
			if (sCookies.length() == 0 || sCrumb.length() == 0)
			{
				cout << "find cookies" << endl;
				curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");

				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_ENCODING, "");
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

				/* perform, then store the expected code in 'result'*/
				result = curl_easy_perform(handle);

				/* Check for errors */
				if (result != CURLE_OK)
				{
					/* if errors have occured, tell us what is wrong with 'result'*/
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}


				char cKey[] = "CrumbStore\":{\"crumb\":\"";
				char *ptr1 = strstr(data.memory, cKey);
				char *ptr2 = ptr1 + strlen(cKey);
				char *ptr3 = strstr(ptr2, "\"}");
				if (ptr3 != NULL)
					*ptr3 = NULL;

				sCrumb = ptr2;
				fp = fopen("cookies.txt", "r");
				char cCookies[100];
				if (fp)
				{
					while (fscanf(fp, "%s", cCookies) != EOF);
					fclose(fp);
				}
				else
					cerr << "cookies.txt does not exists" << endl;

				sCookies = cCookies;
				free(data.memory);
				data.memory = NULL;
				data.size = 0;

			}

			if (itr == StockInfo.end())
				break;


			string symbol = itr->first;
			string anndate = (itr->second)[0];
			string startTime = StartTime(anndate);
			string endTime = EndTime(anndate);
			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char * cURL = url.c_str();
			const char * cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
			curl_easy_setopt(handle, CURLOPT_URL, cURL);
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
			result = curl_easy_perform(handle);

			/* Check for errors */
			if (result != CURLE_OK)
			{
				/* if errors have occurred, tell us what is wrong with 'result'*/
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			cout << count << symbol << " " << anndate << endl;
			stringstream sData;
			sData.str(data.memory);
			string line;
			getline(sData, line);
			if (line == "Date,Open,High,Low,Close,Adj Close,Volume")
			{
				cout << "done" << endl;
				for (; getline(sData, line); )
				{
					//cout<<line<<endl;
				   //substract date from line
					string date = line.substr(0, line.find(","));
					//substract adj price from line

					line.erase(line.find_last_of(","), line.size());
					string price_ = line.substr(line.find_last_of(",") + 1, line.size());
					//change price type from string to double
					double price;
					stringstream sstr(price_);
					sstr >> price;
					Stock[symbol][date] = price;
				}

			}
			else { cout << "failed" << endl; }


			itr++;
			count++;
			free(data.memory);


		}


	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	/* cleanup since you've used curl_easy_init */
	curl_easy_cleanup(handle);

	/* this function releases resources acquired by curl_global_init() */
	curl_global_cleanup();


	return 0;
}


void TrimData(map<string, map<string, double>>&Stock, map<string, vector<string>> StockInfo)
{
	auto it = Stock.begin();
	while (true)
	{
		if (it == Stock.end()) break;
		int mark = 0;
		string anndate = StockInfo[it->first][0];
		auto annit = (it->second).find(anndate);
		if (annit != (it->second).end())
		{
			auto temp = annit;
			int after;
			for (after = 0, temp = annit;temp != (it->second).end();temp++, ++after) if (after > 120) break;
			(it->second).erase(temp, (it->second).end());
			if (after == 121)
			{
				int before;
				for (before = 0, temp = annit;temp != (it->second).begin();temp--, ++before) if (before > 120) break;
				(it->second).erase((it->second).begin(), ++temp);
				if (before == 121)
				{
					mark = 1;
				}
				else cout << it->first << " Need more data before announce date " << endl;

			}
			else { cout << it->first << " Need more data after announce date " << endl; }

		}

		else { cout << it->first << " Announce date is not included" << endl; }

		if (mark == 0)
		{
			it = Stock.erase(it);

		}
		else it++;

	}

	auto it2 = Stock.begin();
	while (true)
	{


		if (it2 == Stock.end()) break;
		int mark = 0;
		for (auto itofmap = (it2->second).begin();itofmap != (it2->second).end();itofmap++)
		{
			if (itofmap->second == 0.0)
				mark = 1; break;
		}

		if (mark == 1) {
			cout << it2->first << "stock price is zero " << endl;
			it2 = Stock.erase(it2);
		}
		else { it2++; }


	}



}



