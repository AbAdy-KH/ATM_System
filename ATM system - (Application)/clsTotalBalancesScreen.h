#pragma once
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"
using namespace std;
class clsTotalBalancesScreen
{
private:
	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << "| " << setw(17) << left << Client.AccountNumber();
		cout << "| " << setw(25) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance << "|";
	}

public:
	static void ShowTotalBalances()
	{
		vector<clsBankClient> vC = clsBankClient::GetClientList();

		cout << "\t      Balances List (" << vC.size() << ") Client(s)\n";
		cout << "=========================================";
		cout << "====================" << endl;
		cout << "| " << left << setw(17) << "Accout Number";
		cout << "| " << left << setw(25) << "Client Name";
		cout << "| " << left << setw(12) << "Balance" << "|";
		cout << "\n=========================================";
		cout << "====================" << endl;

		if (vC.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
		{
			for (clsBankClient& Client : vC)
			{
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
		}

		cout << "=========================================";
		cout << "====================" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances(vC);
		cout << " Total Balances = " << TotalBalances << endl;
		cout << "(" << clsUtil::NumberToText(TotalBalances) << ")" << endl;

		cout << "=========================================";
		cout << "====================" << endl;
	}
};

