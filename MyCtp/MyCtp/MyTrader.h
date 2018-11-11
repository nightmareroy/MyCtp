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

	///�����ѯͶ���߽�������Ӧ
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ϣȷ����Ӧ
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///�����ѯͶ���ֲ߳���Ӧ
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ԥ��¼��������Ӧ
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯԤ����Ӧ
	void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����֪ͨ
	void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�����ѯ������Ӧ
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade);
};