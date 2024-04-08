#pragma once
#include <iostream>
using namespace std;
class clsPerson
{
private :

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FirstName, string LastName, string Email, string Phone) {
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(string FirstName) {
		_FirstName = FirstName;
	}

	string GetFirstName(void) {
		return _FirstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName) {
		_LastName = LastName;
	}

	string GetLastName(void) {
		return _LastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	void SetEmail(string Email) {
		_Email = Email;
	}

	string GetEmail(void) {
		return _Email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone) {
		_Phone = Phone;
	}

	string GetPhone(void) {
		return _Phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	string FullName() {
		return (FirstName + " " + LastName);
	}


};
