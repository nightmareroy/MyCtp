#pragma once
//#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"

#include "MyMethod.h"

class MyMarketData :public CThostFtdcMdSpi
{
public:
	const char* marketUrl = "tcp://180.168.146.187:10010";

	const char* mdflowpath = "F:\exchange\MyCtp\flowpath";

	const char* g_pInstrumentID[1] = { "m1901" };

	CThostFtdcMdApi *myMarketDataApi;
	int requestId = 0;

	void Init(MyMethod *myMethod);

	void Link();

	void Login();

	void SubscribeMarketData();

private:
	MyMethod *myMethod;

	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnFrontConnected();

	void OnFrontDisconnected(int nReason);

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

};