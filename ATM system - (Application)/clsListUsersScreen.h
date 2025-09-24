#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser User)
	{
		cout << left << setw(17) << "|" + User.UserName;
		cout << left << setw(25) << "|" + User.FullName();
		cout << left << setw(15) << "|" + User.Phone;
		cout << left << setw(20) << "|" + User.Email;
		cout << left << setw(10) << "|" + User.Password;
		cout << left << setw(12) << "|" + to_string(User.Permissions) << "|";
		cout << endl;
	}

public:
	static void ShowUsersList()
	{
		vector<clsUser> vU = clsUser::GetUsersList();

		cout << "\t\t\t\t Users List (" << vU.size() << ") User(s)\n";
		cout << "==========================================================";
		cout << "==========================================\n";
		cout << left << setw(17) << "|Username";
		cout << left << setw(25) << "|Client Name";
		cout << left << setw(15) << "|Phone";
		cout << left << setw(20) << "|Email";
		cout << left << setw(10) << "|Password";
		cout << left << setw(12) << "|Permession" << "|";
		cout << endl;
		cout << "==========================================================";
		cout << "==========================================\n";


		for (clsUser n : vU)
		{
			_PrintUserRecordLine(n);
		}
		cout << "==========================================================";
		cout << "==========================================\n";
	}
};

