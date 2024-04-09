#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsAddNewClientScreen : protected clsScreen 
{
private:

    static void _ReadClientInfo(clsBankClient& Client) {

        Client.FirstName = clsInputValidate::ReadString("Enter First Name: ");
        Client.LastName = clsInputValidate::ReadString("Enter Last Name: ");
        Client.Email = clsInputValidate::ReadString("Enter Email: ");
        Client.Phone = clsInputValidate::ReadString("Enter Phone: ");
        Client.AccountNumber = clsInputValidate::ReadString("Enter Account Number: ");
        Client.PinCode = clsInputValidate::ReadString("Enter PinCode: ");
        cout << "\nEnter Account Balance:";
        Client.AccountBalance = clsInputValidate::ReadDblNumber("Please enter a double!");

    }

public:

	static void ShowAddNewClientScreen() {

        if (!clsScreen::CheckAccessRights(clsUser::enPermessions::pAddNewClient)) {
            return;
        }
            _DrawScreenHeader("\t  Add New Client Screen");

            string ClientAccNumber = "";
            bool found = 0;
            ClientAccNumber = clsInputValidate::ReadString("Enter Account Number:");
            while ((found = clsBankClient::IsClientExist(ClientAccNumber)) == true) {
                ClientAccNumber = clsInputValidate::ReadString("Client Account Number already exists, Please enter another one : ");
            }
            clsBankClient client = clsBankClient::GetAddNewClientObject(ClientAccNumber);
            _ReadClientInfo(client);
            clsBankClient::enSaveResults save = client.Save();
            switch (save) {
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "Failed to add client, Because it's empty!";
                break;
            case  clsBankClient::enSaveResults::svSuceeded:
                cout << "client Added Successfully :)";
                break;
            case clsBankClient::enSaveResults::svFaildAccountNumberExists:
                cout << "Client Account Number Already Exists!";
            }
        
        
	}

};
