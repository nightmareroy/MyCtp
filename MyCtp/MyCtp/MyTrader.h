#pragma once
//#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
//#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"

#include "MyMethod.h"

class MyTrader :public CThostFtdcTraderSpi
{
public:
	const char* tradeUrl = "tcp://180.168.146.187:10000";

	const char* mdflowpath = "F:\exchange\MyCtp\flowpath";

	const char* g_pInstrumentID[2] = { "m1901" ,"m1903"};

	CThostFtdcTraderApi *myTradeApi;
	int requestId = 0;

	void Init(MyMethod *myMethod);

	void Link();

	void Authenticate();

	void Login();

	void QrySettlementInfo();

	void SettlementInfoConfirm();

	void QryInvestorPosition();

	void QryInvestorPositionDetail();

	void OrderInsert();

	void ParkedOrderInsert();

	void ParkedOrder();

	void QryOrder();

private:
	MyMethod *myMethod;

	void OrderDispatcher();

	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnFrontConnected();

	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者结算结果响应
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者结算结果确认响应
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询结算信息确认响应
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询投资者持仓响应
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓明细响应
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///预埋单录入请求响应
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询预埋单响应
	void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单通知
	void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///请求查询报单响应
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///成交通知
	void OnRtnTrade(CThostFtdcTradeField *pTrade);
};