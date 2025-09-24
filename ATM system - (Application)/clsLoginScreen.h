#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
#include "clsMainScreen.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short Trials = 3;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                Trials--;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You Have " << Trials << " Trials\n\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            currentUser = clsUser::Find(Username, Password);

            LoginFaild = currentUser.IsEmpty();

        } while (LoginFaild && Trials > 1);


        if (!LoginFaild)
        {
            currentUser.LoginRegister();
            clsMainScreen::ShowMainMenue();
            return true;
        }

        else
        {
            cout << "\n\n\nYou Have Been Locked :-(\n";
            return false;
        }
        
    }   
public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("      Login Screen");

        return _Login();
    }

};

