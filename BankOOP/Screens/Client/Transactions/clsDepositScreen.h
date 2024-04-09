#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen() {
		clsScreen::_DrawScreenHeader("\t  Deposit Screen");
		string ClientAccNumber = clsInputValidate::ReadString("Please enter Account Number:");
		while (!clsBankClient::IsClientExist(ClientAccNumber)) {
			cout << endl << "Client with [" << ClientAccNumber << "] does not exist!\n";
			ClientAccNumber = clsInputValidate::ReadString("Please enter Account NUmber?");
		}
		clsBankClient client = clsBankClient::Find(ClientAccNumber);
        _Print(client);
        cout << "\nPlease enter deposit amount? ";
        double Amount = clsInputValidate::ReadDblNumber("Please enter a valid number!");
        if (clsInputValidate::CheckYesOrNo("Are you sure you want to perform this transaction? y/n? ")) {
            client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << client.AccountBalance;
        }
        
        else
            cout << "\nOperation was cancelled.\n";
	}

};
