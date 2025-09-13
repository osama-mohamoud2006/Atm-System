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


const string ClientsFileName = "local db.text";
sClient CurrentClient;

void ShowMainMenue();
void Login();
void ShowQuickWithdrawScreen();
void ShowNormalWithDrawScreen();
void ShowDepositScreen();

vector<string> SplitString(string s, string delmi) {
    vector<string> res;
    short pos = 0;
    string w;
    while ((pos = s.find(delmi)) != string::npos)
    {
        w = s.substr(0, pos);
        if (w != "") res.push_back(w);
        s.erase(0, pos + delmi.length());
    }

    if (s != "") res.push_back(s);
    return res;
}

sClient ConvertLinetoRecord(string line, string delmi = "#//#") {
    vector<string> data = SplitString(line, delmi);

    sClient c;
    c.AccountNumber = data.at(0);
    c.PinCode = data.at(1);
    c.Name = data.at(2);
    c.Phone = data.at(3);
    c.AccountBalance = stoi(data.at(3));

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

    return load;
}

bool FindClientByAccountNumberAndPinCode(string acc, string pin, sClient& client) {
    vector<sClient> load = LoadCleintsDataFromFile("ClientsFileName");

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
    if (Answer == 'y' || Answer == 'Y')

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

    short op = getQuickWithDrawAmount(ReadQuickWithdrawOption());

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

    vector<sClient> load = LoadCleintsDataFromFile("ClientsFileName");
    int am = ReadDepositAmount();
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber,)
}