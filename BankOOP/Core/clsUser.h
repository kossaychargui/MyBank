#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode, UpdateMode, AddNewMode, DeleteMode };

	enMode _Mode;
	string _UserName;
	string _Password;
	 int _Permissions;

	int _MarkForDelete = false;
	
	static clsUser _GetEmptyUser() {
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = clsString::SplitString(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}

	static string _ConvertUserRecordToLine(clsUser User, string Seperator = "#//#") {
		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User._UserName + Seperator;
		Line += clsUtil::EncryptText(User._Password) + Seperator;
		//Line += User._Password + Seperator;
[O		Line += to_string(User._Permissions);
		return Line;
	}

	static clsUser _ConvertUserLineToRecord(string Line, string Separator = "#//#") {
		vector <string> vUser = clsString::SplitString(Line, Separator);

		return clsUser(UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptText(vUser[5]), stoi(vUser[6]));
	}

	static vector <clsUser> _LoadUsersFromFile() {
		vector <clsUser> vUsers;
		fstream File;
		File.open("users.txt", ios::in);
		if (File.is_open()) {
			string Line = "";
			while(getline(File, Line)){
				if (Line != "") {
					vUsers.push_back(_ConvertUserLineToRecord(Line));
				}
			}
		}
		else
			cout << "\nCouldn't open file!\n";
		return vUsers;
	}

	static void _SaveUsersToFile(vector <clsUser> vUsers) {
		fstream file;
		file.open("users.txt", ios::out);
		if (file.is_open()) {
			for (clsUser& User : vUsers) {
				if (User._MarkForDelete == false) {
					file << _ConvertUserRecordToLine(User);
					file << endl;
				}
			}
			file.close();
		}
		else
			cout << "\nCouldn't open file!\n";
	}

	void _AddNew() {
		fstream file;
		file.open("users.txt", ios::app | ios::out);
		if (file.is_open()) {
			this->Password = clsUtil::EncryptText(this->Password);
			file << _ConvertUserRecordToLine(*this);
			file << endl;
		}
		file.close();
	}

	void _Update() {
		vector <clsUser> vUsers = _LoadUsersFromFile();
		for (clsUser& User : vUsers) {
			if (User._UserName == this->_UserName) {
				User = *this;
				break;
			}
		}
		_SaveUsersToFile(vUsers);
	}

	string _PrepareUserLoginRecord(string Delim = "#//#") {
		string Line = "";
		Line += clsDate::GetSystemDateTimeString();
		Line += Delim + this->UserName;
		Line += Delim + clsUtil::EncryptText(this->Password);
		//Line += Delim + this->Password;
		Line += Delim + to_string(this->Permessions);

		return Line;
	}

public:

	enum enPermessions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions =32 
		, pLoginRegister =  64,pManageUsers = 128,  
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permessions) : clsPerson (FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permessions;
	}

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

	};

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	string GetUserName() {
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermessions(int Permessions) {
		_Permissions = Permessions;
	}

	int GetPermessions() {
		return _Permissions;
	}

	__declspec(property(get = GetPermessions, put = SetPermessions)) int Permessions;

	static bool IsEmptyUser(clsUser User) {
		return (User._Mode == EmptyMode);
	}

	bool IsEmpty() {
		return _Mode == EmptyMode;
	}

	bool MarkedForDeleted() {
		return _MarkForDelete;
	}

	static clsUser Find(string UserName) {
		vector <clsUser> vUsers = _LoadUsersFromFile();
		for (clsUser& User : vUsers) {
			if (User.UserName == UserName) {
				return User;
				break;
			}
		}
		return _GetEmptyUser();
	}

	static clsUser Find(string UserName, string Password) {
		vector <clsUser> vUsers = _LoadUsersFromFile();
		for (clsUser& User : vUsers) {
			if (User._UserName == UserName && User._Password == Password) {
				return User;
				break;
			}
		}
		return _GetEmptyUser();
	}

	bool Delete() {

		vector <clsUser> vUsers = _LoadUsersFromFile();
		for (clsUser& Userr : vUsers) {
			if (Userr.UserName == this->UserName) {
				Userr._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersToFile(vUsers);
		*this = _GetEmptyUser();
		return 1;
	}

	static vector <clsUser> GetUsersList() {
		return _LoadUsersFromFile();
	}

	enum enSaveResult{ svFaildEmptyObject, svSucceeded, svFaildUserExist};

	enSaveResult Save() {
		switch(_Mode){
		case EmptyMode:
			if (IsEmpty())
				return svFaildEmptyObject;
			break;
		case UpdateMode:
			_Update();
			return svSucceeded;
			break;
		case AddNewMode:
			if (IsUserExist(UserName))
				return svFaildUserExist;
			else
			{
				_AddNew();
				_Mode = UpdateMode;
				return svSucceeded;
			}
		}	
	}
	
	static bool IsUserExist(string UserName) {
		clsUser User = Find(UserName);
		return !IsEmptyUser(User);
	}

	static bool IsUserExist(clsUser User) {
		clsUser Userr = Find(User.UserName, User.Password);
		return !IsEmptyUser(Userr);
	}

	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool CheckAccessPermission(enPermessions Permission) {
		if (this->Permessions == enPermessions::eAll)
			return true;
		if ((Permission & this->Permessions) == this->Permessions)
			return true;
		else
			return false;
	}

	void RegisterLogin() {
		string DataLine = _PrepareUserLoginRecord();

		fstream File;
		File.open("LoginRegister.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << DataLine << endl;
		}
		else
			cout << "Couldn't Open the Login File Register!\n";
	}

	static vector <string> LoadLoginRegisterRecords() {
		fstream File;
		File.open("LoginRegister.txt", ios::in);
		if (File.is_open()) {
			vector <string> vRecords;
			string Line = "";
			while (getline(File, Line)) {
				if (Line != "") {
					vRecords.push_back(Line);
				}
			}
			File.close();
			return vRecords;
		}
		else
			cout << "\nCouldn't Open Register Login File!\n";
	}

	static  vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}

};
