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

// things to use in menu option 
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