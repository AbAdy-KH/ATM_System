#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord st)
	{
		cout << left << setw(25) << "|" + st.DateTime;
		cout << left << setw(17) << "|" + st.UserName;
		cout << left << setw(15) << "|" + st.Password;
		cout << left << setw(15) << "|" + to_string(st.Permissions) << "|";
	}
public:
	static void ShowLoginRegisterScreen()
	{
		if (!currentUser.CheckAccessPermission(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}


		vector<clsUser::stLoginRegisterRecord> st = clsUser::GetLoginRegisterList();


		cout << "\t\t\t\t" << st.size() << " Login Were Registed\n";
		cout << "==========================================================";
		cout << "===============\n";
		cout << left << setw(25) << "|Time";
		cout << left << setw(17) << "|Username";
		cout << left << setw(15) << "|Password";
		cout << left << setw(15) << "|Permissions" << "|";
		cout << endl;
		cout << "==========================================================";
		cout << "===============\n";

		for (clsUser::stLoginRegisterRecord n : st)
		{
			_PrintLoginRegisterRecordLine(n);
			cout << endl;
		}

		cout << "==========================================================";
		cout << "===============\n";
	}
};

