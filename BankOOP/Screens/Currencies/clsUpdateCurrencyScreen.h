#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyScreen : public clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Curr) {
		cout << "\nCurrency Card:";
		cout << "\n______________________";
		cout << "\nCountry    : " << Curr.Country();
		cout << "\ncode       : " << Curr.CurrencyCode();
		cout << "\nName       : " << Curr.CountryName();
		cout << "\nRate(1$) = : " << Curr.Rate();
		cout << "\n______________________\n";
	}

public:

	static void ShowUpdateCurrencyScreen() {
		clsScreen::_DrawScreenHeader("Update Currency Screen");

		string CurrCode = clsInputValidate::ReadString("Please enter Currency Code:");

		while (!clsCurrency::IsCurrencyExist(CurrCode))
			CurrCode = clsInputValidate::ReadString("Currency Code Not Found, choose another one:");

		clsCurrency Curr = clsCurrency::FindByCode(CurrCode);
		_PrintCurrencyCard(Curr);
		if (clsInputValidate::CheckYesOrNo("Are you sure you want to update the rate of this Currency? y/n?")) {
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n______________________\n";
			cout << "Enter New Rate : ";
			Curr.UpdateRate(clsInputValidate::ReadDblNumber("Please enter a double Number:"));
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrencyCard(Curr);
		}
		else
			cout << "Operation Cancelled!\n";
	}
};
