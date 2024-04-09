#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient client)
	{
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFull Name      : " << client.FullName();
		cout << "\nAcc. Number    : " << client.AccountNumber;
        cout << "\nAccount Balance: " << client.AccountBalance;
        cout << "\n______________________\n";
	}

	static clsBankClient _FindClient(string Destination) {
		string ClientAccNumber = "";
		string Msg = "\nEnter Client Account Number To transfer " + Destination + ":";
		ClientAccNumber = clsInputValidate::ReadString(Msg);
		while (!clsBankClient::IsClientExist(ClientAccNumber)) {
			ClientAccNumber = clsInputValidate::ReadString("\nClient Not Found!, choose another one:");
		}
		return clsBankClient::Find(ClientAccNumber);
	}

	static double _CheckAmount(clsBankClient ClientFrom, clsBankClient ClientTo) {
		string ErrMsg = "Amount Exceeds the available Balance, Enter Another amount? ";
		cout << "\nEnter Transfer Amount ? ";
		double Amount = clsInputValidate::ReadDblNumberBetween(0, ClientFrom.AccountBalance, ErrMsg);
		return Amount;
	}
	

public:

	static void ShowTransferScreen() {
		clsScreen::_DrawScreenHeader("\tTransfer Screen");

		clsBankClient clientFrom = _FindClient("From");
		_PrintClientCard(clientFrom);
		clsBankClient clientTo = _FindClient("To");
		_PrintClientCard(clientTo);
		double Amount = _CheckAmount(clientFrom, clientTo);
		if (clsInputValidate::CheckYesOrNo("\nAre you sure you want to perform this operation? y/n?")) {
			if (clientFrom.Transfer(Amount, clientTo))
				cout << "\nTransfer done successfully :-)\n";
			else
				cout << "\nTransfer is not Accomplished :-(\n";
			/*clientFrom.Withdraw(Amount);
			clientTo.Deposit(Amount);*/
			
			_PrintClientCard(clientFrom);
			_PrintClientCard(clientTo);
		}
		else
			cout << "\nOperation Cancelled.\n";

	}

};


