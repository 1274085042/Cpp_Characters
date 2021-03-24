#include "ConfigParser.h"

int main()
{
	ConfigParser cp;
	cp.ParseConfig("setup.config");

	string str1;
	cp.GetStringValue("stream.ch0", str1);
	cout << str1 << endl;

	int i1;
	cp.GetIntValue("SystemConfig.deviceId", i1);
	cout << i1 << endl;

	bool b1;
	cp.GetBoolValue("PostProcess.writeDetResult", b1);
	cout << b1 << endl;

	float f1;
	cp.GetFloatValue("VideoDecoder.resizeWidth", f1);
	cout << f1 << endl;

	double d1;
	cp.GetDoubleValue("VideoDecoder.resizeHeight", d1);
	cout << d1 << endl;

	vector<uint32_t> v1;
	bool b2=cp.GetVectorUint32Value("Stream", v1);
	for (auto i : v1)
	{
		cout << i << " ";
	}

}