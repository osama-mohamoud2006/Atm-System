#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<string>
#include<cctype>
#include<iomanip>
#include"E:\projects\my library\AllStuff.h"  
using namespace AllStuff;
using namespace std;

struct StUser {
string account_number = " "; // this is the main key which is very importat to manage data 
string pin = " ";
string name = " ";
string phone = " ";
int account_balance = 0;

};
struct StUser CurrentUser;
enum enMainMenuOptions{eQuickWithdraw=1 , eNormalWithdraw=2 ,eDposit=3 , eCheckBalance=4 ,eLogout=5 };
void login();
const string path = "local db.text"; // Clients
const string delmi = "#//#";
///////////////////////////////////////////////////////////////////////////

// things to use in  options
void back_to_menu(string TextAppearWhenYouBack = "press any key to back to main menu !") {
	screen_color(black);
	cout << "\033[1;31m";
	cout << "\n " << TextAppearWhenYouBack << endl;
	cout << "\033[0m";
	system("pause>0");

}
void print_menu_option(string option_name) {
	cout << "\n_________________________________________________\n\n\n";
	cout << "\t" << option_name << "\n";
	cout << "\n_________________________________________________\n";
}


vector<string> SplitString(string LineOfData , string delmi= "#//#") {

	vector<string> res; 
	
	short pos;
	string sword;

	while ((pos = LineOfData.find(delmi)) != string::npos) {

		sword = LineOfData.substr(0, pos);
		if (sword != "") res.push_back(sword);

		LineOfData.erase(0, pos + delmi.length());
	}

	if(LineOfData!="")  res.push_back(LineOfData);

	return res;
}

// will convert the string into data in struct 
StUser ConvertLineToRecord(string LineOfData) {
	
	
	if (LineOfData == "") {
		screen_color(red);
		cout << "\n\aError !" << endl;
		exit(0);
	}

	StUser user;
	vector<string> DataSplited= SplitString(LineOfData,delmi);

	user.account_number = DataSplited.at(0);//--> i care about it
	user.pin = DataSplited.at(1);//--> i care about it
	user.name = DataSplited.at(2);
	user.phone = DataSplited.at(3);
	user.account_balance =stoi(DataSplited.at(4)); //--> i care about it

	return user; 
}

// convert struct to line(string) 
string ConvertRecordToLine(StUser UserData) {
return (UserData.account_number + delmi + (UserData.pin) + delmi + UserData.name + delmi + UserData.phone + delmi + to_string(UserData.account_balance));
}

// read file content and push it to vector of struct
vector<StUser> VectorThatHaveAllData(string path) {
	vector<StUser> data;
	fstream read;
	read.open(path, ios::in); // read mode
	if (read.is_open()) 
	{
		string line = "";
		StUser user;
		while (getline(read, line)) {

			user = ConvertLineToRecord(line);
			data.push_back(user);
		}
		read.close();
	}
	else 
	{
		screen_color(red);
		cout << "\a\nCouldn't open the file!\n";
	}

	return data;
}


//update current user
void UpdateCurrentUser(StUser &CurrentUserToUpdate , vector<StUser>&VectorThatHaveAllData) {

	for (StUser& U : VectorThatHaveAllData) {
		if (CurrentUserToUpdate.account_number == U.account_number) {
			CurrentUserToUpdate = U;
			break;
		}
	}
}

// write the edited vector on file again 
void EditFile(vector<StUser> &VectorThatHaveAllData , string path) 
{
	// take the edited vector and push the data into file

	fstream write;
	write.open(path, ios::out); // overwriting

	if (write.is_open())
	{
		string line;
		for (StUser& Vdata : VectorThatHaveAllData) {

			line = ConvertRecordToLine(Vdata);
			write << line << endl;
		}
		write.close();
	}
	else
	{
		screen_color(red);
		cout << "\a\nCouldn't open the file!\n";
	}

}

bool EnterY_N() {
	char c;
	cin >> c;
	return (toupper(c) == 'Y'); // return true if it is yes 
}

bool IsAccountNumberExistInVector(StUser UserFromVectorThatHaveAllClients , StUser User) {

	

	if (UserFromVectorThatHaveAllClients.account_number == User.account_number) {
		return true;
	}
	else return false; 
	
}

bool ConfrimOperation(string OperationName) {

	cout << "\n\nAre you sure you want to perform " << OperationName << " [y],[n]: ";
	if (EnterY_N()) return true; // return true if it is true
	else return false; 
}

void DepositMainLogic(vector<StUser>& VectorThatHaveAllClients, int amount ) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (IsAccountNumberExistInVector(U, CurrentUser) == true) {
			U.account_balance += amount;
			break;
		}
	}
	EditFile(VectorThatHaveAllClients, path); // update file
	VectorThatHaveAllClients= VectorThatHaveAllData(path);//refresh vector 
	UpdateCurrentUser(CurrentUser, VectorThatHaveAllClients);
}

// option [3]
void ShowDepositScreen(vector<StUser>& VectorThatHaveAllClients) {

	print_menu_option("Deposit Screen");

	int AmountToDeposit = enter_postive_number("\nEnter a positive Deposit Amount: ");

	if (ConfrimOperation("Deposit")) {
		DepositMainLogic(VectorThatHaveAllClients, AmountToDeposit);
		cout << "\nDone Successfully. " << "Now balance is: " << CurrentUser.account_balance << endl;
	}
	else {
		cout << "\n\a No Changes On User's Balance!\n\n";
	}
}


// option [4]
void CheckBalance(StUser CurentUserBalance) {
	cout << "\n\n\t\t The User \"" << CurentUserBalance.name<<"\" 's account balance is: "<< CurentUserBalance.account_balance << endl;
}

// option [5]
void logout() {
	login();
}



void ImplementOptionAccordingToUserChoice(enMainMenuOptions Option ,vector<StUser>& VectorThatHaveAllClients) {

	switch (Option) {
	case enMainMenuOptions::eQuickWithdraw:
		system("cls");
		cout << "\nwill be QuickWithdraw soon!\n";
		back_to_menu();
		break;

	case enMainMenuOptions::eNormalWithdraw:
		system("cls");
		cout << "\nwill be Normal Withdraw soon!\n";
		back_to_menu();
		break;

	case enMainMenuOptions::eDposit:
		system("cls");
		ShowDepositScreen(VectorThatHaveAllClients);
		back_to_menu();
		break;

	case enMainMenuOptions::eCheckBalance:
		system("cls");
		CheckBalance( CurrentUser);
		back_to_menu();
		break;

	case enMainMenuOptions::eLogout:
		system("cls");
		logout();
		break;
	}
}
void main_menu() {
	system("cls");
	screen_color(black);
	cout << setw(5) << "\tWelcome to Atm System! ";
	cout << "\n_____________________________________________________\n\n";
	cout << setw(5) << "please enter the number of the option you want: \n" << endl;

	cout << setw(4) << "\t[1] Quick Withdraw." << endl;
	cout << setw(4) << "\t[2] Normal Withdraw." << endl;
	cout << setw(4) << "\t[3] Deposit." << endl;
	cout << setw(4) << "\t[4] Check Balance." << endl;
	cout << setw(4) << "\t[5] logout." << endl;
	cout << "\n_____________________________________________________\n\n";
	cout << "Please enter the option you want: ";


}

void Start(vector<StUser> &VectorThatHaveAllClients) {

	enMainMenuOptions choice ;
	do {
	system("cls");
     main_menu(); // call main menu normally (print) 
	 choice = (enMainMenuOptions)enter_postive_number("");
	 ImplementOptionAccordingToUserChoice(choice, VectorThatHaveAllClients);

	} while (choice!= enMainMenuOptions::eLogout);
	
}

//return true if found user 
bool FindUserByAccountNumber(string account_number, StUser& currentUser, vector<StUser>& VectorThatHaveAllData) {

	for (StUser& U : VectorThatHaveAllData)
	{
		if (U.account_number == account_number) {
			currentUser = U;
			return true;
		}
	}
	return false;
}

//check password and the account number 
bool IsUserAuthenticated(string account_number, string Pin, StUser& currentUser, vector<StUser>& VectorThatHaveAllData) {

	if (FindUserByAccountNumber(account_number, currentUser, VectorThatHaveAllData)) {

		if (currentUser.pin == Pin) return true;
		else return false;
	}
	return false;
}

void login() {

	vector<StUser> VectorThatHaveAllClients = VectorThatHaveAllData(path);

	bool check = false; 
	do {
		system("cls");
		screen_color(black);
		print_menu_option("Login");
		string AccountNumber = read_string("\nenter Account Number: ");
		string Pin = read_string("\nenter Pin: ");

		if (IsUserAuthenticated(AccountNumber,Pin,CurrentUser, VectorThatHaveAllClients))
		{
			Start(VectorThatHaveAllClients); // start the program after logining in
			check = true;
		}
		else {
			screen_color(red);
			cout << "\nIncorrect password or user!\n\a";
		}

	} while (check == false);

}

int main() {
	login();
	return 0;
}