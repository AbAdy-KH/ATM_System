#pragma once
#include"clsInputValidate.h"
#include"clsString.h"
#include"clsDate.h"
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include <string>
#include <vector>


class clsBankClient : public clsPerson , clsDate
{
private:
    enum enMode { EmptyMode = 0, UpdeteMode = 1, AddNewMode = 2};
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;


    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;
    }
    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _ConverLineToClientObject(string Line, string Seperator = "#//#")//it must be static
    {
        vector <string> vClient;
        vClient = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdeteMode, vClient[0], vClient[1], vClient[2], vClient[3],
            vClient[4], vClient[5], stof(vClient[6]));
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;
    }
    static void _AddDataLineToFile(string dataLine)
    {
        fstream Myfile;
        Myfile.open("Clients.txt", ios::app);

        string DataLine;
        if (Myfile.is_open())
        {
            Myfile << dataLine;
            Myfile.close();
        }
    }
    void _SaveCleintsDataToFile(vector<clsBankClient> vC)
    {
        fstream Myfile;
        Myfile.open("Clients.txt", ios::out);

        string DataLine;
        if (Myfile.is_open())
        {
            for (clsBankClient n : vC)
            {
                if (n._MarkedForDelete == false)
                {
                DataLine = _ConverClientObjectToLine(n);
                Myfile << DataLine << endl;
                }
            }
            Myfile.close();
        }
    }
    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vC;

        fstream Myfile;
        Myfile.open("Clients.txt", ios::in);

        string line;

        if (Myfile.is_open())
        {
            while (getline(Myfile, line))
            {
                clsBankClient client = _ConverLineToClientObject(line);
                vC.push_back(client);
            }

            Myfile.close();
        }
        return vC;

    }


    void _Update()
    {
        vector<clsBankClient> vC = _LoadClientsDataFromFile();

        for (clsBankClient& n : vC)
        {
            if (n.AccountNumber() == AccountNumber())
            {
                n = *this;
                break;
            }
        }

        _SaveCleintsDataToFile(vC);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

public:

    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string AccountNumber, string PinCode, float AccountBalance)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }


    bool isEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n===================";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n===================\n";
    }

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);


        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient cClient = _ConverLineToClientObject(Line);
                if (cClient.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return cClient;
                }
            }
            MyFile.close();
        }

        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);


        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient cClient = _ConverLineToClientObject(Line);
                if (cClient.AccountNumber() == AccountNumber && cClient.PinCode == PinCode)
                {
                    MyFile.close();
                    return cClient;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    bool Delete()
    {
        vector<clsBankClient> vC = _LoadClientsDataFromFile();

        for (clsBankClient& n : vC)
        {
            if (n.AccountNumber() == _AccountNumber)
            {
                n._MarkedForDelete = true;
            }
        }

        _SaveCleintsDataToFile(vC);
        *this = _GetEmptyClientObject();

        return true;
    }
    

    void Deposit(float amount)
    {
        _AccountBalance += amount;
        save();
    }
    bool Withdraw(float amount)
    {
        if (AccountBalance < amount)
        {
            return false;
        }
        else
        {
            AccountBalance -= amount;
            save();
            return true;
        }
    }
    bool Transfer(float Amount, clsBankClient& DestinationClient, string userName)
    {
        if (!Withdraw(Amount))
        {
            return false;
        }

        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, userName);
        return true;
    }

    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }

    enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};
    enSaveResult save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResult::svFaildEmptyObject; break;

        case enMode::UpdeteMode:
            _Update();
            return enSaveResult::svSucceeded; break;

        case enMode::AddNewMode:
            if (IsClientExist(_AccountNumber))
            {
                return enSaveResult::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdeteMode;
                return enSaveResult::svSucceeded;
            }
        }
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.isEmpty());
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    static vector<clsBankClient> GetClientList()
    {
        return _LoadClientsDataFromFile();
    }
    static double GetTotalBalances(vector<clsBankClient> vC)
    {
        double sum = 0;
        for (clsBankClient& n : vC)
            sum += n.AccountBalance;

        return sum;
    }
};




