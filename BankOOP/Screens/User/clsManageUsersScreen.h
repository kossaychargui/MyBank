#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen
{
private:

    enum enManageUsersOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue
    };

    static void _GoBackToManageUsersScreen() {
        cout << "Press Any Key to Go back To Manage users Screen....";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static int _ReadManageUsersMenueOption() {
        cout << "\t\t\t\t   Choose What do you want to do? [1 to 6]? ";
        int Op = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter A number between 1 and 6:");
        return Op;
    }

    static void _ShowListUsersScreen() {
        //cout << "Show List Users Screen will be here!\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen() {
      //  cout << "Show Add New User Screen will be here!\n";
        clsAddNewUserScreen::ShowAddNewUser();
    }

    static void _ShowDeleteUserScreen() {
       // cout << "Show Delete User Screen will be here!\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
       // cout << "Show Update User Screen will be here!\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    } 

    static void _ShowFindUserScreen() {
        //cout << "Show Find User Screen will be here!\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenueOption(enManageUsersOptions Op) {
        
        switch (Op) 
        {
        case clsManageUsersScreen::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUsersScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUsersScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUsersScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUsersScreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersScreen();
            break;
        default:
            return;
        }
    }

public:

	static void ShowManageUsersMenue() {
        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pManageUsers)) {
            return;
        }
        system("cls");
        clsScreen::_DrawScreenHeader("\tManage Users Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenueOption((enManageUsersOptions)_ReadManageUsersMenueOption());
	}

};
