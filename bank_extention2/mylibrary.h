#pragma once
#pragma once
#include <iostream>
#include <string>
#include <limits>
using namespace std;
namespace mylibrary
{
	int read_num(string msg)
	{
		int num;
		cout << msg;
		cin >> num;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid number! pleaze enter a valid one: " << endl;
			cin >> num;

		}
		return (num);
	}
	string read_string(string msg)
	{
		string ch;
		cout << msg;
		cin >> ch;
		return (ch);
	}
	char read_char(string msg)
	{
		char c;
		cout << msg;
		cin >> c;
		return(c);
	}
	int random_num(int from, int to)
	{
		return (rand() % (to - from + 1) + from);
	}
	void swap(int& a, int& b)
	{
		int temp;
		temp = a;
		a = b;
		b = temp;
	}
	void print_array(int array[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			cout << array[i] << "  ";
		}
		cout << endl;
	}
	void fill_array(int array[100], int length)
	{
		for (int count = 0; count < length; count++)
		{
			cout << "array[" << count << "]:";
			cin >> array[count];
		}
	}
}
