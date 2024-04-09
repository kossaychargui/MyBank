#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsDeleteClientScreen : protected clsScreen
{
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

	static void ShowDeleteClientScreen() {
        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pDeleteClient)) {
            return;
        }
        clsScreen::_DrawScreenHeader("\tDelete Client Screen");
        string ClientAccNumber = "";
        ClientAccNumber = clsInputValidate::ReadString("Enter Account Number:");
        while (!clsBankClient::IsClientExist(ClientAccNumber)) {
            ClientAccNumber = clsInputValidate::ReadString("Client Account Number Doesn't exist enter another one:");
        }
        clsBankClient client = clsBankClient::Find(ClientAccNumber);
        _Print(client);
        if (clsInputValidate::CheckYesOrNo("Are you sure you want to delete this client: y/n?"))
        {
            if (client.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                _Print(client);
            }
            else
                cout << "\nError Client was not Deleted!\n";
        }
	}

};
