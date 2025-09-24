#pragma once
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;
class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _AddNewUser()
	{
		string username = "";
		cout << "\nPlease Enter Username: ";
		username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(username))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::GetAddNewUserObject(username);
		ReadUserInfo(user);

		clsUser::enSaveResults SaveResult;
		SaveResult = user.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			user.Print();
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;
			
		}
		case clsUser::enSaveResults::svFaildUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}
	static void ReadUserInfo(clsUser& user)
	{
		cout << "\nEnter FirstName: ";
		user.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		user.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		user.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		user.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		user.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permmision: ";
		user.Permissions = _ReadPermissionsToSet();
	}
	static int _ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = 'n';


		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{


			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nLogin Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pLoginRegister;
		}
		return Permissions;

	}

public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("      Add New User");
		_AddNewUser();
	}
};