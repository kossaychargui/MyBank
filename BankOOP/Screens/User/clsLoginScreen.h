#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "fstream"

class clsLoginScreen :protected clsScreen
{

private:

    
    static bool _Login()
    {
        bool LoginFaild = false;
        int TrialsNumber = 3;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvalid Username/Password!\n";
                cout << "You have " << --TrialsNumber << " Trials to login\n\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

            if (TrialsNumber <= 0)
                return false;
          

        } while (LoginFaild);

        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenue();

    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};
