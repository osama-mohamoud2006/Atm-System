#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"E:\projects\my library\AllStuff.h"  
#include <iomanip>

using namespace std;
using namespace AllStuff;
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


const string ClientsFileName = "local db.text";
sClient CurrentClient;

void ShowMainMenue();
void Login();
void ShowQuickWithdrawScreen();
void ShowNormalWithDrawScreen();
void ShowDepositScreen();

sClient ConvertLinetoRecord(string line, string delmi = "#//#") {
    vector<string> data = SplitString(line, delmi);

    sClient c;
    c.AccountNumber = data.at(0);
    c.PinCode = data.at(1);
    c.Name = data.at(2);
    c.Phone = data.at(3);
    c.AccountBalance = stod(data.at(4));

    return c; 
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

// vector of clients From file 
vector<sClient>LoadCleintsDataFromFile(string FileName) {

    vector< sClient> load; 

    fstream read;
    read.open(FileName,ios::in);// read

    if (read.is_open()) 
    {
        string line;
        sClient c;
        while (getline(read, line)) {
            c = ConvertLinetoRecord(line);
            load.push_back(c);
        }

        read.close();
    }
    else {
        cout << "\a\n couldn't open file!\n";
    }

    return load;
}

bool FindClientByAccountNumberAndPinCode(string acc, string pin, sClient& client) {
    vector<sClient> load = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient& c : load) {
        if (c.AccountNumber == acc && c.PinCode == pin) {
            client = c;
            return true;
        }
    }
    return false; 
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector <sClient> &vClients) {

    fstream write;
    write.open(FileName, ios::out); // overwrite 

   if( write.is_open()) {

       for(sClient &c: vClients){

           if (c.MarkForDelete == false) 
           {
           string line = ConvertRecordToLine(c);
           write << line << endl;

           }
         
       }
       write.close();
    }

   return vClients;
}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, double amount, vector <sClient>& vClients) {
   
 char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
   
        if (Answer == 'Y' || Answer == 'y') {

            for (sClient& c : vClients) {

                if (c.AccountNumber == AccountNumber) {
                    c.AccountBalance += amount;
                    SaveCleintsDataToFile(ClientsFileName, vClients);
                    cout << "\n\nDone Successfully. New balance is: " << c.AccountBalance;

                    return true;
                }
            }
            return false;
        }
    return false;
}


short ReadQuickWithdrawOption()
{
    short Choice = 0;
    while (Choice < 1 || Choice>9)
    {
        cout << "\nChoose what to do from [1] to [9] ? ";
        cin >> Choice;
    }

    return Choice;
}

short getQuickWithDrawAmount(short QuickWithdrawOption) {

    switch (QuickWithdrawOption) {

    case 1:
        return 20;

    case 2:
        return 50;

    case 3:
        return 100;

    case 4:
        return 200;

    case 5:
        return 400;

    case 6:
        return 600;

    case 7:
        return 800;

    case 8:
        return 1000;

    default:
        return 0; 
    }
}

void PerfromQuickWithdrawOption(short QuickWithdrawOption) {

    if (QuickWithdrawOption == 9) return; 

    short op = getQuickWithDrawAmount(QuickWithdrawOption);


    if (op > CurrentClient.AccountBalance) {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, op*-1, vClients);
    CurrentClient.AccountBalance -= op;
}

double ReadDepositAmount()
{
    double Amount;
    cout << "\nEnter a positive Deposit Amount? ";

    cin >> Amount;
    while (Amount <= 0)
    {
        cout << "\nEnter a positive Deposit Amount? ";
        cin >> Amount;
    }
    return Amount;
}

void PerfromDepositOption() {

    vector<sClient> load = LoadCleintsDataFromFile(ClientsFileName);
    double am = ReadDepositAmount();
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, am, load);
    CurrentClient.AccountBalance += am;
}

void ShowDepositScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit Screen\n";
    cout << "===========================================\n";

    PerfromDepositOption();
}

void ShowCheckBalanceScreen() {

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "===========================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << "\n";
}

int ReadWithDrawAmont()
{
    int Amount;
    cout << "\nEnter an amount multiple of 5's ? ";

    cin >> Amount;

    while (Amount % 5 != 0)
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Amount;
    }
    return Amount;
}

void PerfromNormalWithdrawOption() {
    int w = ReadWithDrawAmont();

    if (w > CurrentClient.AccountBalance) {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowNormalWithDrawScreen();
        return;
    }

    vector<sClient> load = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, w*-1, load);
    CurrentClient.AccountBalance -= w;
}

void ShowNormalWithDrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";
    PerfromNormalWithdrawOption();
}

void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQucik Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance;

    PerfromQuickWithdrawOption(ReadQuickWithdrawOption());
}

void GoBackToMainMenue()
{
    cout << colorText(" \n\nPress any key to go back to Main Menue...", "purple") << endl;
    system("pause>0");
    ShowMainMenue();
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}


void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eQucikWithdraw:
    {
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eNormalWithDraw:
        system("cls");
        ShowNormalWithDrawScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eExit:
        system("cls");
        Login();

        break;
    }

}

void ShowMainMenue()
{
    system("cls");    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";


    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool LoadClientInfo(string AccountNumber, string PinCode) {

    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient)) {
        return true;
    }
    else return false;
}

void Login() {

    bool Failed = false; 
    string AccountNumber, PinCode;

    do {
        system("cls");
        print_menu_option(colorText("login","red",true));

        if (Failed) {
            cout << "\n invaild pass or acc num\n";
        }

        cout << "Enter Account Number? ";
        cin >> AccountNumber;

        cout << "Enter Pin? ";
        cin >> PinCode;

       Failed = !LoadClientInfo(AccountNumber, PinCode);

    } while (Failed);

    ShowMainMenue();
}

int main() {
  
    Login();
}