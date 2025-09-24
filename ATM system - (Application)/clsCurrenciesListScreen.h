#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen :protected clsScreen
{

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();

    }

public:


    static void ShowCurrenciesListScreen()
    {


        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "  Currencies List Screen";
        string SubTitle = "(" + to_string(vCurrencys.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);
        cout << "" << "\n=======================================================";
        cout << "===============================================\n";
        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << "\n=======================================================";
        cout << "===============================================\n";

        if (vCurrencys.size() == 0)
            cout << "\tNo Currencies Available In the System!";
        else

            for (clsCurrency Currency : vCurrencys)
            {
                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << "=======================================================";
        cout << "===============================================\n" << endl;

    }

};

