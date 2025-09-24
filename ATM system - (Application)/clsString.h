#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class clsString
{
private:


public:

	static vector<string> Split(string Line, string Seperator)
	{
		vector<string> vClient;

		short pos = 0;
		pos = Line.find(Seperator);

		string SubString;

		while (pos != Line.npos)
		{
			SubString = Line.substr(0, pos);
			vClient.push_back(SubString);

			Line.erase(0, pos + Seperator.length());

			pos = Line.find(Seperator);
		}

		if (Line != "")
		{
			vClient.push_back(Line);
		}

		return vClient;
	}
	static string UpperAllString(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (islower(s[i]))
				s[i] = toupper(s[i]);
		}

		return s;
	}
};

