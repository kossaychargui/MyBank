#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : public clsScreen
{
private:

	static clsCurrency _FindCurrency() {
		short Op = clsInputValidate::ReadIntNumberBetween(1, 2, "Please enter a number between 1 and 2:");
		string Str = "";
	
		if (Op == 1) {
			Str = clsInputValidate::ReadString("Please Enter Country Code:");
			clsCurrency Curr = clsCurrency::FindByCode(Str);
			return Curr;
		}
		else if (Op == 2) {
			Str = clsInputValidate::ReadString("Please Enter Country Name:");
			clsCurrency Curr = clsCurrency::FindByName(Str);
			return Curr;
		}
			
	}

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

	static void ShowFindCurrencyScreen() {

		clsScreen::_DrawScreenHeader("Find Currency Screen");
		cout << "\nFind by [1] Code or [2] Country ?";
		clsCurrency Curr = _FindCurrency();
		if (!Curr.IsEmpty()) {
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyCard(Curr);
		}
		else
			cout << "\nCurrency Not Found :-(\n\n";
	}

};
