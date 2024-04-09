#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsFindClientScreen : clsScreen
{
private:

    static void _Print(clsBankClient client) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirst Name     : " << client.FirstName;
        cout << "\nLast Name      : " << client.LastName;
        cout << "\nEmail          : " << client.Email;
        cout << "\nPhone          : " << client.Phone;
        cout << "\nAccount Number : " << client.AccountNumber;
        cout << "\nPinCode        : " << client.PinCode;
        cout << "\nAccount Balance: " << client.AccountBalance;
        cout << "\n______________________\n";
    }

public:

    static void ShowFindClientScreen() {
        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pFindClient)) {
            return;
        }
        clsScreen::_DrawScreenHeader("\t  Find Client Screen");
        string ClientAccNumber = "";
        ClientAccNumber = clsInputValidate::ReadString("Enter Account Number:");
        if (clsBankClient::IsClientExist(ClientAccNumber)) {
            clsBankClient client = clsBankClient::Find(ClientAccNumber);
            _Print(client);
        }
        else
            cout << "\nClient Doesn't Exist!\n";

    }

};
