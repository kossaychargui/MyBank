#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyMainScreen : public clsScreen
{
private:
	enum enOption{ListCurrencies= 1	, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenue = 5 };
	
	static int _ReadCurrencyMainScreenOption() {
		cout << "\t\t\t\t\tChoose what do you want to do? [1 to 5]?";
		return clsInputValidate::ReadIntNumberBetween(1, 5, "Please Enter a Number 1 and 5: ");
	}

	static void _ListCurrenciesScreen() {
		//cout << "List Currencies Code will be here!";
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _FindCurrencyScreen() {
		//cout << "Find Currency Screen Will be hree!";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _UpdateRateScreen() {
		//cout << "UPdate Rate Code will be here!";
		clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
	}

	static void _CurrencyCalculatorScreen() {
		//cout << "Currency Calculator will bgere here";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrencyMainMenue() {
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowCurrencyMainScreen();
	}

	static void _PerformCurrencyMainScreen(enOption Op) {
		
		switch (Op)
		{
		case clsCurrencyMainScreen::ListCurrencies:
			system("cls");
			_ListCurrenciesScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case clsCurrencyMainScreen::FindCurrency:
			system("cls");
			_FindCurrencyScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case clsCurrencyMainScreen::UpdateRate:
			system("cls");
			_UpdateRateScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case clsCurrencyMainScreen::CurrencyCalculator:
			system("cls");
			_CurrencyCalculatorScreen();
			_GoBackToCurrencyMainMenue();
			break;
		case clsCurrencyMainScreen::MainMenue:
			break;

		}
	}

public:

	static void ShowCurrencyMainScreen() {

		system("cls");
		clsScreen::_DrawScreenHeader("  Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "================================================\n";

		_PerformCurrencyMainScreen((enOption)_ReadCurrencyMainScreenOption());
	}

};
