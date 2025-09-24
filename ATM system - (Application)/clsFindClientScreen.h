#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsFindClientScreen : public clsScreen
{
private:
	static void _FindClient()
	{
		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(AccountNumber);
		client.Print();
	}
	
public:
	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("    Find Client");
		_FindClient();
	}

};

