// MyCtp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"
#include <iostream>
//#include <string>
#include <unordered_map>
using namespace std;

// 链接库
#pragma comment (lib, "20180109_tradeapi64_windows/lib/thostmduserapi.lib")
#pragma comment (lib, "20180109_tradeapi64_windows/lib/thosttraderapi.lib")
#pragma comment(lib,"ws2_32.lib")



//// ---- 全局变量 ---- //
//// 公共参数
//TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
//TThostFtdcInvestorIDType gInvesterID = "";                         // 投资者账户名
//TThostFtdcPasswordType gInvesterPassword = "";                     // 投资者密码
//
//// 行情参数
//CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
//char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址
//const char *g_pInstrumentID[] = { "TF1706", "zn1705", "cs1801", "CF705" }; // 行情合约代码列表，中、上、大、郑交易所各选一种
//int instrumentNum = 4;                                             // 行情合约订阅数量
//unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表
//
//// 交易参数
//CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址
//TThostFtdcInstrumentIDType g_pTradeInstrumentID = "m1709";         // 所交易的合约代码
//TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
//TThostFtdcPriceType gLimitPrice = 2818;                            // 交易价格

const char* tradeAndMarketUrl = "tcp://180.168.146.187:10000";
const char* tradePort = "10000";
const char* marketPort = "10010";

const char* mdflowpath = "F:\exchange\MyCtp\flowpath";

CThostFtdcMdApi *api;
int requestId = 0;


//登录
int login(CThostFtdcMdApi *api)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, "9999");
	strcpy_s(req.UserID, "129239");
	strcpy_s(req.Password, "HELICOPTER");
	int ret = api->ReqUserLogin(&req, ++requestId);
	std::cout << "login ret:" << ret<<endl;
	return ret;
}


class MarketDataCollector :public CThostFtdcMdSpi
{
public:
	void OnFrontConnected()
	{
		std::cout << "connected!" << endl;

		login(api);
	}

	void OnFrontDisconnected(int nReason) 
	{
		//printf("disconnected!reason:s%",nReason);
		std::cout << "disconnected!reason!" << nReason;
	};

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		cout <<"登录结果："<< pRspInfo->ErrorID <<endl<<"登录返回消息："<< pRspInfo->ErrorMsg << endl;
	};

};

//连接
CThostFtdcMdApi* link()
{

	api = CThostFtdcMdApi::CreateFtdcMdApi("", false);
	MarketDataCollector *spi = new MarketDataCollector();
	api->RegisterSpi(spi);
	api->RegisterFront(const_cast<char*>(tradeAndMarketUrl));
	api->Init();
	api->Join();

	return api;
}

int main()
{
    //std::cout << "Hello World!\n"; 

	
	link();

}





