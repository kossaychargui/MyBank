#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : public clsScreen
{
private:

    static void PrintCurrencyRecordLine(clsCurrency Curr)
    {

        cout << setw(8) << left << "";
        cout << "| " << setw(28) << left << Curr.Country();
        cout << "| " << setw(7) << left << Curr.CurrencyCode();
        cout << "| " << setw(37) << left << Curr.CountryName();
        cout << "| " << setw(10) << left << Curr.Rate();
    }

public:

	static void ShowCurrenciesList() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Subtitle = "   Currencies (" + to_string(vCurrencies.size()) + ").";
		clsScreen::_DrawScreenHeader("   Currencies List Screen", Subtitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "";
        cout << "| " << left << setw(28) << "Country";
        cout << "| " << left << setw(7) << "Code";
        cout << "| " << left << setw(37) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency Record : vCurrencies)
            {

                PrintCurrencyRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}
};
