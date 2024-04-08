#pragma once
#include <iostream>
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>

#define FileName "Currencies.txt"

class clsCurrency
{
private:
	enum enMode{EmptyMode , UpdateMode};
	enMode _Mode;

	string _Country;
	string _CountryName;
	string _CurrencyCode;
	float _CurrencyRate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line) {

		vector <string> vLine = clsString::SplitString(Line, "#//#");

		return clsCurrency (UpdateMode, vLine[0], vLine[1], vLine[2], stod(vLine[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Curr, string Delim = "#//#") {
		string Line = "";
		Line += Curr._Country + Delim;
		Line += Curr._CurrencyCode + Delim;
		Line += Curr._CountryName + Delim;
		Line += to_string(Curr._CurrencyRate);
		return Line;
	}

	static vector<clsCurrency> _LoadCurrencyDateFromFile() {
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open()) {
			string Line;
			vector <clsCurrency> vCurrencies;
			while (getline(File, Line)) {
				if (Line != "") {
					vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
				}
			}
			File.close();
			return vCurrencies;
		}
		else
			cout << "Couldn't Open 'Currencies.txt' File!\n";
	}
	
	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies) {
		fstream File;
		File.open(FileName, ios::out);//Overwrite
		if (File.is_open()) {
			for (clsCurrency Curr : vCurrencies) {
				File << _ConvertCurrencyObjectToLine(Curr) << endl;
			}
		}
		else
			cout << "Couldn't Open '" << FileName << "' File!\n";
	}

	void _Update(){
		vector<clsCurrency> vCurrencies = _LoadCurrencyDateFromFile();

		for (clsCurrency& Curr : vCurrencies) {
			if (Curr._Country == this->Country()) {
				Curr = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(EmptyMode, "", "", "", 0.0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float CurrencyRate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CountryName = CurrencyName;
		_CurrencyRate = CurrencyRate;
	}
	
	static vector<clsCurrency> GetAllUSDRates() {
		return _LoadCurrencyDateFromFile();
	}

	bool IsEmpty() {
		return _Mode == EmptyMode;
	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CountryName() {
		return _CountryName;
	}

	void UpdateRate(float NewRate) {
		_CurrencyRate = NewRate;
		_Update();
	}

	float Rate() {
		return _CurrencyRate;
	}

	static clsCurrency FindByName(string CountryName) {
		CountryName = clsString::UpperAllStringLetters(CountryName);

		vector<clsCurrency> vCurrencies = _LoadCurrencyDateFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (clsString::UpperAllStringLetters(C.Country()) == CountryName) {
				return C;
				break;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllStringLetters(CurrencyCode);

		vector<clsCurrency> vCurrencies = _LoadCurrencyDateFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (clsString::UpperAllStringLetters(C.CurrencyCode()) == CurrencyCode) {
				return C;
				break;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
		return (!C.IsEmpty());
	}
[O
	static vector<clsCurrency>GetCurrenciesList() {
		return _LoadCurrencyDateFromFile();
	}

	float ConvertToUsd(float Amount) {
		return (float)Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		return (float)ConvertToUsd(Amount) * Currency2.Rate();
	}

};


