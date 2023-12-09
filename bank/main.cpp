#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "mylibrary.h"
using namespace std;
struct stclient
{
    string account_number;
    int pin_code = 0;
    string name;
    string phone;
    string account_balance;
    bool del = 0;
};
vector <string> split_string(string str, string delim)
{
    string sword = "";
    short pos = 0;
    vector <string> vstring;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        sword = str.substr(0, pos);
        if (sword != "")
            vstring.push_back(sword);
        str.erase(0, pos + delim.length());
    }
    if (str != "")
        vstring.push_back(str);

    return vstring;
}
string struct_to_line(stclient client, string delim)
{
    string str = "";
    str += client.account_number + delim;
    str += to_string(client.pin_code) + delim;
    str += client.name + delim;
    str += client.phone + delim;
    str += client.account_balance;
    return str;
}
stclient read_client(void)
{
    cout << "\nPlease enter Client Data:\n";
    stclient client;
    cin.ignore();
    cout << "Enter account number?";
    getline(cin, client.account_number);
    cout << "Enter Pin code?";
    cin >> client.pin_code;
    cin.ignore();
    cout << "enter name?";
    getline(cin, client.name);
    cout << "enter phone?";
    getline(cin, client.phone);
    cout << "Enter Account balance?";
    getline(cin, client.account_balance);
    return client;
}
stclient line_to_struct(string line, string delim)
{
    stclient client;
    vector <string> vstring = split_string(line, delim);
    client.account_number = vstring.at(0);
    client.pin_code = stoi(vstring.at(1));
    client.name = vstring.at(2);
    client.phone = vstring.at(3);
    client.account_balance = vstring.at(4);
    return client;
}
bool add_more_clients(void)
{
    char c;
    cout << "\nDo you want to add more clients?";
    cin >> c;
    return (c == 'Y' || c == 'y');
}
void add_new_client_to_file(string file_name, string str)
{
    fstream file;
    file.open(file_name, ios::out | ios::app);
    if (file.is_open())
    {
        file << str << endl;
    }
    else
        cout << "couldn' not open file!!";
    file.close();

}
bool exist(string account_number, vector<stclient> vclients)
{
    for (stclient& client : vclients)
    {
        if (client.account_number == account_number)
        {
            cout << "\nClient with [" << account_number << "] already exist!";
            return 0;
        }
    }
    return 1;
}
vector<stclient> get_clients(string file_name)
{
    fstream file;
    string str = "";
    vector<stclient> vclients;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        while (getline(file, str))
        {
            vclients.push_back(line_to_struct(str, "#//#"));
        }
        file.close();
    }
    return vclients;
}
void add_new_client(string file_name)
{
    bool add_more = true;
    stclient client;
    vector<stclient> vclients = get_clients(file_name);
    while (add_more)
    {
        do {
            client = read_client();
        } while (!exist(client.account_number, vclients));
        string str = struct_to_line(client, "#//#");
        add_new_client_to_file(file_name, str);
        add_more = add_more_clients();
    }
}

void show_clients_header(short num)
{
    cout << "\n                             Clients List (" << num << ") Clients (s)";
    cout << endl;
    cout << "___________________________________________________________________________\n";
    cout << "| Account Number | Pin code | Client Name           | Phone     | Balance |\n";
    cout << "___________________________________________________________________________\n";
}
void show_client(stclient client)
{
    cout << "|" << left << setw(16) << client.account_number << "|";
    cout << left << setw(10) << client.pin_code << "|";
    cout << left << setw(23) << client.name << "|";
    cout << left << setw(11) << client.phone << "|";
    cout << left << setw(9) << client.account_balance << "|";
}
void show_client_list(string file_name)
{
    vector <stclient> vclients;
    vclients = get_clients(file_name);
    show_clients_header(vclients.size());
    for (stclient& client : vclients)
    {
        show_client(client);
        cout << endl;
    }
    cout << "___________________________________________________________________________\n";
}
void print_client(stclient client)
{
    cout << "ACCOUNT NUMBER:" << client.account_number << endl;
    cout << "Pin code:" << client.pin_code << endl;
    cout << "Name:" << client.name << endl;
    cout << "Phone:" << client.phone << endl;
    cout << "Account balance:" << client.account_balance << endl;
}
bool find_client_by_account_number(string file_name, string account_number, stclient& c)
{
    vector <stclient> vclients = get_clients(file_name);
    for (stclient& client : vclients)
    {
        if (client.account_number == account_number)
        {
            c = client;
            return 1;
        }
    }
    return 0;
}
void update_file(string file_name, vector<stclient>vclients)
{
    fstream file;
    file.open(file_name, ios::out);
    file.close();
    for (stclient client : vclients)
    {
        if (client.del != 1)
        {
            add_new_client_to_file(file_name, struct_to_line(client, "#//#"));
        }
    }
}
bool verify_deleting(void)
{
    char c;
    cout << "Are you Sure you want to delete this client? y/n?";
    cin >> c;
    return (c == 'Y' || c == 'y');
}
void delete_client_by_account_number(string file_name)
{
    stclient c;
    vector <stclient> vclients;
    string account_number = mylibrary::read_string("Please enter Account NUmber:");
    if (find_client_by_account_number(file_name, account_number, c))
    {
        print_client(c);
        if (verify_deleting())
        {
            vclients = get_clients(file_name);
            for (stclient& client : vclients)
            {
                if (client.account_number == c.account_number)
                {
                    client.del = 1;
                }
            }
            update_file(file_name, vclients);
        }
    }
    else
    {
        cout << "Clients with account number (" << account_number << ") does not exist!";
    }
}
bool verify_updating(void)
{
    char c;
    cout << "Are you Sure you want to update this client? y/n?";
    cin >> c;
    return (c == 'Y' || c == 'y');
}
stclient change_client_data(stclient& client)
{
    cout << "\nPlease enter Client Data:\n";
    cout << "Enter Pin code?";
    cin >> client.pin_code;
    cin.ignore();
    cout << "enter name?";
    getline(cin, client.name);
    cout << "enter phone?";
    getline(cin, client.phone);
    cout << "Enter Account balance?";
    getline(cin, client.account_balance);
    return client;
}
void update_client_by_account_number(string file_name)
{
    stclient c;
    string account_number = mylibrary::read_string("Please enter account number:");
    if (find_client_by_account_number(file_name, account_number, c))
    {
        print_client(c);
        if (verify_updating())
        {
            vector <stclient>vclients = get_clients(file_name);
            for (stclient& client : vclients)
            {
                if (client.account_number == c.account_number)
                {
                    client = change_client_data(client);
                    break;
                }
            }
            update_file(file_name, vclients);
        }
    }
    else
        cout << "Client with account number (" << account_number << ") does not exist!";
}

void show_main_menue_screen(void)
{
    cout << "===================================\n";
    cout << "        Main Menue Screen\n";
    cout << "===================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add new Client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===================================\n";
}
void show_end_of_the_program()
{

    cout << "-----------------------------------\n";
    cout << "        Program Ends :-)\n";
    cout << "-----------------------------------\n";
}
void find_client(string file_name)
{
    string account_number = mylibrary::read_string("Please enter account number:");
    vector <stclient> vclients = get_clients(file_name);
    bool found = false;
    for (stclient& client : vclients)
    {
        if (client.account_number == account_number)
        {
            print_client(client);
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Client with account number (" << account_number << ") does not exist!";
}
void bank_operation(string file_name, short op)
{
    switch (op)
    {
    case 1:
        system("cls");
        show_client_list(file_name);
        break;
    case 2:
        system("cls");
        add_new_client(file_name);
        break;
    case 3:
        system("cls");
        delete_client_by_account_number(file_name);
        break;
    case 4:
        system("cls");
        update_client_by_account_number(file_name);
        break;
    case 5:
        system("cls");
        find_client(file_name);
        break;
    default:
        system("cls");
        cout << "\a";
        cout << "\nPlease enter a valid number between 1 to 6!\n";
        return;
    }
}
void bank(string file_name)
{
    short num = 0;
    do
    {
        show_main_menue_screen();
        num = mylibrary::read_num("Choose what do you want to do? [1 to 6]?");
        if (num != 6)
        {  
            bank_operation(file_name, num);
            cout << "\nPress any key to go back to Main Menue...";
            system("pause>0");
            system("cls");
        }
        else
        {
            system("cls");
            show_end_of_the_program();
            cout << "\nThanx for your visit :-), Goodbye\n";
            system("pause>0");
            return;
        }
    } while (num);
}
int main()
{
    bank("text.txt");
    return 0;
}
