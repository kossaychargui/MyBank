#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:

    string _Value;

    static char _InvertChar(char c)
    {
        return(isupper(c) ? tolower(c) : toupper(c));
    }

    enum WhatToCount { SmallLetters, CapitalLetters, all };

    enum enMatchCase { MatchCase, NoMatchCase };

    static bool _isVowel(char c)
    {
        c = tolower(c);
        return(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }

public:

    clsString() {
        _Value = "";
    }

    clsString(string Value) {
        _Value = Value;
    }

    void setValue(string Value) {
        _Value = Value;
    }

    string getValue(void) {
        return _Value;
    }
    __declspec(property(get = getValue, put = setValue)) string Value;

    short Length() {
        return _Value.length();
    }

    static short Length(string Value) {
        return Value.length();
    }

    static void PrintFirstLetterOfEachWord(string Value)
    {
        short j;
        // i used this loop just to print the first letter . that means if there is any spaces at first it will never be shown
        for (j = 0; j < Value.length(); j++)
        {
            if (Value[j] != ' ')
            {
                cout << Value[j] << endl;
                break;
            }
        }
        for (short i = j; i < Value.length(); i++)
        {
            if (Value[i] == ' ' && Value[i + 1] != ' ')
            {
                cout << Value[i + 1] << endl;
            }
        }
    }

    void PrintFirstLetterOfEachWord() {
        PrintFirstLetterOfEachWord(_Value);
    }

    static string UpperFirstLetterOfEachWord(string Value)
    {
        bool isFirstLetter = true;
        for (short i = 0; i < Value.length(); i++)
        {
            if (Value[i] != ' ' && isFirstLetter)
            {
                Value[i] = toupper(Value[i]);
            }
            isFirstLetter = Value[i] == ' ' ? true : false;
        }
        return Value;

    }

    void UpperFirstLetterOfEachWord() {
        UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string Value)
    {
        bool isFirstLetter = true;
        for (short i = 0; i < Value.length(); i++)
        {
            if (Value[i] != ' ' && isFirstLetter)
            {
                Value[i] = tolower(Value[i]);
            }
            isFirstLetter = Value[i] == ' ' ? true : false;
        }
        return Value;
    }

    void LowerFirstLetterOfEachWord() {
        LowerFirstLetterOfEachWord(_Value);
    }
[O
    static string LowerAllStringLetters(string Value)
    {
        for (short i = 0; i < Value.length(); i++)
        {
            Value[i] = tolower(Value[i]);
        }
        return Value;
    }

    void LowerAllStringLetters() {
        LowerAllStringLetters(_Value);
    }

    static string UpperAllStringLetters(string Value)
    {
        for (short i = 0; i < Value.length(); i++)
        {
            Value[i] = toupper(Value[i]);
        }
        return Value;
    }

    void UpperAllStringLetters() {
        LowerAllStringLetters(_Value);
    }

    static string InvertString(string Value)
    {
        for (short i = 0; i < Value.length(); i++)
        {
            Value[i] = _InvertChar(Value[i]);
        }
        return Value;
    }

    void InvertString() {
        InvertString(_Value);
    }

    static short CountSmallLetters(string Value)
    {
        short count = 0;
        for (short i = 0; i < Value.length(); i++)
        {
            if (islower(Value[i]))
                count++;
        }
        return count;
    }

    short CountSmallLetters() {
        return CountSmallLetters(_Value);
    }

    static short CountCapitalLetters(string Value)
    {
        short count = 0;
        for (short i = 0; i < Value.length(); i++)
        {
            if (isupper(Value[i]))
                count++;
        }
        return count;
    }

    short CountCapitalLetters() {
        return CountCapitalLetters(_Value);
    }

    static short CountSmallOrCapitalLetters(string Value, WhatToCount letter)
    {
        short count = 0;
        for (short i = 0; i < Value.length(); i++)
        {
            if (letter == CapitalLetters && isupper(Value[i]))
                count++;
            else if (letter == SmallLetters && islower(Value[i]))
                count++;

        }
        return count;
    }

    short CountSmallOrCapitalLetters(WhatToCount letter) {
        return  CountSmallOrCapitalLetters(_Value, letter);
    }

    static short CountLetters(string Value, char letter, enMatchCase match = MatchCase)
    {
        short count = 0;
        for (short i = 0; i < Value.length(); i++)
        {
            if (match == MatchCase)
            {
                if (Value[i] == letter)
                    count++;
            }
            else
            {
                if (tolower(Value[i]) == tolower(letter))
                    count++;
            }
        }
        return count;
    }

    short CountLetters(char letter, enMatchCase match = MatchCase) {
        return CountLetters(_Value, letter, match = MatchCase);
    }

    static short CountVowelsInString(string Value)
    {
        short count = 0;
        for (short i = 0; i < Value.length(); i++)
        {
            if (_isVowel(Value[i]))
                count++;
        }
        return count;
    }

    short CountVowelsInString() {
        return  CountVowelsInString(_Value);
    }

    static void PrintAllVowelsInString(string Value)
    {
        for (short i = 0; i < Value.length(); i++)
        {
            if (_isVowel(Value[i]))
                cout << Value[i] << "   ";;
        }
    }

    void PrintAllVowelsInString() {
        PrintAllVowelsInString(_Value);
    }

    static void PrintEachWordOfString(string Value)
    {
        string sword;
        size_t pos = 0;
        string delim = " ";
        while ((pos = Value.find(delim)) != std::string::npos)
        {
            sword = Value.substr(0, pos);
            if (sword != "")
                cout << sword << endl;
            Value.erase(0, sword.length() + delim.length());
        }
        if (Value != "")
            cout << Value << endl;
    }

    void PrintEachWordOfString() {
        PrintEachWordOfString(_Value);
    }

    static short CountWordsInString(string Value)
    {
        short count = 0, pos = 0;
        string sword = "", delim = " ";
        while ((pos = Value.find(delim)) != std::string::npos)
        {
            sword = Value.substr(0, pos);
            if (sword != " ")
                count++;
            Value.erase(0, pos + delim.length());
        }
        if (Value != "")
            count++;

        return count;
    }

    short CountWordsInString() {
        return CountWordsInString(_Value);
    }

    static vector <string> SplitString(string Value, string Delim)
    {
        string sword = "";
        size_t pos = 0;
        vector <string> vstring;
        while ((pos = Value.find(Delim)) != std::string::npos)
        {
            sword = Value.substr(0, pos);
            if (sword != "")
                vstring.push_back(sword);
            Value.erase(0, pos + Delim.length());
        }
        if (Value != "")
            vstring.push_back(Value);

        return vstring;
    }

    vector <string> SplitString(string Delim) {
        return SplitString(_Value, Delim);
    }

    static string TrimLeft(string Value)
    {
        short i = 0;
        while (Value[i] == ' ')
        {
            Value.erase(0, 1);
        }
        return Value;
    }

    void TrimLeft() {
        TrimLeft(_Value);
    }

    static string TrimRight(string Value)
    {
        size_t j = Value.length() - 1;
        while (Value[j] == ' ')
        {
            Value.erase(j, j - 1);
            j = Value.length() - 1;
        }
        return Value;
    }

    void TrimRight() {
        TrimRight(_Value);
    }

    static string Trim(string Value)
    {
        return (TrimRight(TrimLeft(Value)));
    }

    void Trim() {
        Trim(_Value);
    }

    static string JoinString(vector <string> vstring, string Delim)
    {
        string str = "";
        for (string& s : vstring)
        {
            str += s + Delim;
        }
        return (str.substr(0, str.length() - Delim.length()));
    }

    static string JoinString(string str[], short Length, string Delim)
    {
        string s = "";
        for (short i = 0; i < Length; i++)
        {
            s += str[i] + Delim;
        }
        return (s.substr(0, s.length() - Delim.length()));
    }

    static string ReverseString(string Value, string Delim)
    {
        vector<string> vstring = SplitString(Value, " ");
        string s2 = "";
        vector<string>::iterator iter = vstring.end();
        while (iter != vstring.begin())
        {
            --iter;
            s2 += *iter + Delim;

        }
        return(s2.substr(0, s2.length() - Delim.length()));

    }

    void ReverseString(string Delim) {
        ReverseString(_Value, Delim);
    }

    static string ReplaceWordInString(string Value, string WordToReplace, string Word, enMatchCase match = MatchCase)
    {
        vector<string>vstring = SplitString(Value, " ");

        for (string& s : vstring)
        {
            if (match == MatchCase)
            {
                if (s == WordToReplace)
                    s = Word;
            }
            else
            {
                if (LowerAllStringLetters(s) == LowerAllStringLetters(WordToReplace))
                    s = Word;
            }
        }
        return(JoinString(vstring, " "));
    }

    void ReplaceWordInString(string WordToReplace, string Word, enMatchCase match = MatchCase) {
        ReplaceWordInString(_Value, WordToReplace, Word, match = MatchCase);
    }

    static string RemovePunctuations(string Value)
    {
        string s2 = "";
        for (short i = 0; Value[i] != '\0'; i++)
        {
            if (!ispunct(Value[i]))
                s2 += Value[i];
        }
        return s2;
    }

    void RemovePunctuations() {
        RemovePunctuations(_Value);
    }

};
