#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};


enum enMainMenueOptions {
    eQucikWithdraw = 1, eNormalWithDraw = 2, eDeposit = 3, eCheckBalance = 4, eExit = 5};


const string ClientsFileName = "Clients.txt";
sClient CurrentClient;

void ShowMainMenue();
void Login();
void ShowQuickWithdrawScreen();
void ShowNormalWithDrawScreen();
void ShowDepositScreen();