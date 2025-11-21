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
bool MarkForDelete = false;

};
struct StUser CurrentUser;
enum enMainMenuOptions{eQuickWithdraw=1 , eNormalWithdraw=2 ,eDposit=3 , eCheckBalance=4 ,eUserInfo=5 ,eDeleteAccount=6 , eChangePassword=7 ,eLogout=8 };
void login();
void logout();
const string path = "local db.text"; // Clients
const string delmi = "#//#";
///////////////////////////////////////////////////////////////////////////

// things to use in  options
//void back_to_menu(string TextAppearWhenYouBack = "press any key to back to main menu !") {
//	screen_color(black);
//	cout << "\033[1;31m";
//	cout << "\n " << TextAppearWhenYouBack << endl;
//	cout << "\033[0m";
//	system("pause>0");
//
//}
void print_menu_option(string option_name) {
	cout << "\n_________________________________________________\n\n\n";
	cout << "\t" << option_name << "\n";
	cout << "\n_________________________________________________\n";
}


//vector<string> SplitString(string LineOfData , string delmi= "#//#") {
//
//	vector<string> res; 
//	
//	short pos;
//	string sword;
//
//	while ((pos = LineOfData.find(delmi)) != string::npos) {
//
//		sword = LineOfData.substr(0, pos);
//		if (sword != "") res.push_back(sword);
//
//		LineOfData.erase(0, pos + delmi.length());
//	}
//
//	if(LineOfData!="")  res.push_back(LineOfData);
//
//	return res;
//}

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
void UpdateCurrentUser(StUser& CurrentUserToUpdate, vector<StUser>& VectorThatHaveAllData) {

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
			if (Vdata.MarkForDelete == false) { // if it isn't marked for delete 
				line = ConvertRecordToLine(Vdata);
				write << line << endl;
			}
		}
		write.close();
	}
	else
	{
		screen_color(red);
		cout << "\a\nCouldn't open the file!\n";
	}

}


// update the vector and file 
void UpdateAll(vector<StUser>& VectorThatHaveAllClients) {
	EditFile(VectorThatHaveAllClients, path); // update file
	VectorThatHaveAllClients = VectorThatHaveAllData(path);//refresh vector 
	UpdateCurrentUser(CurrentUser, VectorThatHaveAllClients);//update the global var
}

bool EnterY_N() {
	char c;
	cin >> c;
	return (toupper(c) == 'Y'); // return true if it is yes 
}

bool IsAccountNumberExistInVector(StUser UserFromVectorThatHaveAllClients , StUser User) {
	return (UserFromVectorThatHaveAllClients.account_number == User.account_number);
}


bool ConfrimOperation(string OperationName) {
cout << "\n\nAre you sure you want to perform " << OperationName << " [y],[n]: ";
if (EnterY_N()) return true; // return true if it is true
else return false;
}

////////////////////////////////////////////////////////////////////////////////////////////

enum EnQuickWithdrawOption{Twenty=1 , Fifty=2, OneHundered=3 , TwoHundered=4 , FourHunderd=5 ,
	SixHundered=6, EigthHundered=7, OneThousand=8 , eExit=9};

void QuickWithDrawMainMenu() {

	print_menu_option("Quick Withdraw");
	screen_color(black);
	cout << "\n" << setw(9) << "[1] 20" << setw(15) << "[2] 50" << endl;
	cout << "\n" << setw(10) << "[3] 100" << setw(15) << "[4] 200" << endl;
	cout << "\n" << setw(10) << "[5] 400" << setw(15) << "[6] 600" << endl;
	cout << "\n" << setw(10) << "[7] 800" << setw(16) << "[8] 1000" << endl;
	cout << "\n" << "\t  " << "[9] Exit" << endl;
	cout << "\n=======================================\n";
	cout << "\nYour balance is: " << CurrentUser.account_balance << endl;
}
void QuickWithDrawMainLogic(vector<StUser>& VectorThatHaveAllClients, int AmountOption)
{
	for (StUser& U : VectorThatHaveAllClients) {

		if (U.account_number == CurrentUser.account_number) {
				U.account_balance -= AmountOption;
				break; 
		}
	}

	UpdateAll(VectorThatHaveAllClients);
}
void ImplementOptionInQuickDraw(EnQuickWithdrawOption noption , vector<StUser>& VectorThatHaveAllClients) {

	switch (noption) {
	case EnQuickWithdrawOption::Twenty:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 20);
		break;

	case EnQuickWithdrawOption::Fifty:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 50);
		break;

	case EnQuickWithdrawOption::OneHundered:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 100);
		break;

	case EnQuickWithdrawOption::TwoHundered:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 200);
		break;

	case EnQuickWithdrawOption::FourHunderd:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 400);
		break;

	case EnQuickWithdrawOption::SixHundered:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 600);
		break;

	case EnQuickWithdrawOption::EigthHundered:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 800);
		break;

	case EnQuickWithdrawOption::OneThousand:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 1000);
		break;

	case EnQuickWithdrawOption::eExit:
		break;

	default:
		QuickWithDrawMainLogic(VectorThatHaveAllClients, 0);
		break;
	}

}
bool IsAmountTrueToStartQuickWithdraw(vector<StUser>& VectorThatHaveAllClients , int Amount) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (U.account_number == CurrentUser.account_number) {

			if (U.account_balance < (Amount)) {
				cout << "\n\aThe amount exceeds your balance!\n\n";
				return false; // the amount is bigger than actual balance 
			}

		}
	}
	return true;
}
//option[1]
void QuickWithdrawScreen(vector<StUser>& VectorThatHaveAllClients) {

	QuickWithDrawMainMenu(); // print menu 

	cout << "\nChoose What To Withdraw From [1] To [9]: ";
	int ChoiceOption = enter_number_from_to(1, 9);
	if (ChoiceOption == 9) return; // exit the operation 
	if (IsAmountTrueToStartQuickWithdraw(VectorThatHaveAllClients, ChoiceOption))
	{
		if (ConfrimOperation("Transaction")) { //Y

			ImplementOptionInQuickDraw((EnQuickWithdrawOption)ChoiceOption, VectorThatHaveAllClients);
			cout << "\n\nDone Successfully , your balance is: " << CurrentUser.account_balance << endl << endl;

	       }
		
	}

}


bool EnterCorrectAmountToWithdraw( int &amount) {

	int AmountToWithDraw = 0;
	AmountToWithDraw = enter_postive_number("\nEnter number multiple of 5's: ");

	if ( AmountToWithDraw > CurrentUser.account_balance)
	{
		screen_color(red);
		cout << "\a\n\n The amount exceeds you balance \n";
		return false; 
	}
	else {
		while (!(AmountToWithDraw % 5 == 0) ||(AmountToWithDraw > CurrentUser.account_balance)) { // multple of 5

			// reinput again 
			screen_color(red_on_black);
			AmountToWithDraw = enter_postive_number("\a\nEnter number multiple of 5's: ");

		}
	}
	screen_color(black);
	amount = AmountToWithDraw;
	return true; 

}
void NormalWithDrawLogic(vector<StUser>& VectorThatHaveAllClients, int amount) {

	for (StUser& U : VectorThatHaveAllClients)
	{
		if (IsAccountNumberExistInVector(U,CurrentUser)) { // if found the client in vector
			U.account_balance -= amount;
			break;

		}
	}

	UpdateAll(VectorThatHaveAllClients); 
}
//option[2]
void ShowNoramlWithDrawScreen(vector<StUser>& VectorThatHaveAllClients ) {

	print_menu_option("Normal Withdraw Screen");

	int amount = 0; 
	if (EnterCorrectAmountToWithdraw(amount)==true) // if the number isn't exceed account balance and it is multiple of 5
	{

		if (ConfrimOperation("withdraw")) {

			NormalWithDrawLogic(VectorThatHaveAllClients, amount);
			cout << "\nDone Successfully , Now Balance is : " << CurrentUser.account_balance << endl;
		}
	}

}


void DepositMainLogic(vector<StUser>& VectorThatHaveAllClients, int amount) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (IsAccountNumberExistInVector(U, CurrentUser) == true) {
			U.account_balance += amount;
			break;
		}
	}

	UpdateAll(VectorThatHaveAllClients);
	//EditFile(VectorThatHaveAllClients, path); // update file
	//VectorThatHaveAllClients= VectorThatHaveAllData(path);//refresh vector 
	//UpdateCurrentUser(CurrentUser, VectorThatHaveAllClients);//update the global var
}
// option [3]
void ShowDepositScreen(vector<StUser>& VectorThatHaveAllClients) {

	print_menu_option("Deposit Screen");

	int AmountToDeposit = enter_postive_number("\nEnter a positive Deposit Amount: ");

	if (ConfrimOperation("Deposit")) 
	{
		DepositMainLogic(VectorThatHaveAllClients, AmountToDeposit);
		cout << "\nDone Successfully. " << "Now balance is: " << CurrentUser.account_balance << endl;
	}
	else {
		cout << "\n\a No Changes On User's Balance!\n\n";
	}
}


// option [4]
void CheckBalance(StUser &CurentUserBalance) {
	cout << "\n\n\t The User \"" << CurentUserBalance.name<<"\" 's account balance is: "<< CurentUserBalance.account_balance << endl;
}

//option [5]
void ShowCurrentUserDetails(StUser &UserDetails) {
	cout << "\n\t"<<"Name: " << UserDetails.name << endl;
	cout << "\t" << "Pin: " << UserDetails.pin << endl;
	cout << "\t" << "AccountNumber: " << UserDetails.account_number << endl;
	cout << "\t"<<"Phone: " << UserDetails.phone << endl;

	cout << "\n\tYou Have Missed Account Balance? check this option: Check Balance.\n\n";
	

}


void DeleteMainLogic(vector<StUser>& VectorThatHaveAllClients) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (IsAccountNumberExistInVector(U, CurrentUser)) {

			U.MarkForDelete = true;
			break;
		}
	}
	UpdateAll(VectorThatHaveAllClients);
}
// Delete Account option[6]
void DeleteAccountScreen(vector<StUser>& VectorThatHaveAllClients , bool &Clogout) {

	print_menu_option("Delete Account Screen");

	if (ConfrimOperation("Deletion For This Account")) 
	{
		DeleteMainLogic(VectorThatHaveAllClients);
		Clogout = true;
	}
}


bool IsNewPassLikesTheOldPass(vector<StUser>& VectorThatHaveAllClients, string & NewPassword) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (IsAccountNumberExistInVector(U, CurrentUser)) {
			if (U.pin == NewPassword) return true;
		}
	}
	return false;
}
void ChangePasswordLogic(vector<StUser>& VectorThatHaveAllClients, string& NewPassword) {

	for (StUser& U : VectorThatHaveAllClients) {

		if (IsAccountNumberExistInVector(U,CurrentUser)) {
			 U.pin= NewPassword;
			break;
		}
	}
	UpdateAll(VectorThatHaveAllClients);
}
// option [7]
void ChangePasswordScreen(vector<StUser>& VectorThatHaveAllClients ) {

	print_menu_option("Change Password");
	string NewPass = read_string("\nEnter New Password: ");

	if (!IsNewPassLikesTheOldPass(VectorThatHaveAllClients, NewPass)) {

		if (ConfrimOperation("Change Password")) {
			ChangePasswordLogic(VectorThatHaveAllClients, NewPass);
			cout << "\nThe operation Of Changing Password Was Done Successfully !\n";
		}
	}
	else {
		cout << "\n\n\a What fuck!\n are you kidding!";
		cout<<"\nthe new ass password is exactly the same of your OLD FUCKIN PASSWORD GETOUT PLEASE\n";
	}


}

// option [8]
void logout() {
	login();
}

void ImplementOptionAccordingToUserChoice(enMainMenuOptions Option ,vector<StUser>& VectorThatHaveAllClients) {

	bool ConfrimLogout = false; // for delete account case
	switch (Option) {
	case enMainMenuOptions::eQuickWithdraw:
		system("cls");
		QuickWithdrawScreen(VectorThatHaveAllClients);
		back_to_menu();
		break;

	case enMainMenuOptions::eNormalWithdraw:
		system("cls");
		ShowNoramlWithDrawScreen(VectorThatHaveAllClients);
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

	case enMainMenuOptions::eUserInfo:
			system("cls");
			ShowCurrentUserDetails(CurrentUser);
			back_to_menu();
			break;

	case enMainMenuOptions::eDeleteAccount:
		    system("cls");  
			DeleteAccountScreen(VectorThatHaveAllClients, ConfrimLogout);
			if (ConfrimLogout ==true) {
			back_to_menu("\n\aYour account Deleted Successfully! ,so why are you still here GET OUT!\n");
			logout();
			}
			else back_to_menu();
			break;

	case enMainMenuOptions::eChangePassword:
		system("cls");
		ChangePasswordScreen(VectorThatHaveAllClients);
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
	cout << setw(5)<< "\tWelcome to Atm System "<< "\033[38;5;177m"<< CurrentUser.name<< "\033[0m" << " !";
	cout << "\n_____________________________________________________\n\n";
	cout << "\033[36m" << setw(5)<< " Please enter the number of the option you want: \n"<< "\033[0m" << endl;
	cout << setw(4) << "\t[1] Quick Withdraw." << endl;
	cout << setw(4) << "\t[2] Normal Withdraw." << endl;
	cout << setw(4) << "\t[3] Deposit." << endl;
	cout << setw(4) << "\t[4] Check Balance." << endl;
	cout << setw(4) << "\t[5] User Info." << endl;
	cout << setw(4) << "\t[6] Delete Account." << endl;
	cout << setw(4) << "\t[7] Change Password." << endl;
	cout << setw(4) << "\t[8] logout." << endl;
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