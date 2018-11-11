#include "pch.h"
#include "MyMethod.h"


using namespace std;

void MyMethod::Init()
{

	MyInstrument *mi;
	string key;

	
	
	key = "m1901";
	mi = new MyInstrument(key);
	instrumentIDs.insert(pair<string, MyInstrument>(key, *mi));

	key = "m1903";
	mi = new MyInstrument(key);
	instrumentIDs.insert(pair<string, MyInstrument>(key, *mi));
}
void MyMethod::DoMethod(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

}