#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
class clsWithdrawScreen : protected clsScreen
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
	static void ShowWithdrawScreen() {

		clsScreen::_DrawScreenHeader("\t  Withdraw Screen");

		string ClientAccNumber = clsInputValidate::ReadString("Enter Account Number:");
		while (!clsBankClient::IsClientExist(ClientAccNumber)) {
			ClientAccNumber = clsInputValidate::ReadString("Client Account Number doesn't exist, choose another one:");
		}
		clsBankClient client = clsBankClient::Find(ClientAccNumber);
		_Print(client);
		double Amount = 0;
		cout << "Enter Amount:";
		Amount = clsInputValidate::ReadDblNumber("Invalid Number, Enter a number Please:");
		while (Amount > client.AccountBalance) {
			cout << "Withdraw Amount exeeded your balance! Your Balance is :" << client.AccountBalance << endl;
			cout << "Enter Amount:";
			Amount = clsInputValidate::ReadDblNumber("Invalid Number, Enter a number Please:");
		}
		if (clsInputValidate::CheckYesOrNo("Are you sure you want to make this Transaction? y/n? ")) {
			client.Withdraw(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is: " << client.AccountBalance;
		}
		else
			cout << "\nTransaction Cancelled!\n";
		
	}
};
