#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "mylibrary.h"
using namespace std;
void manage_users_operation(string file_name_users, string file_name_clients, short op, int permissions);
void manage_users(string file_name_users, string file_name_clients, int permissions);
void bank_operation(string file_name_clients, string file_name_users, short op, int permissions);
void bank(string file_name_clients, string file_name_users, int permissions);
void transaction(string file_name_clients, string file_name_users, int permessions);


void login();

struct stuser
{
    string username = "";
    string password = "";
    int permissions = 0;
    bool mark_for_delete = false;
};
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
        cout << "couldn't not open file!!";
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
    cout << "___________________________________________________\n";
    cout << "\t\tAdd New Client Screen\n";
    cout << "___________________________________________________\n";
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

void show_clients_header(size_t num)
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
void update_clients_file(string file_name, vector<stclient>vclients)
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
    cout << "___________________________________________________\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "___________________________________________________\n";
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
            update_clients_file(file_name, vclients);
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
    cout << "___________________________________________________\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "___________________________________________________\n";
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
            update_clients_file(file_name, vclients);
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
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
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
    cout << "___________________________________________________\n";
    cout << "\t\tFind Client Screen\n";
    cout << "___________________________________________________\n";
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

void show_transaction_menue()
{
    cout << "===================================\n";
    cout << "        Transaction Menue Screen\n";
    cout << "===================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===================================\n";
}
void deposit(string file_name_clients, string file_name_users, int permessions)
{
    vector <stclient> vclients = get_clients(file_name_clients);
    bool found = false;
    string account_number;

    account_number = mylibrary::read_string("Please enter account number:");
    for (stclient& client : vclients)
    {
        if (client.account_number == account_number)
        {
            print_client(client);
            found = true;
            int amount = mylibrary::read_num("Please enter deposit amount?");
            client.account_balance = to_string(stoi(client.account_balance) + amount);
            break;
        }
    }
    if (!found)
    {
        cout << "Client with account number (" << account_number << ") does not exist!\n\n\n";
        system("pause");
        transaction(file_name_clients, file_name_users, permessions);
    }
    update_clients_file(file_name_clients, vclients);
}
void withdraw(string file_name_clients, string file_name_users, int permessions)
{
    vector <stclient> vclients = get_clients(file_name_clients);
    bool found = false;
    string account_number;

    account_number = mylibrary::read_string("Please enter account number:");
    for (stclient& client : vclients)
    {
        if (client.account_number == account_number)
        {
            print_client(client);
            found = true;
            int amount;
            do
            {
                amount = mylibrary::read_num("\nPlease enter withdraw amount?");
                if (amount > stoi(client.account_balance))
                {
                    cout << "\nAmount Exceeded the balance, you can withdraw up to: " << client.account_balance;
                }
            } while (amount > stoi(client.account_balance));
            client.account_balance = to_string(stoi(client.account_balance) - amount);
            break;
        }
    }
    if (!found)
    {
        cout << "Client with account number (" << account_number << ") does not exist!\n\n\n";
        system("pause");
        transaction(file_name_clients, file_name_users, permessions);
    }
    update_clients_file(file_name_clients, vclients);
}
void show_clients_balance_header(size_t num)
{
    cout << "\n         Balance List (" << num << ") Clients (s)";
    cout << endl;
    cout << "___________________________________________________\n";
    cout << "| Account Number| Client Name           | Balance |\n";
    cout << "___________________________________________________\n";
}
void show_client_balance(stclient client)
{
    cout << "|" << left << setw(16) << client.account_number << "|";
    cout << left << setw(23) << client.name << "|";
    cout << left << setw(9) << client.account_balance << "|";
}
void total_balances(string file_name)
{
    vector <stclient> vclients;
    vclients = get_clients(file_name);
    show_clients_balance_header(vclients.size());
    short total_balances = 0;
    for (stclient& client : vclients)
    {
        show_client_balance(client);
        total_balances += stoi(client.account_balance);
        cout << endl;
    }
    cout << "___________________________________________________\n";
    cout << "\t Total Balances = " << total_balances << "\n\n";
    cout << "\nPress any key to go back to Transaction Menue...";
    system("pause>0");

}
void transaction_operation(string file_name_clients, string file_name_users, short op, int permissions)
{
    switch (op)
    {
    case 1:
        system("cls");
        deposit(file_name_clients, file_name_users, permissions);
        transaction(file_name_clients, file_name_users, permissions);
        break;
    case 2:
        system("cls");
        withdraw(file_name_clients, file_name_users, permissions);
        transaction(file_name_clients, file_name_users, permissions);
        break;
    case 3:
        system("cls");
        total_balances(file_name_clients);
        system("pause>0");
        transaction(file_name_clients, file_name_users, permissions);
        break;
    default:
        system("cls");
        bank(file_name_clients, file_name_users, permissions);
    }
}
void transaction(string file_name_clients, string file_name_users, int permissions)
{
    short op = 0;
    system("cls");
    show_transaction_menue();
    do
    {
        op = mylibrary::read_num("Choose What do you want to do? [1 to 4]?");
        if (op < 1 || op > 4)
            cout << "\nPlease enter a number between [1 and 4]:\n";
    } while (op < 1 || op > 4);
    transaction_operation(file_name_clients, file_name_users, op, permissions);
}
bool does_user_exist(stuser &user, string file_name);
void manage_users(string file_name);
vector <stuser> get_users(string file_name);
void show_manage_users_menue()
{
    cout << "===================================\n";
    cout << "        Manage Users Menue Screen\n";
    cout << "===================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===================================\n";
}
void show_list_users_header(void)
{
    cout << "\n--------------------------------------------------------\n";
    cout << "| User Name     | Password   | Permissions";
    cout << "\n--------------------------------------------------------\n";

}
void show_user(stuser user)
{
    cout << '|'<< setw(15) << user.username ;
    cout << '|' << setw(12) << user.password;
    cout << '|' << setw(4) << user.permissions;
    cout << endl;
}
void list_users(string file_name)
{
    vector<stuser>vusers = get_users(file_name);
    cout << "\t\t Users List (" << vusers.size() << ") Users(s).";
    show_list_users_header();
    for (stuser& user : vusers)
        show_user(user);
    cout << "\n--------------------------------------------------------\n";
}
void show_add_new_user_screen(void)
{
    cout << "\n---------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n---------------------------------\n";
}
bool does_user_name_exist(stuser &user, string file_name)
{
    vector <stuser> vusers = get_users(file_name);
    for (stuser& userr : vusers)
    {
        if (user.username == userr.username)
        {
            user = userr;
            return 1;
        }
        
    }
    return 0;
}
string stuser_to_line(stuser user, string delim)
{
    string str = "";
    str += user.username + delim;
    str += user.password + delim;
    str += to_string(user.permissions);
    return str;
}
void add_new_user_to_file(stuser user, string file_name)
{
    fstream file;
    file.open(file_name, ios::out | ios::app);
    string str = stuser_to_line(user, "#//#");
    if (file.is_open())
    {
        file << str << endl;
        file.close();
    }
    else
        cout << "couldn't not open file!!";

}
enum enpermessions {
    enlist_clients = 1, enadd_new_client = 2, endelete_client = 4, enupdate_client = 8, enfind_client = 16, entransactions = 32, enmanage_users = 64
};
int show_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Show client list?");
    if (c == 'y')
        return permesstions | 1;
    else
        return permesstions;

}
int add_new_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Add new client?");
    if (c == 'y')
        return permesstions | 2;
    else
        return permesstions;

}
int delete_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Delete client?");
    if (c == 'y')
        return permesstions | 4;
    else
        return permesstions;

}
int update_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Update client?");
    if (c == 'y')
        return permesstions | 8;
    else
        return permesstions;

}
int find_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Find client?");
    if (c == 'y')
        return permesstions | 16;
    else
        return permesstions;

}
int transactions_client_permession(int permesstions)
{
    char c = mylibrary::read_char("Transactions?");
    if (c == 'y')
        return permesstions | 32;
    else
        return permesstions;
}
int manage_users_permession(int permesstions)
{
    char c = mylibrary::read_char("Manager users?");
    if (c == 'y')
        return permesstions | 64;
    else
        return permesstions;
}
int add_user_permissions()
{
    int permesstions = 0;
    char c = mylibrary::read_char("Do you want to give full access? y/n ?");
    if (c == 'y')
        return -1;
    else
    {
        permesstions = show_client_permession(permesstions);
        permesstions = add_new_client_permession(permesstions);
        permesstions = delete_client_permession(permesstions);
        permesstions = update_client_permession(permesstions);
        permesstions = find_client_permession(permesstions);
        permesstions = transactions_client_permession(permesstions);
        permesstions = manage_users_permession(permesstions);
    }
    return permesstions;
    
}
bool check_add_new_user() {
    char c = mylibrary::read_char("\nUser added succesfully, Do you want to add new user? y/n?");
    return (c == 'y');
}
void add_new_user(string file_name)
{
    show_add_new_user_screen();
    bool add_new_use = true;
    do
    {
        bool user_exist = true;
        stuser user;
        do
        {
            user.username = mylibrary::read_string("Enter Username?");
            user_exist = does_user_name_exist(user, file_name);
            if (user_exist)
                cout << "User with [" << user.username << "] already exists, ";
        } while (user_exist);
        user.password = mylibrary::read_string("Enter Password?");
        user.permissions = add_user_permissions();
        add_new_user_to_file(user, file_name);
        add_new_use = check_add_new_user();
    } while (add_new_use);
}
void print_user(stuser user)
{
    cout << "\n-----------------------------\n";
    cout << "Username    : " << user.username << endl;
    cout << "Password    : " << user.password << endl;
    cout << "Permessions : " << user.permissions;
    cout << "\n-----------------------------\n";
}
bool check_for_delete(void)
{
    char c = mylibrary::read_char("Are you sure you want to delete this user? y/n? ");
    return (c == 'y');
}
void update_users_file(string file_name, vector <stuser> vusers)
{
    fstream file;
    file.open(file_name, ios::out);
    file.close();
    for (stuser& user : vusers)
    {
        if(!user.mark_for_delete)
            add_new_user_to_file(user, file_name);
    }
}
void delete_user(string file_name)
{
    stuser user;
    cout << "___________________________________________________\n";
    cout << "\t\Delete User Screen\n";
    cout << "___________________________________________________\n";
    user.username = mylibrary::read_string("Please enter username? ");
    if (does_user_name_exist(user, file_name))
    {
        vector <stuser> vusers = get_users(file_name);
        print_user(user);
        if (check_for_delete())
        {
            for(stuser &userr:vusers)
            {
                if (userr.username == user.username)
                {
                    userr.mark_for_delete = true;
                    break;
                }
            }
        }
        update_users_file(file_name, vusers);
    }
    else
        cout << "\nUser [" << user.username << "] does not exist!";
}
bool check_for_update(void)
{
    char c = mylibrary::read_char("Are you sure you want to update this client? y/n? ");
    return (c == 'y');
}
void update_user_by_username(stuser& user)
{
    user.password = mylibrary::read_string("Enter password? ");
    user.permissions = add_user_permissions();
}
void update_user(string file_name)
{
    stuser user;
    cout << "___________________________________________________\n";
    cout << "\t\tUpdate User Screen\n";
    cout << "___________________________________________________\n";
    user.username = mylibrary::read_string("Please enter username? ");
    if (does_user_name_exist(user, file_name))
    {
        vector <stuser> vusers = get_users(file_name);
        print_user(user);
        if (check_for_update())
        {
            for (stuser& userr : vusers)
            {
                if (userr.username == user.username)
                {
                    update_user_by_username(userr);
                    break;
                }
            }
        }
        update_users_file(file_name, vusers);
    }
    else
        cout << "\nUser [" << user.username << "] does not exist!";
}
void find_user(string file_name)
{
    stuser user;
    cout << "___________________________________________________\n";
    cout << "\t\tFind client Screen\n";
    cout << "___________________________________________________\n";
    user.username = mylibrary::read_string("Please enter Username? ");
    if (does_user_name_exist(user, file_name))
        print_user(user);
    else
        cout << "\nUser with username [" << user.username << "] does not exist!\a";
}
void manage_users_operation(string file_name_users, string file_name_clients, short op, int permissions)
{
    switch (op)
    {
    case 1:
        system("cls");
        list_users(file_name_users);
        system("pause>0");
        break;
    case 2:
        system("cls");
        add_new_user(file_name_users);
        break;
    case 3:
        system("cls");
        delete_user(file_name_users);     
        break;
    case 4:
        system("cls");
        update_user(file_name_users);
        break;
    case 5:
        system("cls");
        find_user(file_name_users);
        system("pause>0");
        break;
    default:
        system("cls");
        bank(file_name_clients, file_name_users, permissions);
    }
}
void manage_users(string file_name_users, string file_name_clients, int permissions)
{
    short op = 0;
    do
    {
        system("cls");
        show_manage_users_menue();
        op = mylibrary::read_num("Choose What do you want to do? [1 to 6]?");
        if (op < 1 || op > 6)
            cout << "\nPlease enter a number between [1 and 6]:\n";

        manage_users_operation(file_name_users, file_name_clients, op, permissions);
    } while (op >= 1 || op <= 6);
   
}
void show_permession_denied(void)
{
    cout << "\n---------------------------------\n";
    cout << "Access Denied, you don't have the Permession to do this,\nPlease contact Your Admin.";
    cout << "\n---------------------------------\n";
}
bool show_client_list_permession_check(int permessions)
{
    return (permessions & enlist_clients) != 0;
}
bool add_new_client_permession_check(int permessions)
{
    return (permessions & enadd_new_client) != 0;
}
bool delete_client_permession_check(int permessions)
{
    return (permessions & endelete_client) != 0;
}
bool update_client_permession_check(int permessions)
{
    return (permessions & enupdate_client) != 0;
}
bool find_client_permession_check(int permessions)
{
    return (permessions & enfind_client) != 0;
}
bool transactions_permession_check(int permessions)
{
    return (permessions & entransactions) != 0;
}
bool manage_users_permession_check(int permessions)
{
    return (permessions & enmanage_users) != 0;
}
void bank_operation(string file_name_clients, string file_name_users, short op, int permissions)
{
    switch (op)
    {
    case 1:
        system("cls");
        if(show_client_list_permession_check(permissions) || permissions == -1)
            show_client_list(file_name_clients);
        else
            show_permession_denied();
        break;
    case 2:
        system("cls");
        if (add_new_client_permession_check(permissions) || permissions == -1)
            add_new_client(file_name_clients);
        else
            show_permession_denied();
        break;
    case 3:
        system("cls");
        if(delete_client_permession_check(permissions) || permissions == -1)
            delete_client_by_account_number(file_name_clients);
        else
            show_permession_denied();
        break;
    case 4:
        system("cls");
        if (update_client_permession_check(permissions) || permissions == -1)
            update_client_by_account_number(file_name_clients);
        else
            show_permession_denied();
        break;
    case 5:
        system("cls");
        if (find_client_permession_check(permissions) || permissions == -1)
            find_client(file_name_clients);
        else
            show_permession_denied();
        break;
    case 6:
        system("cls");
        if (transactions_permession_check(permissions) || permissions == -1)
            transaction(file_name_clients, file_name_users, permissions);
        else
            show_permession_denied();
        break;
    case 7:
        system("cls");
        if (manage_users_permession_check(permissions) || permissions == -1)
            manage_users(file_name_users, file_name_clients, permissions);
        else
            show_permession_denied();
        break;
    default:
        system("cls");
        cout << "\a";
        cout << "\nPlease enter a valid number between 1 to 7!\n";
        return;
    }
}
void bank(string file_name_clients, string file_name_users, int permissions)
{
    short num = 0;
    do
    {
        system("cls");
        show_main_menue_screen();
        num = mylibrary::read_num("Choose what do you want to do? [1 to 8]?");
        if (num != 8)
        {
            bank_operation(file_name_clients, file_name_users, num, permissions);
            cout << "\nPress any key to go back to Main Menue...";
            system("pause>0");
            system("cls");
        }
        else
        {
            system("cls");
            login();
            return;
        }
    } while (num != 8);
}
void show_login_screen()
{
    cout << "___________________________________________________\n";
    cout << "\t\tLogin Screen\n";
    cout << "___________________________________________________\n";
}
stuser enter_user(void)
{
    stuser user;
    user.username = mylibrary::read_string("Enter Username?:");
    user.password = mylibrary::read_string("Enter Password?:");
    return user;
}
stuser line_to_stuser(string str, string delim)
{
    stuser user;
    vector<string>vstring = split_string(str, delim);
    user.username = vstring[0];
    user.password = vstring[1];
    user.permissions = stoi(vstring[2]);
    return user;
}
vector <stuser> get_users(string file_name)
{
    string str = "";
    vector <stuser> vusers;
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        while (getline(file, str))
        {
            vusers.push_back(line_to_stuser(str, "#//#"));
        }
        file.close();
    }
    return vusers;
}
bool does_user_exist(stuser &user, string file_name)
{
    vector <stuser> vusers = get_users(file_name);
    for (stuser& userr : vusers)
    {
        if (user.username == userr.username&& user.password == userr.password)
        {
            user.permissions = userr.permissions;
            user.password =userr.password;
            return 1;
        }
    }
    return 0;
}
void login()
{
    show_login_screen();
    bool user_exist = true;
    stuser user;
    do
    {
        user = enter_user();
        user_exist = does_user_exist(user, "users.txt");
        if (!user_exist)
            cout << "Invalid Username/Password!\n";
    } while (!user_exist);
    bank("clients.txt", "users.txt", user.permissions);
}
int main()
{
    login();
    return 0;
}
