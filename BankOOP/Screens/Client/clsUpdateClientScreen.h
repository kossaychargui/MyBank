#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen : protected clsScreen
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
    
    static void _ReadClientInfo(clsBankClient& Client) {

        Client.FirstName = clsInputValidate::ReadString("Enter First Name: ");
        Client.LastName = clsInputValidate::ReadString("Enter Last Name: ");
        Client.Email = clsInputValidate::ReadString("Enter Email: ");
        Client.Phone = clsInputValidate::ReadString("Enter Phone: ");
       // Client.AccountNumber = clsInputValidate::ReadString("Enter Account Number: ");
        Client.PinCode = clsInputValidate::ReadString("Enter PinCode: ");
        cout << "Enter Account Balance:";
        Client.AccountBalance = clsInputValidate::ReadDblNumber("Please enter a double!");

    }
public:

    static void ShowUpdateClientScreen() {
        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pUpdateClient)) {
            return;
        }
        clsScreen::_DrawScreenHeader("\tUpdate Client Screen");

        string ClientAccNumber = "";

        ClientAccNumber = clsInputValidate::ReadString("Please enter account number:");
        while (!clsBankClient::IsClientExist(ClientAccNumber)) {
            ClientAccNumber = clsInputValidate::ReadString("\nAccount Number NOt found, choose another one:");
        }
        clsBankClient client = clsBankClient::Find(ClientAccNumber);
        _Print(client);
        if (clsInputValidate::CheckYesOrNo("Are you sure you want to Update this Client? y/n? ")) {
            cout << "\n\nUpdate Client Info:";
            cout << "\n_________________________\n";
            _ReadClientInfo(client);
            _Print(client);

            clsBankClient::enSaveResults save = client.Save();

            switch (save) {
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nFailed to save the client because it is empty !\n";
                break;
            case clsBankClient::enSaveResults::svSuceeded:
                cout << "\nClient saved Successfully.\n";
                _Print(client);
                break;
            }
        }
        else
        {
            cout << "\nOperation Cancelled!\n";
        }
    }
};
