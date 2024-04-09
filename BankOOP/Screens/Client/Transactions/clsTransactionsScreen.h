#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen : protected clsScreen
{
private:

    enum enTransactionOptions {
        Deposit = 1, Withdraw = 2, TotalBalances = 3, Transfer = 4, TransferLog = 5, MainMenue = 6
    };

    static  void _GoBackToTransactionMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowTransactionsMenue();
    }

    static int _ReadTransactionMenueOption() {
        cout << "\t\t\t\t\tChoose what you want to do? [1 to 6]? ";
        int Op = clsInputValidate::ReadIntNumberBetween(1, 6, "Please enter a number between 1 and 6:");
        return Op;
    }

    static void _ShowDepositScreen() {
      //  cout << "Deposit Code Will be here!\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
      //  cout << "Withdraw Code Will be here!\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTransferScreen() {
        //cout << "Transfer Code Will be here!\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferScreenLog() {
        //cout << "Transfer Log Code Will be here!\n";
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _ShowTotalBalancesScreen() {
       // cout << "Total Balnces Code Will be here!\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _PerformTransactionsMenueOption(enTransactionOptions Op) {
        
        switch (Op)
        {
        case clsTransactionsScreen::Deposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::Withdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::TotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::Transfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::TransferLog:
            system("cls");
            _ShowTransferScreenLog();
            _GoBackToTransactionMenue();
            break;
        default:
            return;
        }
    }

public:

	static void ShowTransactionsMenue() {
        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pTransactions)) {
            return;
        }
		system("cls");
		clsScreen::_DrawScreenHeader("\tTransactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] TotalBalances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] MainMenue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionOptions)_ReadTransactionMenueOption());
	}

};
