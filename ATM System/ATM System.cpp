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
enum enMainMenuOptions{QuicWithdraw=1 , NormalWithdraw=2 ,Dposit=3 , CheckBalance=4 ,Logout=5};
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

// read file content and push in



void main_menu() {
	system("cls");
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

void login() {

}