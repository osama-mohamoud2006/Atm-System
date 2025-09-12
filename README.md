# ATM System (Extension 2)

![ATM System](https://img.shields.io/badge/Status-Active-brightgreen)
![C++](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Version](https://img.shields.io/badge/Version-2.0-orange)
![License](https://img.shields.io/badge/License-MIT-green)

This is an **ATM System project** .

The project is built in C++ and relies on a custom library (`AllStuff.h`) for utility functions like input handling and screen formatting. It’s designed for educational purposes, showcasing file I/O, structs, enums, vectors, and robust user authentication.

---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
  - [User Transactions](#user-transactions)
- [Data Storage](#data-storage)
- [Custom Library Dependencies](#custom-library-dependencies)

---



## Features

### Core Features 
- **User Operations**:
  - Quick Withdraw: Predefined amounts (20, 50, 100, 200, 400, 600, 800, 1000).
  - Normal Withdraw: Custom amounts (multiple of 5, within balance).
  - Deposit: Add funds to the account.
  - Check Balance: Display current user balance.
  - Logout: Return to login screen.
- **Data Persistence**: User data (account number, PIN, name, phone, balance) stored in `local db.text`.


## Project Structure

- **Main Components**:
  - `StUser` struct: Holds user data (account number, PIN, name, phone, balance).
  - Enums: `enMainMenuOptions` for main menu, `EnQuickWithdrawOption` for quick withdrawals.
  - Global Variables: File path (`path` for users), delimiter (`delmi = "#//#"`), current user (`CurrentUser`).

- **Key Functions**:
  - **Data Handling**: `VectorThatHaveAllData()`, `ConvertLineToRecord()`, `SplitString()`, `EditFile()`, `UpdateAll()`.
  - **User Operations**: `QuickWithdrawScreen()`, `ShowNoramlWithDrawScreen()`, `ShowDepositScreen()`, `CheckBalance()`, `logout()`.
  - **Login**: `login()`, `IsUserAuthenticated()`.

The code is modular, with separate sections for user transactions and authentication.

---

## Installation

1. **Prerequisites**:
   - C++ compiler (e.g., g++ via MinGW or Visual Studio, C++11 or later).
   - Custom library: Ensure `AllStuff.h` is available at `E:\projects\my library\AllStuff.h` (or adjust the include path). This provides functions like `screen_color()`, `enter_postive_number()`, `read_string()`.

2. **Setup**:
   - Clone or download the project files.
   - Create data files in the project directory:
     - `local db.text`: For user data (e.g., `A123#//#1234#//#John Doe#//#1234567890#//#5000`).
   - Ensure file paths match the hardcoded `path` and `AdminsPer` variables or modify them.

3. **Compile and Run**:
   - Compile: `g++ main.cpp -o atm_system`
   - Run: `./atm_system`

Note: Update the include path for `AllStuff.h` if it’s located elsewhere.

---

## Usage

### User Transactions
- After user log in with account number and PIN.
- Main menu (options 1-5):
  - Quick Withdraw: Select predefined amounts; validates balance and admin permissions.
  - Normal Withdraw: Enter custom amount (multiple of 5); checks balance and permissions.
  - Deposit: Add positive amount; confirms with admin permissions.
  - Check Balance: View current balance (permission-checked).
  - Logout: Return to user login screen.
  
Press any key to return to menus after  Any operation.

---

## Data Storage

- **Users**: `local db.text` – One line per user, delimited by `#//#`.
  - Format: `account_number#//#pin#//#name#//#phone#//#balance`
  - Example: `A123#//#1234#//#John Doe#//#1234567890#//#5000`

- Files are read into vectors on load, modified in memory, and rewritten after changes.

---

## Custom Library Dependencies

Relies on `AllStuff.h` for:
- **Input Handling**: `read_string()`, `enter_postive_number()`, `enter_number_from_to()`.
- **UI**: `screen_color()` (e.g., red for errors, black for normal text).
- If `AllStuff.h` is unavailable, implement these functions or adjust the code to use standard C++ alternatives.

---

---

