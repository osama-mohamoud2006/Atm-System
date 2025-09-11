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

