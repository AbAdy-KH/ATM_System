#pragma once
#include<iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
	static void _ShowCurrentUser()
	{
		cout << "User: ";
		cout << currentUser.UserName << endl;
	}
	static void _ShowCurrentDate()
	{
		clsDate currentDate;
		cout << "Date: ";
		currentDate.Print();
	}
	static void _DrawScreenHeader(string title, string subtitle = "")
	{
		cout << "User: " << currentUser.UserName << endl;
		cout << "Date: " << clsDate::DateToString(clsDate()) << endl;

		cout << "==========================\n";
		cout << title << '\n';
		if (subtitle != "")
		{
			cout << "\t" << subtitle << '\n';
		}
		cout << "==========================\n";
	}
	static bool _CheckAccessRights(clsUser::enPermissions permission)
	{
		if (currentUser.CheckAccessPermission(permission))
			return true;
		else
		{
			cout << "======================================";
			cout << "\n  Access Denied! Contact your Admin\n";
			cout << "======================================\n";

			return false;
		}
	}
};

