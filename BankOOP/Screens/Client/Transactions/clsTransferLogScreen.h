#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private:
    static void _DrawTransferLogHeader() {

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(14) << "s.Balance";
        cout << "| " << left << setw(14) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;

    }

    static void _PrintTransferLogLine(string Line) {
        vector <string> vLine = clsString::SplitString(Line, "#//#");
        cout << setw(8) << left << "" << "| " << setw(25) << left << vLine[0];
        cout << "| " << setw(10) << left << vLine[1];
        cout << "| " << setw(10) << left << vLine[2];
        cout << "| " << setw(12) << left << vLine[3];
        cout << "| " << setw(14) << left << vLine[4];
        cout << "| " << setw(14) << left << vLine[5];
        cout << "| " << setw(10) << left << vLine[6];
    }

public:

	static void ShowTransferLogScreen() {

        vector <string> vRecords = clsBankClient::LoadTransferLogRecords();
        string Subtitle = "";
        Subtitle += "\t(" + to_string(vRecords.size()) + ") Record(s).";
        clsScreen::_DrawScreenHeader("\tTransfer Log List Screen", Subtitle);
        _DrawTransferLogHeader();

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Transfer Logs Available In the System!";
        else

            for (string& Line : vRecords)
            {

                _PrintTransferLogLine(Line);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;
	}

};
