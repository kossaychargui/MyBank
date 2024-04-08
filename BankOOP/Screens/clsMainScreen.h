#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginRegisterListScreen.h"
#include "clsCurrencyMainScreen.h"
//#include "clsLoginScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private :

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8 ,eExit = 10, eCurrencyExchange = 9
    };

    static void _DrawScreenHeader(string HeaderName) {
       // cout << "\t\t\t\t\t-------------------------------------\n";
        //cout << setw(33) << left << "\t" << HeaderName << endl;
        //cout << "\t\t\t\t\t-------------------------------------\n";
        clsScreen::_DrawScreenHeader(HeaderName);
    }

    static short _ReadMainMenueOption() {
        cout << "\t\t\t\t\tChoose what do want to do? [1 to 10]?";
        short Op = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 9? ");
        return Op;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
       // cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::Show_ClientList();
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
       // cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
       // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
     //   cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
       // cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _LoginRegister() {
        clsLoginRegisterListScreen::ShowLoginRegister();
    }

    static void _CurrencyMenue() {
        clsCurrencyMainScreen::ShowCurrencyMainScreen();
    }

    static void _Logout() {
        CurrentUser = clsUser::Find("", "");

    }

    static void _PerformMainMenueOption(enMainMenueOptions Op) {
        system("cls");
        switch (Op)
        {
        case clsMainScreen::eListClients:
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eAddNewClient:
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eDeleteClient:
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eUpdateClient:
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eFindClient:
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eShowTransactionsMenue:
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eManageUsers:
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eLoginRegister:
            _LoginRegister();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eCurrencyExchange:
            _CurrencyMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eExit:
            _Logout();
            break;
        }

       
    }
    
public:
	
        static void ShowMainMenue()
        {

            system("cls");
            _DrawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Login Register.\n";
            cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
            cout << setw(37) << left << "" << "\t[10] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
        }

};


