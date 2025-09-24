#pragma once

#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;


class clsDeleteClientScreen : public clsScreen
{
private:
	static void _DeleteClient()
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

		cout << "\nAre you sure you want to delete this client y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				client.Print();
			}
			else
				cout << "\nError Client Was not Deleted\n";
		}
	}
public:
	static void ShowDeleteClientScreen()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("      Delete Client");
		_DeleteClient();
	}

};

