# ATM Console Application

### Overview

This console application simulates an ATM (Automated Teller Machine) system where users can perform various banking operations such as quick withdrawals, normal withdrawals, deposits, and checking their account balance. The program is written in C++ and includes features to handle user authentication, account management, and transaction processing.

## Features
User Authentication:

Users can log in using their account number and PIN code.
Invalid login attempts are tracked, and users are notified of login failures.
Quick Withdrawal:

Users can choose predefined withdrawal amounts for quick transactions.
Normal Withdrawal:

Users can enter a custom withdrawal amount, subject to certain conditions (e.g., multiple of 5, not exceeding account balance).
Deposit:

Users can deposit funds into their accounts.
Check Balance:

Users can view their account balance.
Implementation Details
File Handling:

Client information is stored in a file ("clients.txt").
The application reads and updates client information from/to this file.
User Interface:

The application provides clear and user-friendly screens for each operation.
Menus guide users through available options.
How to Use
Login:

Launch the application and log in using your account number and PIN code.
Main Menu:

Choose from options such as quick withdrawal, normal withdrawal, deposit, and check balance.
Perform Transactions:

Follow on-screen instructions to complete transactions.
Logout:

Safely log out of the application.
Building and Running
The application is written in C++ and can be compiled and executed using a C++ compiler.
Requirements
C++ Compiler
