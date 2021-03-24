#include "ConfigParser.h"

const char COMMENT_CHAR = '#';

// Breaks the string at separator and return a vector of strings
void Split(const string& inString, vector<string>& outVector, const char delimiter)
{
	stringstream ss(inString);
	string item;
	while (getline(ss, item, delimiter))
	{
		outVector.emplace_back(item);
	}
}

inline void ConfigParser::Trim(string& str)
{
	/*
	* erase( const_iterator first, const_iterator last ) 移除范围[first, last)中的字符
	* 
	* constexpr InputIt find_if( InputIt first, InputIt last, UnaryPredicate p )
	*	参数：first, last - 要检查的元素范围
	*		  p - 一元谓词，返回类型是bool的callable
	*	返回值：返回首个p(v)为true的迭代器
	* 
	* template< class Predicate > constexpr std::unary_negate<Predicate> not1(const Predicate& pred)
	*	参数：pred - 一元谓词
	*	返回值：类型为unary_negate<Predicate>的函数对象，也就是一元谓词逻辑补的包装函数对象、
	* 
	* template< class Arg, class Result > std::pointer_to_unary_function<Arg,Result> ptr_fun(f)
	*	参数： f - 函数指针
	*	返回值： 包装f的函数对象
	* 
	* int isspace( int ch ) 如果是空白字符，返回非零值，否则返回零
	*/
	//str.erase(str.begin(), find_if(str.begin(), str.end(), not1(isspace)));
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun(isspace))));
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun(isspace))).base(), str.end());
}

bool ConfigParser::ParseConfig(const string& filename)
{
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		cout << "Cannot read config file!" << endl;
		return false;
	}

	string line, newline;
	int startPos, endPos, pos;
	while (getline(inFile, line))  //getline()定义于头文件<string>
	{
		if (line.empty())
		{
			continue;
		}

		startPos = 0;
		endPos = line.size() - 1;

		pos = line.find(COMMENT_CHAR);  //find the position of comment
		if (pos != -1)
		{
			if (pos == 0)	//该行是注释
			{
				continue;
			}

			endPos = pos - 1;
		}

		newline = line.substr(startPos, (endPos - startPos) + 1);
		pos = newline.find('=');

		if (pos == -1)
		{
			continue;
		}

		string na = newline.substr(0, pos);
		Trim(na);
		string value = newline.substr(pos + 1, endPos - (pos + 1) + 1);
		Trim(value);
		configData_.insert(make_pair(na, value));

	}

	return  true;
}


bool ConfigParser::GetStringValue(const string& name, string& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}
	value = configData_.find(name)->second;
	return true;
}

bool ConfigParser::GetIntValue(const string& name, int& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}

	string str = configData_.find(name)->second;
	if (!(stringstream(str) >> value))
	{
		return false;	
	}

	return true;
}

bool ConfigParser::GetBoolValue(const string& name, bool& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}

	string str = configData_.find(name)->second;
	if (str == "true")
	{
		value = true;
	}
	else if (str == "false")
	{
		value = false;
	}
	else
	{
		return false;
	}
	return true;
}

bool ConfigParser::GetFloatValue(const string& name, float& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}

	string str = configData_.find(name)->second;
	if (!(stringstream(str) >> value))
	{
		return false;
	}

	return true;
}

bool ConfigParser::GetDoubleValue(const string& name, double& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}

	string str = configData_.find(name)->second;
	if (!(stringstream(str) >> value))
	{
		return false;
	}

	return true;
}

// Array like 1,2,4,8  split by ","
bool ConfigParser::GetVectorUint32Value(const string& name, vector<uint32_t>& value)
{
	if (configData_.count(name) == 0)
	{
		return false;
	}

	string str = configData_.find(name)->second;
	vector<string> splits;
	Split(str, splits, ',');

	uint32_t v = 0;
	for (auto i : splits)
	{
		if (!i.empty())
		{
			stringstream ss;
			ss << i;
			ss >> v;
			value.emplace_back(v);
		}
	}

	return true;
}