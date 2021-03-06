#include "Util.h"
#include <sstream>

using namespace v8;
using namespace std;
using namespace tns;

string Util::JniClassPathToCanonicalName(const string& jniClassPath)
{
	std::string canonicalName;

	const char prefix = jniClassPath[0];

	std::string rest;
	int lastIndex;

	switch (prefix)
	{
		case 'L':
			canonicalName = jniClassPath.substr(1, jniClassPath.size() - 2);
			std::replace(canonicalName.begin(), canonicalName.end(), '/', '.');
			std::replace(canonicalName.begin(), canonicalName.end(), '$', '.');
			break;

		case '[':
			canonicalName = jniClassPath;
			lastIndex = canonicalName.find_last_of("[");
			rest = canonicalName.substr(lastIndex + 1);
			canonicalName = canonicalName.substr(0, lastIndex + 1);
			canonicalName.append(JniClassPathToCanonicalName(rest));
			break;

		default:
			// TODO:
			canonicalName = jniClassPath;
			break;
	}
	return canonicalName;
}

void Util::SplitString(const string& str, const string& delimiters, vector<string>& tokens)
{
	string::size_type delimPos = 0, tokenPos = 0, pos = 0;

	if (str.length() < 1)
		return;

	while (true)
	{
		delimPos = str.find_first_of(delimiters, pos);
		tokenPos = str.find_first_not_of(delimiters, pos);

		if (string::npos != delimPos)
		{
			if (string::npos != tokenPos)
			{
				if (tokenPos < delimPos)
				{
					tokens.push_back(str.substr(pos, delimPos - pos));
				}
				else
				{
					tokens.push_back("");
				}
			}
			else
			{
				tokens.push_back("");
			}
			pos = delimPos + 1;
		}
		else
		{
			if (string::npos != tokenPos)
			{
				tokens.push_back(str.substr(pos));
			}
			else
			{
				tokens.push_back("");
			}
			break;
		}
	}
}

bool Util::EndsWith(const string& str, const string& suffix)
{
	bool res = false;
	if (str.size() > suffix.size())
	{
		res = equal(suffix.rbegin(), suffix.rend(), str.rbegin());
	}
	return res;
}

string Util::ConvertFromJniToCanonicalName(const std::string& name)
{
	string converted = name;
	replace(converted.begin(), converted.end(), '/', '.');
	return converted;
}

string Util::ConvertFromCanonicalToJniName(const std::string& name)
{
	string converted = name;
	replace(converted.begin(), converted.end(), '.', '/');
	return converted;
}

void Util::ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}