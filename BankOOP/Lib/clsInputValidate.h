#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:

	static bool IsNumberBetween(int num, int from, int to) {
		return (num <= to && num >= from);
	}

	static bool IsNumberBetween(double num, double from, double to) {
		return (num <= to && num >= from);
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo) {
		if (clsDate::IsDate1AfterDate2(DateFrom, DateTo))
			clsDate::SwapDates(DateFrom, DateTo);
		return (clsDate::IsDate1BeforeDate2(Date, DateTo) && clsDate::IsDate1BeforeDate2(Date, DateFrom));
	}

	static int ReadIntNumber(string ErrorMsg) {
		int Num = 0;

		while (cout << "Enter a number" && !(cin >> Num)) {
			cin.clear(); //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			cout << ErrorMsg;
		}
		return Num;
	}

	static int ReadIntNumberBetween(int from, int to, string ErrorMsg) {
		int Num;
		bool verify;
		do {
			cin >> Num;
			verify = (Num <= to && Num >= from) && cin.good();
			if (!verify) {

				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << ErrorMsg;
			}
		} while (!verify);
		return Num;
	}

	static double ReadDblNumber(string ErrorMsg) {
		double Num = 0;
		bool verify;
		do {
			cin >> Num;
			verify = (cin.good());
			if (!verify) {

				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << ErrorMsg << endl;
			}
		} while (!verify);
		return Num;
	}

	static double ReadDblNumberBetween(double from, double to, string ErrorMsg) {
		double Num = 0;
		bool verify;
		do {
			cin >> Num;
			verify = cin.good() && (Num >= from && Num <= to);
			if (!verify) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << ErrorMsg;
			}
		} while (!verify);

		return Num;
	}

	static bool IsValideDate(clsDate Date) {
		return (clsDate::IsValidDate(Date));
	}

	static string ReadString(string Msg) {
		string str = "";
		cout << Msg;
		getline(cin >> ws, str);
		return str;
	}
	
	static bool CheckYesOrNo(string Msg) {
		cout << Msg;
		//cout << " y/n?";
		char c;
		cin >> c;
		return (c == 'y' || c == 'Y');
	}

};
