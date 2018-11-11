#pragma once
#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"

#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

class MyInstrument
{
public:
	MyInstrument()
	{

	};
	MyInstrument(string InstrumentID)
	{
		//this->InstrumentID = InstrumentID;
		strcpy_s(this->InstrumentID, InstrumentID.data());
		Position = 0;
		WantPosition = 0;
	};

	TThostFtdcInstrumentIDType	InstrumentID;
	int Position;
	int TodayPosition;
	int WantPosition;

	queue<list<int>> priceQueue;
};

class MyMethod
{
public:
	//MyInstrument *myInstruments;
	unordered_map<string, MyInstrument> instrumentIDs;

	void Init();
	void DoMethod(CThostFtdcDepthMarketDataField *pDepthMarketData);

	
	//const char *g_pInstrumentID[] = { "m1901","m1903" };
};

