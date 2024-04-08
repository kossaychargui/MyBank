#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "Global.h"

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode, UpdateMode, AddNewMode, DeleteMode };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector <string> vstring = clsString::SplitString(Line, Separator);

		return clsBankClient(UpdateMode, vstring[0], vstring[1], vstring[2], vstring[3], vstring[4], vstring[5], stod(vstring[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		string Line = "";
		Line += Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client.AccountNumber + Separator;
		Line += Client.PinCode + Separator;
		Line += to_string(Client.AccountBalance);
		return Line;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDateFromFile() {
		
			vector <clsBankClient> vClients;

			fstream MyFile;
			MyFile.open("clients.txt", ios::in);//read Mode

			if (MyFile.is_open())
			{

				string Line;


				while (getline(MyFile, Line))
				{

					clsBankClient Client = _ConvertLineToClientObject(Line);

					vClients.push_back(Client);
				}

				MyFile.close();

			}

			return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients) {
		fstream MyFile;
		MyFile.open("clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream file;
		file.open("clients.txt", ios::out | ios::app);
		if (file.is_open()) {
			file << stDataLine;
				file << endl;
		}
		file.close();
	}

	void _Update() {
		vector <clsBankClient> _vClients = _LoadClientsDateFromFile();

		for (clsBankClient& c : _vClients) {
			if (c.AccountNumber == AccountNumber) {
				c = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferRecord(clsBankClient DestinationClient, double Amount, string Delim = "#//#") {
		string Line = "";
		Line += clsDate::GetSystemDateTimeString() + Delim;
		Line += this->AccountNumber + Delim + DestinationClient.AccountNumber + Delim;
		Line += to_string(Amount) + Delim + to_string(this->AccountBalance) + Delim;
		Line += to_string(DestinationClient.AccountBalance) + Delim + CurrentUser.UserName;

		return Line;
	}

	void _AddTransferRecord(clsBankClient DestinationClient, double Amount) {
		string Record = _PrepareTransferRecord(DestinationClient, Amount);
		fstream File;
		File.open("TransferLog.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << Record << endl;
			File.close();
		}
		else
			cout << "\nCouldn't Open TransferLog File!\n";
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson (FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		this->FirstName = FirstName;
		this->LastName = LastName;
		this->Email = Email;
		this->Phone = Phone;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	 bool IsEmpty()  {
		return (_Mode == EmptyMode);
	}

	void SetAccountNumber(string AccountNumber) {
		_AccountNumber = AccountNumber;
	}

	string GetAccountNumber() {
		return _AccountNumber;
	}

	__declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;
	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;
	// From now one we should seperate the UI from the classes!
	/*void Print() {
		cout << "\nClient Card:";
		cout << "\n______________________";
		cout << "\nFirst Name     : " << FirstName;
		cout << "\nLast Name      : " << LastName;
		cout << "\nEmail          : " << Email;
		cout << "\nPhone          : " << Phone;
		cout << "\nAccount Number : " << _AccountBalance;
		cout << "\nPinCode        : " << _PinCode;
		cout << "\nAccount Balance: " << _AccountBalance;
		cout << "\n______________________\n";
	}*/

	static clsBankClient Find(string AccountNumber) {
		fstream file;
		vector <clsBankClient> vClients;
		string Line = "";
		file.open("clients.txt", ios::in);
		if (file.is_open()) {
			while (getline(file, Line)) {
				clsBankClient client = _ConvertLineToClientObject(Line);
				if (!client.IsEmpty()) {
					vClients.push_back(client);
				}
			}
			for (clsBankClient& Client : vClients) {
				if (Client.AccountNumber == AccountNumber)
				{
					file.close();
					return Client;
				}
			}
			file.close();
		}
		else
			cout << "\nCouldn't open the file!\n";

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream file;
		vector <clsBankClient> vClients;
		string Line = "";
		file.open("clients.txt", ios::in);
		if (file.is_open()) {
			while (getline(file, Line)) {
				clsBankClient client = _ConvertLineToClientObject(Line);
				if (!client.IsEmpty()) {
					vClients.push_back(client);
				}
			}
			for (clsBankClient& Client : vClients) {
				if (Client.AccountNumber == AccountNumber&& Client.PinCode == PinCode)
					return Client;
			}
		}
		else
			cout << "\nCouldn't open the file!\n";

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResults{ svFaildEmptyObject, svSuceeded, svFaildAccountNumberExists
	};

	enSaveResults Save() {
		switch (_Mode) {
		case EmptyMode:
			return svFaildEmptyObject;

		case UpdateMode:
			_Update();
			return svSuceeded;
			break;
		case AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			else
			{
				_AddNew();
				_Mode = UpdateMode;
				return enSaveResults::svSuceeded;
			}
			break;
		}

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0.0);
	}

	bool Delete() {
		vector <clsBankClient> vClients = _LoadClientsDateFromFile();
		for (clsBankClient& c : vClients) {
			if (c.AccountNumber == this->AccountNumber)
				c._MarkForDelete = true;
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDateFromFile();
	}

	static double GetTotalBalances(){ 
		vector <clsBankClient> vClients = _LoadClientsDateFromFile();
		double TotalBalances = 0;
		for (clsBankClient C : vClients) {
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount) {
		this->AccountBalance += Amount;
		_Update();
	}

	void Withdraw(double Amount) {
		this->AccountBalance -= Amount;
		_Update();
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);

		_AddTransferRecord(DestinationClient, Amount);

		return true;
	}

	static vector<string> LoadTransferLogRecords() {
		fstream File;
		File.open("TransferLog.txt", ios::in);
		if (File.is_open()) {
			string Line;
			vector <string> vRecords;
			while (getline(File, Line)) {
				if (Line != "") {
					vRecords.push_back(Line);
				}
			}
			File.close();
			return vRecords;
		}
		else
			cout << "\nCouldn't Open TransferLog File!\n";

		
	}
	
};
