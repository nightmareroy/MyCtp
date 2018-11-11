#include "pch.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcMdApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcTraderApi.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiDataType.h"
#include "20180109_tradeapi64_windows/header/ThostFtdcUserApiStruct.h"
#include <iostream>
//#include <string>
#include <unordered_map>

#include "MyTrader.h"
using namespace std;

#pragma comment (lib, "20180109_tradeapi64_windows/lib/thostmduserapi.lib")
#pragma comment (lib, "20180109_tradeapi64_windows/lib/thosttraderapi.lib")
#pragma comment(lib,"ws2_32.lib")


///public
//��ʼ��
void MyTrader::Init(MyMethod *myMethod)
{
	this->myMethod = myMethod;
}

//����
void MyTrader::Link()
{
	myTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	myTradeApi->RegisterSpi(this);
	myTradeApi->RegisterFront(const_cast<char*>(tradeUrl));
	myTradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
	myTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	myTradeApi->Init();
	myTradeApi->Join();

}

//��¼
void MyTrader::Login()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, "9999");
	strcpy_s(req.UserID, "129239");
	strcpy_s(req.Password, "HELICOPTER");
	int ret = myTradeApi->ReqUserLogin(&req, ++requestId);
	cout << "login ret:" << ret << endl;
}


//��֤
void MyTrader::Authenticate()
{
	CThostFtdcReqAuthenticateField req;
	memset(&req, 0, sizeof(req));
	int ret = myTradeApi->ReqAuthenticate(&req, ++requestId);

}

//�����ѯͶ���߽�����
void MyTrader::QrySettlementInfo()
{
	CThostFtdcQrySettlementInfoField req;
	memset(&req, 0, sizeof(req));
	//strcpy_s(req.BrokerID, "9999");
	//strcpy_s(req.UserID, "129239");
	//strcpy_s(req.Password, "HELICOPTER");
	int ret = myTradeApi->ReqQrySettlementInfo(&req, ++requestId);
}

//Ͷ���߽�����ȷ��
void MyTrader::SettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	//strcpy_s(req.BrokerID, "9999");
	//strcpy_s(req.UserID, "129239");
	//strcpy_s(req.Password, "HELICOPTER");
	myTradeApi->ReqSettlementInfoConfirm(&req, ++requestId);
}

//�����ѯͶ���ֲ߳�
void MyTrader::QryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField *req = new CThostFtdcQryInvestorPositionField();
	//memset(&req, 0, sizeof(req));
	cout<<myTradeApi->ReqQryInvestorPosition(req, ++requestId)<<endl;
}

//�����ѯͶ���ֲ߳���ϸ
void MyTrader::QryInvestorPositionDetail()
{
	CThostFtdcQryInvestorPositionDetailField *req = new CThostFtdcQryInvestorPositionDetailField();
	cout << myTradeApi->ReqQryInvestorPositionDetail(req, ++requestId) << endl;
}

//����¼��(����)
void MyTrader::OrderInsert()
{
	CThostFtdcInputOrderField *req = new CThostFtdcInputOrderField();
	strcpy_s(req->BrokerID, "9999");
	strcpy_s(req->InvestorID, "129239");
	strcpy_s(req->InstrumentID, "m1901");
	strcpy_s(req->OrderRef, "");


	req->Direction = THOST_FTDC_D_Buy;
	req->CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	req->CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	req->VolumeTotalOriginal = 1;
	req->VolumeCondition = THOST_FTDC_VC_AV;
	req->MinVolume = 1;
	req->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	req->IsAutoSuspend = 0;
	req->UserForceClose = 0;

	req->ContingentCondition = THOST_FTDC_CC_LastPriceLesserThanStopPrice;
	req->OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	req->LimitPrice = 2500;
	req->TimeCondition = THOST_FTDC_TC_GTC;


	cout << myTradeApi->ReqOrderInsert(req, ++requestId) << endl;
}

//Ԥ��¼��
void MyTrader::ParkedOrderInsert()
{
	CThostFtdcParkedOrderField *req = new CThostFtdcParkedOrderField();
	strcpy_s(req->BrokerID, "9999");
	strcpy_s(req->InvestorID, "129239");
	strcpy_s(req->InstrumentID, "m1901");
	strcpy_s(req->OrderRef, "");

	req->Direction = THOST_FTDC_D_Buy;
	req->CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	req->CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	req->VolumeTotalOriginal = 1;
	req->VolumeCondition = THOST_FTDC_VC_AV;
	req->MinVolume = 1;
	req->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	req->IsAutoSuspend = 0;
	req->UserForceClose = 0;

	req->ContingentCondition = THOST_FTDC_CC_ParkedOrder;
	req->OrderPriceType = THOST_FTDC_OPT_AnyPrice;
	req->LimitPrice = 2500;
	req->TimeCondition = THOST_FTDC_TC_GFD;
	cout << myTradeApi->ReqParkedOrderInsert(req, ++requestId) << endl;
}

//�����ѯԤ��
void MyTrader::ParkedOrder()
{
	CThostFtdcQryParkedOrderField *req = new CThostFtdcQryParkedOrderField();
	strcpy_s(req->BrokerID, "9999");
	strcpy_s(req->InvestorID, "129239");
	strcpy_s(req->InstrumentID, "m1901");

	cout << myTradeApi->ReqQryParkedOrder(req, ++requestId) << endl;
}

//�����ѯ����
void MyTrader::QryOrder()
{
	CThostFtdcQryOrderField *req = new CThostFtdcQryOrderField();
	cout << myTradeApi->ReqQryOrder(req, ++requestId) << endl;
}


//private
void MyTrader::OrderDispatcher()
{
	int orderId;
	cout << "������ָ�";
	cin >> orderId;

	switch (orderId)
	{
	case 0://�����ѯͶ���߽�����
		QrySettlementInfo();
		break;
	case 1://Ͷ���߽�����ȷ��
		SettlementInfoConfirm();
		break;
	case 2://�����ѯͶ���ֲ߳�
		QryInvestorPosition();
		break;
	case 3://�����ѯͶ���ֲ߳���ϸ
		QryInvestorPositionDetail();
		break;
	case 4://����¼��
		OrderInsert();
		break;
	case 5://Ԥ��¼��
		ParkedOrderInsert();
		break;
	case 6://�����ѯԤ��
		ParkedOrder();
		break;
	case 7://�����ѯ����
		QryOrder();
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	default:
		return;
	}
}

void MyTrader::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "error id:" << pRspInfo->ErrorID << "error msg:" << pRspInfo->ErrorMsg << endl;
	OrderDispatcher();
}

void MyTrader::OnFrontConnected()
{
	//���Ӻ��½
	Login();
}

void MyTrader::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "authenticate rsp:" << pRspInfo->ErrorMsg << endl;
	OrderDispatcher();
};

void MyTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "login rsp:" << pRspInfo->ErrorMsg << endl;
	OrderDispatcher();
};

void MyTrader::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pSettlementInfo->Content << endl;
	if (bIsLast)
	{
		OrderDispatcher();
	}
	
}

void MyTrader::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "settlement info confirm rsp:" << pSettlementInfoConfirm->ConfirmTime << endl;
	OrderDispatcher();
}

void MyTrader::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "qry settlement info confirm rsp:" << pSettlementInfoConfirm->ConfirmTime << endl;
	OrderDispatcher();
}

void MyTrader::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "qry investor position rsp:" << pInvestorPosition->UseMargin << endl;

	string key = pInvestorPosition->InstrumentID;
	MyInstrument myInstrument = myMethod->instrumentIDs[key];
	myInstrument.Position = pInvestorPosition->Position;
	myInstrument.TodayPosition = pInvestorPosition->TodayPosition;
	/*myInstrument.WantPosition*/
	//OrderDispatcher();
}

void MyTrader::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "qry investor position detail rsp:" << pInvestorPositionDetail->Direction << endl;
	OrderDispatcher();
}

void MyTrader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "��������  insert order rsp:" << pRspInfo->ErrorMsg << endl;
	OrderDispatcher();
}

void MyTrader::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	cout << "�������ύ rtn order rsp:" << pOrder->OrderStatus << endl;
	//OrderDispatcher();
}

void MyTrader::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "insert parked order rsp:" << pRspInfo->ErrorMsg << endl;
	OrderDispatcher();
}

void MyTrader::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "qry parked order rsp:" << pParkedOrder->AccountID << endl;
	OrderDispatcher();
}

void MyTrader::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "qry parked order rsp:" << pOrder->LimitPrice << endl;

	string key = pOrder->InstrumentID;
	MyInstrument myInstrument = myMethod->instrumentIDs[key];
	//myInstrument.WantPosition = pOrder->AccountID;
}

void MyTrader::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}