
# Bank Management System

## Overview

This project is an intermediate-to-advanced level Bank Management System implemented in C++. It allows users to manage bank accounts with various functionalities such as opening accounts, depositing money, withdrawing money, transferring funds between accounts, and closing accounts. Additionally, the system maintains transaction histories and allows users to search for accounts by the account holder's name.

## Features

1. **Open New Account**
   - Allocates memory for a new account.
   - Generates a unique account number.
   - Stores account holder's details (name, address, phone, email).
   - Generates a secure 4-digit PIN for the account.

2. **Deposit Money**
   - Deposits a specified amount into the account.
   - Updates the account balance.
   - Records the transaction in the account's history.

3. **Withdraw Money**
   - Withdraws a specified amount from the account, if sufficient funds are available.
   - Updates the account balance.
   - Records the transaction in the account's history.

4. **Transfer Money**
   - Transfers a specified amount from one account to another.
   - Ensures sufficient funds are available in the source account.
   - Updates the balances of both accounts.
   - Records the transaction in the accounts' histories.

5. **Check Account Balance**
   - Displays the current balance of the account.

6. **Close Account**
   - Frees the memory allocated for the account.
   - Removes the account from the system.

7. **Show Transaction History**
   - Displays the transaction history of the account.

8. **Find Account by Name**
   - Searches for accounts by the account holder's name.
   - Displays account details and balance.

## User Interface

The user interface is a command-line interface (CLI) that provides a menu for users to select various actions. The menu options are:

1. Open Account
2. Close Account
3. Deposit
4. Withdraw
5. Transfer
6. Show Transaction History
7. Find Account by Name
8. Exit
