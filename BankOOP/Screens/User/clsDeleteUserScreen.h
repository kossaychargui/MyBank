#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsDeleteUserScreen : protected clsScreen
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

public:

	static void ShowDeleteUserScreen() {
        clsScreen::_DrawScreenHeader("\tDelete User Screen");
        string UserName = clsInputValidate::ReadString("Enter User Name:");
        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("User Name doesn't exist, Enter User Name:");
        }
        clsUser User = clsUser::Find(UserName);
        _Print(User);
        if (clsInputValidate::CheckYesOrNo("Are you sure you want to delete this User? y/n?")) {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully.\n";
                _Print(User);
            }
            else
                cout << "Error Occurred, Couldn't Delete User!\n";
        }
        else
            cout << "\nOperation cancelled\n";
	}

};
