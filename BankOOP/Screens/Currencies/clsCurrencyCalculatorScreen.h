#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : public clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Curr, string Destination) {
		cout << "\n"<< Destination << ":";
		cout << "\n______________________";
		cout << "\nCountry    : " << Curr.Country();
		cout << "\ncode       : " << Curr.CurrencyCode();
		cout << "\nName       : " << Curr.CountryName();
		cout << "\nRate(1$) = : " << Curr.Rate();
		cout << "\n______________________\n";
	}

	static clsCurrency _GetCurrency(string Msg) {
		string CurrCode;
		CurrCode = clsInputValidate::ReadString(Msg);
		while (!clsCurrency::IsCurrencyExist(CurrCode)) {
			CurrCode = clsInputValidate::ReadString("Currency code not Found, choose another one:");
		}
		return clsCurrency::FindByCode(CurrCode);
	}

	static float _ReadAmount() {
		cout << "Enter Amount To Exchange: ";
		return (float)clsInputValidate::ReadDblNumber("Invalid Number, choose another one:");
	}

	static void _PrintCalculationResults(float Amount, clsCurrency CurrFrom, clsCurrency CurrTo) {
		if (CurrFrom.CurrencyCode() != "USD") {
			_PrintCurrencyCard(CurrFrom, "Convert From");

			cout << endl << Amount << CurrFrom.CurrencyCode() << " = " <<
				CurrFrom.ConvertToUsd(Amount) << " USD\n";
		}
		if (CurrTo.CurrencyCode() == "USD")
			return;
		_PrintCurrencyCard(CurrTo, "Converting From USD to");
		cout << endl << Amount << CurrFrom.CurrencyCode() << " = " <<
			CurrFrom.ConvertToOtherCurrency(Amount, CurrTo) << " " << CurrTo.CurrencyCode() << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen() {
		clsScreen::_DrawScreenHeader("Currency Calculator Screen");
		bool Continue = false;
		do {
		
			clsCurrency CurrFrom = _GetCurrency("\nEnter Currency1 Code : \n");
			clsCurrency CurrTo = _GetCurrency("\nEnter Currency2 Code:\n");
			
			float Amount = _ReadAmount();

			_PrintCalculationResults(Amount, CurrFrom, CurrTo);

			Continue = clsInputValidate::CheckYesOrNo("\nDo you want to perform another calculation? y/n?");
		} while (Continue);
	}

};
