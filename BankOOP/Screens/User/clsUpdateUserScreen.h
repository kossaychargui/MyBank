#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:

    static void _Print(clsUser User) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirst Name     : " << User.FirstName;
        cout << "\nLast Name      : " << User.LastName;
        cout << "\nEmail          : " << User.Email;
        cout << "\nPhone          : " << User.Phone;
        cout << "\nUser Name      : " << User.UserName;
        cout << "\nPassword       : " << User.Password;
        cout << "\nPermessions    : " << User.Permessions;
        cout << "\n______________________\n\n";
    }

    static int _ReadPermessions() {
        int per = 0;
        cout << "Do you want to give Acess to :\n";
        if (clsInputValidate::CheckYesOrNo("\nList Clients? y/n?"))
            per = per | clsUser::enPermessions::pListClients;
        if (clsInputValidate::CheckYesOrNo("\nAdd New Client? y/n?"))
            per = per | clsUser::enPermessions::pAddNewClient;
        if (clsInputValidate::CheckYesOrNo("\nDelete Client? y/n?"))
            per = per | clsUser::enPermessions::pDeleteClient;
        if (clsInputValidate::CheckYesOrNo("\nUpdate Client? y/n?"))
            per = per | clsUser::enPermessions::pUpdateClient;
        if (clsInputValidate::CheckYesOrNo("\nFind Client? y/n?"))
            per = per | clsUser::enPermessions::pFindClient;
        if (clsInputValidate::CheckYesOrNo("\nTransactions? y/n?"))
            per = per | clsUser::enPermessions::pTransactions;
        if (clsInputValidate::CheckYesOrNo("\nManage Users? y/n?"))
            per = per | clsUser::enPermessions::pManageUsers;
        if (clsInputValidate::CheckYesOrNo("\nLogin Register? y/n?"))
            per = per | clsUser::enPermessions::pLoginRegister;

        return per;
    }

    static void _ReadUserInfo(clsUser& User) {

        User.FirstName = clsInputValidate::ReadString("Enter First Name: ");
        User.LastName = clsInputValidate::ReadString("Enter Last Name: ");
        User.Email = clsInputValidate::ReadString("Enter Email: ");
        User.Phone = clsInputValidate::ReadString("Enter Phone: ");
       // User.UserName = clsInputValidate::ReadString("Enter User Name: ");
        User.Password = clsInputValidate::ReadString("Enter Password: ");
        cout << "Enter Permessions:";
        if (clsInputValidate::CheckYesOrNo("Do you Want to give full access? y/n?"))
            User.Permessions = -1;
        else
            User.Permessions = _ReadPermessions();
    }

public:

	static void ShowUpdateUserScreen() {
        clsScreen::_DrawScreenHeader("\tUpdate User Screen");
        string UserName = clsInputValidate::ReadString("Enter User Name:");
        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("User Name doesn't exist, Enter User Name:");
        }
        clsUser User = clsUser::Find(UserName);
        _Print(User);
        if (clsInputValidate::CheckYesOrNo("Are you sure you want to Update this User? y/n?")) {
            _ReadUserInfo(User);
            clsUser::enSaveResult SaveResult = User.Save();
            switch (SaveResult)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\nFailed saving the User, Empty User!\n";
                break;
            case clsUser::svSucceeded:
                cout << "\nClient Updated Successfully :-)\n";
                _Print(User);
                break;
            }
        }
        else
            cout << "\nOperation cancelled\n";
	}

};
