#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen : protected clsScreen
{
private:

    static void _Print(clsUser User) {
        cout << "\nUser Card:";
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

	static void ShowFindUserScreen() {
        clsScreen::_DrawScreenHeader("\tFind User Screen");
        string UserName = clsInputValidate::ReadString("Enter User Name:");
        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("User Name Not Found, Enter User Name:");
        }
        clsUser User = clsUser::Find(UserName);
        cout << "\nUser Found :-)\n";
        _Print(User);
	}

};
