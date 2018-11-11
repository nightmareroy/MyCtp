#include "pch.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"
#include <iostream>
//#include <string>
#include <unordered_map>

#include "MyMarketData.h"
#include "MyMethod.h"
using namespace std;

#pragma comment (lib, "20180109_tradeapi64_windows/lib/thostmduserapi.lib")
#pragma comment (lib, "20180109_tradeapi64_windows/lib/thosttraderapi.lib")
#pragma comment(lib,"ws2_32.lib")






///public
//初始化
void MyMarketData::Init(MyMethod *myMethod)
{
	MyMarketData::myMethod = myMethod;
}


//连接
void MyMarketData::Link()
{

	myMarketDataApi = CThostFtdcMdApi::CreateFtdcMdApi("", false);
	myMarketDataApi->RegisterSpi(this);
	myMarketDataApi->RegisterFront(const_cast<char*>(marketUrl));
	myMarketDataApi->Init();
	myMarketDataApi->Join();

}

//登录
void MyMarketData::Login()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, "9999");
	strcpy_s(req.UserID, "129239");
	strcpy_s(req.Password, "HELICOPTER");
	int ret = myMarketDataApi->ReqUserLogin(&req, ++requestId);
	cout << "login ret:" << ret << endl;
}

//订阅行情
void MyMarketData::SubscribeMarketData()
{
	int ret = myMarketDataApi->SubscribeMarketData(const_cast<char**>(g_pInstrumentID), 1);

	cout << "subscribe ret:" << ret << endl;

}


///private

void MyMarketData::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "error id:" << pRspInfo->ErrorID << "error msg:" << pRspInfo->ErrorMsg << endl;
};

void MyMarketData::OnFrontConnected()
{
	cout << "connected!" << endl;

	

	MyMarketData::Login();
}

void MyMarketData::OnFrontDisconnected(int nReason)
{
	//printf("disconnected!reason:s%",nReason);
	cout << "disconnected! reason!" << nReason;
};

void MyMarketData::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "登录结果：" << pRspInfo->ErrorID << endl << "登录返回消息：" << pRspInfo->ErrorMsg << endl;

	SubscribeMarketData();
};

void MyMarketData::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "订阅结果：" << pRspInfo->ErrorID << endl;
};

void MyMarketData::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	cout << "订阅数据：" << pDepthMarketData->AskPrice1 << endl;

	myMethod->DoMethod(pDepthMarketData);


};

//class MarketDataCollector :public CThostFtdcMdSpi
//{
//public:
//	//const char* tradeAndMarketUrl = "tcp://180.168.146.187:10010";
//	//const char* tradePort = "10000";
//	//const char* marketPort = "10010";
//
//	//const char* mdflowpath = "F:\exchange\MyCtp\flowpath";
//
//	//const char* g_pInstrumentID[1] = { "m1901" };
//
//	//CThostFtdcMdApi *api;
//	//int requestId = 0;
//
//
//	
//
//
//};