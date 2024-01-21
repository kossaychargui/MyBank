#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "mylibrary.h"
using namespace std;
void login();
struct stclient
{
    string account_number = "";
    string pin_code = "";
    string name = "";
    string phone_number = "";
    int account_balance = 0;
};
vector <string> split_string(string str, string delim)
{
    string sword = "";
    size_t pos = 0;
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
bool validate_choice(string msg)
{
    char c = mylibrary::read_char(msg);
    return c == 'y';
}
void show_login_screen(void)
{
    cout << "\n-------------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n-------------------------------------\n";
}
stclient read_client()
{
    stclient client;
    client.account_number = mylibrary::read_string("Enter Account Number?");
    client.pin_code = mylibrary::read_string("Enter Pin?");
    return client;
}
stclient line_to_stclient(string str, string delim)
{
    stclient client;
    vector <string> vstring = split_string(str, delim);
    client.account_number = vstring[0];
    client.pin_code = vstring[1];
    client.name = vstring[2];
    client.phone_number = vstring[3];
    client.account_balance = stoi(vstring[4]);
    return client;
}
string stclient_to_line(stclient client, string delim)
{
    string str = "";
    str += client.account_number + delim;
    str += client.pin_code + delim;
    str += client.name + delim;
    str += client.phone_number + delim;
    str += to_string(client.account_balance);
    return str;
}
vector <stclient> get_clients(string file_name)
{
    fstream file;
    vector <stclient> vclients;
    file.open(file_name, ios::in);
    string str = "";
    if (file.is_open())
    {
        while (getline(file, str))
            vclients.push_back(line_to_stclient(str, "#//#"));

        file.close();
    }
    else
        cout << "\n\aCouldn't open file!\n";

    return vclients;
}
bool does_client_exist(stclient& client, string file_name)
{
    vector <stclient> vclients = get_clients(file_name);
    for (stclient& clientt : vclients)
    {
        if (clientt.account_number == client.account_number && clientt.pin_code == client.pin_code)
        {
            client = clientt;
            return 1;
        }
    }
    return 0;
}
void show_atm_main_menue_screen(void)
{
    cout << "=======================================\n";
    cout << "\tATM Main Menue Screen";
    cout << "\n=======================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "=======================================\n";
}
short read_operation(short from, short to)
{
    short op;
    do
    {
        cout << "From " << from << " to " << to;
        op = mylibrary::read_num(", Choose what do you want to do?");
        if (op < from || op > to)
            cout << "\a\nPlease enter a number between"<< from << " and " << to <<"!\n";
    } while (op < from || op > to);
    return op;
}
void show_quick_withdraw_screen(void)
{
    cout << "=======================================\n";
    cout << "\tQuick Withdraw Screen";
    cout << "\n=======================================\n";
    cout << "\t[1] 20          [2] 50\n";
    cout << "\t[3] 100         [4] 200\n";
    cout << "\t[5] 400         [6] 600\n";
    cout << "\t[7] 800         [8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "\n=======================================\n";
}
void check_balance_screen(void)
{
    cout << "======================================\n";
    cout << "\tCheck Balance Screen";
    cout << "\n=======================================\n";
}
void add_client_to_file(stclient client, string file_name)
{
    string str = "";
    fstream file;
    file.open(file_name, ios::out | ios::app);
    if (file.is_open())
    {
        str = stclient_to_line(client, "#//#");
        file << str << endl;
        file.close();
    }
    else
        cout << "\n\aCouldn't open file!\n";
}
void update_clients_file(vector<stclient> vclients, string file_name)
{
    fstream file;
    file.open(file_name, ios::out);
    file.close();
    for (stclient& client : vclients)
    {
        add_client_to_file(client, file_name);
    }
}
[Ovoid check_balance(stclient& client, string file_name)
{
    cout << "Your balance is " << client.account_balance << endl;
}
enum enOpmoeny { op1 = 20, op2 = 50, op3 = 100, op4 = 200, op5 = 400, op6 = 600, op7 = 800, op8 = 900 };
void quick_withdraw_operation(stclient& clientt, short op)
{
    switch (op)
    {
    case 1:
        clientt.account_balance -= op1;
        break;
    case 2:
        clientt.account_balance -= op2;
        break;
    case 3:
        clientt.account_balance -= op3;
        break;
    case 4:
        clientt.account_balance -= op3;
        break;
    case 5:
        clientt.account_balance -= op4;
        break;
    case 6:
        clientt.account_balance -= op5;
        break;
    case 7:
        clientt.account_balance -= op6;
        break;
    case 8:
        clientt.account_balance -= op7;
        break;
    }
}
bool validate_quick_withdraw(short op, short client_money)
{
    switch (op)
    {
    case 1:
        return (op1 <= client_money);
    case 2:
        return (op2 <= client_money);
    case 3:
        return (op3 <= client_money);
    case 4:
        return (op4 <= client_money);
    case 5:
        return (op5 <= client_money);
    case 6:
        return (op6 <= client_money);
    case 7:
        return (op7 <= client_money);
    default:
        return (op8 <= client_money);
    }
}
void quick_withdraw(stclient& client, string file_name)
{
    show_quick_withdraw_screen();
    check_balance(client, file_name);
    vector<stclient> vclients = get_clients(file_name);
    short op = 0;
    bool valid_op = true;
    for (stclient& clientt : vclients)
    {
        if (clientt.account_number == client.account_number)
        {
            do
            {
                op = read_operation(1, 9);
                if (op == 9)
                    return;
                valid_op = validate_quick_withdraw(op, clientt.account_balance);
                if(!valid_op)
                    cout << "\n\aThe amount exceeds your balance, Your balance is " << clientt.account_balance<<".\n";
            } while (!valid_op);
            if (validate_choice("Are you sure you want to make this transaction? y/n?"))
                quick_withdraw_operation(clientt, op);
            else
                return;
            cout << "\nDone Successfully. New balance is: " << clientt.account_balance << endl;
            client = clientt;
            update_clients_file(vclients, file_name);
            break;
        }
    }
}
void show_normal_withdraw_screen(void)
{
    cout << "=======================================\n";
    cout << "\t\tNormal Withdraw Screen";
    cout << "\n=======================================\n";
}
void normal_withdraw(stclient& client, string file_name)
{
    show_normal_withdraw_screen();
    short money_to_withdraw = 0;
    do
    {
        money_to_withdraw = mylibrary::read_num("Enter an amount multiple of 5's ?");
        if (money_to_withdraw > client.account_balance)
            cout << "\n\aThe amount exceeds your balance, make another choice.\n";

    } while ((money_to_withdraw % 5) != 0 || money_to_withdraw > client.account_balance);
    if (validate_choice("Are you sure you want to make this transaction? y/n? "))
        client.account_balance -= money_to_withdraw;
    vector <stclient> vclients = get_clients(file_name);
    for (stclient& clientt : vclients)
    {
        if (client.account_number == clientt.account_number)
        {
            clientt.account_balance = client.account_balance;
            break;
        }
    }
    update_clients_file(vclients, file_name);
}
void show_deposit_screen(void)
{
    cout << "=======================================\n";
    cout << "\t\tDeposit Screen";
    cout << "\n=======================================\n";
}
void deposit(stclient& client, string file_name)
{
    short money = 0;
    show_deposit_screen();
    do
    {
        money = mylibrary::read_num("Enter a positive Amount?");
    } while (money <= 0);
    client.account_balance += money;
    vector <stclient> vclients = get_clients(file_name);
    for (stclient& clientt : vclients)
    {
        if (client.account_number == clientt.account_number)
        {
            clientt.account_balance = client.account_balance;
            break;
        }
    }
    update_clients_file(vclients, file_name);
}
void atm_operations(stclient& client, string file_name, short op)
{
    system("cls");
    switch (op)
    {
    case 1:
        quick_withdraw(client, file_name);
        break;
    case 2:
        normal_withdraw(client, file_name);
        break;
    case 3:
        deposit(client, file_name);
        break;
    default:
        check_balance_screen();
        check_balance(client, file_name);
        break;
    }
}
void atm_client(stclient client, string file_name)
{
    short op = 0;
    do
    {
        system("cls");
        show_atm_main_menue_screen();
        op = read_operation(1, 5);
        if (op != 5)
        {
            atm_operations(client, file_name, op);
            //system("pause>0");
            cout << "\n\nPress any key to go back to Main Menue...";
            system("pause>0");
        }
        else
            login();
    } while (op);
}
void login(void)
{
    system("cls");
    show_login_screen();
    bool login_failed = true;
    stclient client;
    do
    {
        client = read_client();
        if (does_client_exist(client, "clients.txt"))
            atm_client(client, "clients.txt");
        else
        {
            login_failed = false;
            cout << "\nInvalid Account Number/PinCode!\n\a";
        }
    } while (!login_failed);
}
int main()
{
    login();
    return 0;
}
