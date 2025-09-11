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

struct StUser { int account_balance = 0; int pin = 0; int account_number = 0; };

struct StUser CurrentUser;

enum enMainMenuOptions{QuicWithdraw=1 , NormalWithdraw=2 ,Dposit=3 , CheckBalance=4 ,Logout=5};

 
