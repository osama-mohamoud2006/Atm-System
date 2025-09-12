ATM System (Extension 2)

This is an extension 2 of the original ATM System project. The core functionality for user transactions (quick/normal withdrawals, deposits, balance checks) remains intact, but this version introduces a secure login system for admins and advanced admin management with granular permission controls. Admins can now be created with specific permissions (e.g., allow balance checks but restrict withdrawals), and only authorized users can access sensitive operations. Data is persisted in text files, and the system uses a modular approach for efficient management.
The project is built in C++ and relies on a custom library (AllStuff.h) for utility functions like input handling and screen formatting. It’s designed for educational purposes, showcasing file I/O, structs, enums, vectors, and robust user authentication.

Table of Contents

New Enhancements
Features
Project Structure
Installation
Usage
Login and Admin Permissions
User Transactions
Admin Management


Data Storage
Custom Library Dependencies
Limitations
Future Improvements


New Enhancements
This extension builds on the original ATM project by adding:

Secure Admin Login System: Admins log in with a username and password stored in Admins.text. Only authenticated admins can access the system or specific operations.
Admin Management Module:
Create, delete, update, search, and list admins.
Assign permissions using bitwise flags (e.g., allow quick withdrawals but not deposits).
Full access (-1) or custom permissions for specific actions like viewing balances or managing users.


Permission Checks: Every operation verifies the logged-in admin’s permissions, preventing unauthorized access (e.g., a limited admin can check balances but can’t perform withdrawals).
Improved Security and Usability: Prevents self-deletion of the root admin ("admin"), handles invalid inputs gracefully, and uses color-coded feedback for errors/success.


Features
Core Features (from Original Project)

User Operations:
Quick Withdraw: Predefined amounts (20, 50, 100, 200, 400, 600, 800, 1000).
Normal Withdraw: Custom amounts (multiple of 5, within balance).
Deposit: Add funds to the account.
Check Balance: Display current user balance.
Logout: Return to login screen.


Data Persistence: User data (account number, PIN, name, phone, balance) stored in local db.text.

New Features (in this Extension)

Admin Operations:
List all admins with usernames, PINs, and permission levels.
Add new admins with full or custom permissions.
Delete admins (except the root "admin").
Update admin details and permissions.
Search for admins by username.


Permission System:
Bitwise enums for permissions (e.g., PQuickWithdraw = 1, PDeposit = 4).
Checks permissions before actions (e.g., CheckPermission(admin, PQuickWithdraw)).
Custom permission assignment during add/update (e.g., "Allow deposits? Y/N").


Login and Session Management:
Loads admins from Admins.text and verifies credentials.
Tracks the current logged-in admin for permission checks.
Logout returns to the login screen.



The system uses vectors of structs for in-memory data handling and rewrites files for persistence.

Project Structure

Main Components:

StUser struct: Holds user data (account number, PIN, name, phone, balance).
stadmins struct: Holds admin data (username, PIN, permissions as int).
Enums: enMainMenuOptions for main menu, EnQuickWithdrawOption for quick withdrawals, enAdminPermissions for access control.
Global Variables: File paths (path for users, AdminsPer for admins), delimiter (delmi = "#//#"), current user (CurrentUser).


Key Functions:

Data Handling: VectorThatHaveAllData(), ConvertLineToRecord(), SplitString(), EditFile(), UpdateAll().
User Operations: QuickWithdrawScreen(), ShowNoramlWithDrawScreen(), ShowDepositScreen(), CheckBalance(), logout().
Admin Operations: add_Admin(), delete_Admin(), update_admin(), find_admin(), show_admin_list() (to be implemented).
Permissions: CheckPermission(), GiveTheAdminFullAccess(), CustomAdminPer() (to be implemented).
Login: login(), IsUserAuthenticated().



The code is modular, with separate sections for user transactions, admin management, and authentication.

Installation

Prerequisites:

C++ compiler (e.g., g++ via MinGW or Visual Studio, C++11 or later).
Custom library: Ensure AllStuff.h is available at E:\projects\my library\AllStuff.h (or adjust the include path). This provides functions like screen_color(), enter_postive_number(), read_string().


Setup:

Clone or download the project files.
Create data files in the project directory:
local db.text: For user data (e.g., A123#//#1234#//#John Doe#//#1234567890#//#5000).
Admins.text: For admin data (e.g., admin#//#admin#//#-1 for root admin with full permissions).


Ensure file paths match the hardcoded path and AdminsPer variables or modify them.


Compile and Run:

Compile: g++ main.cpp -o atm_system
Run: ./atm_system



Note: Update the include path for AllStuff.h if it’s located elsewhere.

Usage
Login and Admin Permissions

Start the program: It opens the admin login screen.
Enter username and password (e.g., default: admin/admin).
Permissions control access:
Full access (permissions = -1): All operations.
Custom: Bitwise OR of enums (e.g., PQuickWithdraw | PCheckBalance allows quick withdrawals and balance checks but not deposits).


Error Message: "You don't have permission to access this section" if denied.

User Transactions

After admin login, users log in with account number and PIN.
Main menu (options 1-5):
Quick Withdraw: Select predefined amounts; validates balance and admin permissions.
Normal Withdraw: Enter custom amount (multiple of 5); checks balance and permissions.
Deposit: Add positive amount; confirms with admin permissions.
Check Balance: View current balance (permission-checked).
Logout: Return to user login screen.


Admin must have relevant permissions (e.g., PQuickWithdraw for quick withdrawals).

Admin Management

Main menu option (to be added, e.g., option 6): Opens admin sub-menu.
Operations (to be implemented):
Add: Prompt for username, PIN, and permissions (full or custom via Y/N prompts).
Delete: Prevent deletion of root admin ("admin").
Update: Modify PIN and permissions.
Search: Find admin by username.
List: Show all admins with details.


Data Format in Admins.text: username#//#pin#//#permissions

Press any key to return to menus after operations.

Data Storage

Users: local db.text – One line per user, delimited by #//#.
Format: account_number#//#pin#//#name#//#phone#//#balance
Example: A123#//#1234#//#John Doe#//#1234567890#//#5000


Admins: Admins.text – One line per admin, including permission integer.
Format: username#//#pin#//#permissions
Example: admin#//#admin#//#-1 (full access)


Files are read into vectors on load, modified in memory, and rewritten after changes.


Custom Library Dependencies
Relies on AllStuff.h for:

Input Handling: read_string(), enter_postive_number(), enter_number_from_to().
UI: screen_color() (e.g., red for errors, black for normal text).
If AllStuff.h is unavailable, implement these functions or adjust the code to use standard C++ alternatives.


Limitations

Incomplete Admin Features: Admin management (add/delete/update/search/list) and permission checks are not implemented in the provided code and need to be added.
Custom Library Dependency: Relies on AllStuff.h, which is not provided.
Hardcoded Paths: File paths (E:\projects\my library\AllStuff.h, local db.text) may need adjustment.
Security: PINs are stored in plain text, unsuitable for production use.
Single User Session: Only one user can be logged in at a time (CurrentUser).


Future Improvements

Implement admin management module (add/delete/update/search/list admins).
Add bitwise permission checks for all operations.
Encrypt PINs and sensitive data in files.
Support multiple concurrent user sessions.
Make file paths configurable (e.g., via command-line arguments).
Enhance input validation (e.g., account number format, PIN length).
Add user registration for self-service account creation.
