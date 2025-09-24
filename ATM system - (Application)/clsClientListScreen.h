#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient client)
	{
		cout << left << setw(17) << "|" + client.AccountNumber();
		cout << left << setw(25) << "|" + client.FullName();
		cout << left << setw(15) << "|" + client.Phone;
		cout << left << setw(20) << "|" + client.Email;
		cout << left << setw(10) << "|" + client.PinCode;
		cout << left << setw(12) << "|" + to_string(client.AccountBalance) << "|";
	}
public:
	static void ShowClientsList()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}



		vector<clsBankClient> vC = clsBankClient::GetClientList();

		cout << "\t\t\t\t Clients List (" << vC.size() << ") Client(s)\n";
		cout << "==========================================================";
		cout << "==========================================\n";
		cout << left << setw(17) << "|Account Number";
		cout << left << setw(25) << "|Client Name";
		cout << left << setw(15) << "|Phone";
		cout << left << setw(20) << "|Email";
		cout << left << setw(10) << "|PIN Cide";
		cout << left << setw(12) << "|Balance" << "|";
		cout << endl;
		cout << "==========================================================";
		cout << "==========================================\n";

		if (vC.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
		{
			for (clsBankClient& n : vC)
			{
				_PrintClientRecordLine(n);
				cout << endl;
			}
		}
		cout << "==========================================================";
		cout << "==========================================\n";
	}
};

