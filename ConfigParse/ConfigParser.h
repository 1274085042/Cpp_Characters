#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>


using namespace std;

class ConfigParser
{
private:
	map<string, string> configData_;

public:
	inline void Trim(string& str);

	//Read the config file and save the useful information with the key-value pairs format in configData_
	bool ParseConfig(const string& filename);
	bool GetStringValue(const string& name, string& value);
	bool GetIntValue(const string& name, int& value);
	bool GetBoolValue(const string& name, bool& value);
	bool GetFloatValue(const string& name, float& value);
	bool GetDoubleValue(const string& name, double& value);
	//Get vector by key, split by ","
	bool GetVectorUint32Value(const string& name, vector<uint32_t>& value);
};
