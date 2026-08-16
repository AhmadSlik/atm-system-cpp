#include <iostream> // Project#2 (ATM Systen)
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

enum enUserChoiseTransaction{enQuickWithdraw = 1,  enNormalWithdraw = 2, enDeposit = 3, enCheckBalances = 4};



struct stReadinfo
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    int AccountBalance;
    bool MarkeUpdate = false;
};
stReadinfo CurrentUser; 

string FileName = "ClientRecord.txt";
void StartProgramTransaction(enUserChoiseTransaction UserChoiseTransaction);

void PrintATMMainMenueScreen()
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tATM Main Menue Screen \n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] Quick Withdraw." << endl;
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

void PrintQucikWithdrawBalance()
{
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tQucikWithdraw Screen \n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] 20";
    cout << "\t[2] 50.\n";
    cout << "\t[3] 100";
    cout << "\t[4] 200\n";
    cout << "\t[5] 400";
    cout << "\t[6] 600\n";
    cout << "\t[7] 800.";
    cout << "[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Input AccountNumber? ";
    cin >> AccountNumber;
    cout << "\n";
    return AccountNumber;
}

enUserChoiseTransaction UserChoiseTransaction()
{
    PrintATMMainMenueScreen();
    short UserChoiseTransaction = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 5]? ";
        cin >> UserChoiseTransaction;
    } while (UserChoiseTransaction < 1 || UserChoiseTransaction > 5);
    return (enUserChoiseTransaction)UserChoiseTransaction;
}

void PrintLoginScreen()
{
    cout << "_______________________________________________\n";
    cout << "\t\tLogin Screen\n";
    cout << "_______________________________________________\n";
}

bool ChechAccountNumberAndPinCode(vector<stReadinfo> &vClients, string AccountNumber, string PinCode)
{
        for (stReadinfo info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                if(PinCode == info.PinCode)
                {
                    CurrentUser = info;
                    return true;
                }
            }
        }
    cout << "Invlaid AccountNumber/PinCode!\n";
    return false;
}

vector <string> SplitRecord(string Record, string Seperater)
{
    short Pos= 0;
    string word = "";
    vector <string> Vword;
    while((Pos = Record.find(Seperater)) != string::npos)
    {
        word = Record.substr(0, Pos);
        if(word != "")
        {
        Vword.push_back(word);
        Record.erase(0, Pos + Seperater.length());
        }
    }
    if(Record != "")
    {
        Vword.push_back(Record);
    }
    return Vword;
}

stReadinfo FillStructByRecord(string Record)
{
    stReadinfo info;
    vector <string> vClineData;
    vClineData = SplitRecord(Record, "#//#");
    info.AccountNumber = vClineData[0];
    info.PinCode = vClineData[1];
    info.Name = vClineData[2];
    info.Phone = vClineData[3];
    info.AccountBalance = stoi(vClineData[4]);
    return info;
}

vector<stReadinfo> LoadClientsDataFromFile(string FileName)
{
    vector<stReadinfo> vClients;
    string Record;
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::in);
    
    if(ClientRecordFile.is_open())
    {
        while (getline(ClientRecordFile, Record))
        {
            stReadinfo info = FillStructByRecord(Record);
            vClients.push_back(info);
        }
        ClientRecordFile.close();
    }
    return vClients;
}

void StartProgramLogin()
{
    stReadinfo info;
    string AccountNumber = "";
    string PinCode = "";
    vector<stReadinfo> vClients;
    PrintLoginScreen();
    do
    {
        cout << "Input your AccountNumber? " <<endl;
        getline(cin >> ws, info.AccountNumber);
        AccountNumber  = info.AccountNumber;
        cout << "Input your PinCode? " <<endl;
        getline(cin >> ws, info.PinCode);
        PinCode  = info.PinCode;
        vClients = LoadClientsDataFromFile(FileName);
    } while (!ChechAccountNumberAndPinCode(vClients , AccountNumber, PinCode));
    CurrentUser = info;
    StartProgramTransaction(UserChoiseTransaction());
}

void PrintCheckBalance(stReadinfo info)
{
    cout << "Your Balance is  : " <<  info.AccountBalance << endl;
}


bool CheckBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
        for (stReadinfo &info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                PrintCheckBalance(info);
                return true;
            }
        }
        cout << "Client with Account Number (" << AccountNumber << ") Is Not Found!";
        return false;
}

bool MarkForDeletedOrUpdate(vector<stReadinfo> &vClients, string AccountNumber)
{
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            Clinet.MarkeUpdate = true;
        }
    }
    return false;
}

string ConvertRecordToLine(stReadinfo info, string Seperator = "#//#")
{
    string ClientRecord ="";
    ClientRecord += info.AccountNumber + Seperator;
    ClientRecord += info.PinCode + Seperator;
    ClientRecord += info.Name + Seperator;
    ClientRecord += info.Phone + Seperator;
    ClientRecord += to_string(info.AccountBalance);
    return ClientRecord;
}

stReadinfo DepositBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    short DepositBalance = 0;
    stReadinfo A;
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nHow Deposit Balance you want  : ";
            cin >> DepositBalance;
            Clinet.AccountBalance += DepositBalance;
            return Clinet;
        }
    }
    return A;
}

stReadinfo WithdrawBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    short WithdrawBalance = 0;
    stReadinfo A;
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nInput an amunt multiple of 5's  : ";
            cin >> WithdrawBalance;
            while (WithdrawBalance > Clinet.AccountBalance || WithdrawBalance % 5 != 0)
            {
                cout << "Please Input Another Amount multiple of 5's ? ";
                cin >> WithdrawBalance;
            }
            Clinet.AccountBalance += WithdrawBalance * (-1);
            return Clinet;
        }
    }
    return A;
}

stReadinfo QuichWithdrawBalances(vector<stReadinfo> &vClients, string AccountNumber)
{
    short QucikWithdrawBalance = 0;
    int arr[10] = {0, 20, 50, 100, 200, 400, 600, 800, 1000};
    stReadinfo A;
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nChoose what to withdraw from [1] to [9] ? ";
            cin >> QucikWithdrawBalance;
            
            if(QucikWithdrawBalance == 9) 
            {
                StartProgramTransaction(UserChoiseTransaction());
                return A;
            }
            while (QucikWithdrawBalance < 1 || QucikWithdrawBalance > 9 || arr[QucikWithdrawBalance] > Clinet.AccountBalance)
            {
                cout << "The amount exceeds your balance, make another choice. \n";
                cin >> QucikWithdrawBalance;
            }
            Clinet.AccountBalance -= arr[QucikWithdrawBalance];
            CurrentUser.AccountBalance = Clinet.AccountBalance; 
            return Clinet;
        }
    }
    return A;
}
vector <stReadinfo> SaveCleintsDataToFileFromDeposit(string FileName, vector <stReadinfo> vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = DepositBalance(vClients, AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

vector <stReadinfo> SaveCleintsDataToFileFromWithDrow(string FileName, vector <stReadinfo> vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = WithdrawBalance(vClients, AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

vector <stReadinfo> SaveCleintsDataToFileFromQuickWithDrow(string FileName, vector <stReadinfo> vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = QuichWithdrawBalances(vClients, AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void UpdetInfoClineForDepositBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(CheckBalance(vClients, AccountNumber))
    {
        cout << "\nAre you sure you want to Deposit Balance for this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromDeposit("ClientRecord.txt", vClients, AccountNumber);
        vClients = LoadClientsDataFromFile("ClientRecord.txt");
        cout << "\nClinet Updated successflly. \n";
        }
    }
    else
    {
        UpdetInfoClineForDepositBalance(vClients, ReadAccountNumber());
    }
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nNew Balance after Deposit is " << Clinet.AccountBalance << endl;
        }
    }
    return; 
}

void WithDrowBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(CheckBalance(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to WithDrow Balance for this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromWithDrow("ClientRecord.txt", vClients, AccountNumber);
        vClients = LoadClientsDataFromFile("ClientRecord.txt");
        cout << "\nClinet Updated successflly. \n";
        }

        else
        {
            return;
        }
    }
    else
    {
        WithDrowBalance(vClients, ReadAccountNumber());
    }
      for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nNew Balance after WithDrow is " << Clinet.AccountBalance << endl;
        }
    }
    return; 
}

void QuickWithDrowBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
        char Answer;
    if(CheckBalance(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to WithDrow Balance for this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromQuickWithDrow("ClientRecord.txt", vClients, AccountNumber);
        vClients = LoadClientsDataFromFile("ClientRecord.txt");
        cout << "\nClinet Updated successflly. \n";
        }

        else
        {
            return;
        }
    }
    else
    {
        QuickWithDrowBalance(vClients, ReadAccountNumber());
    }
      for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nNew Balance after WithDrow is " << Clinet.AccountBalance << endl;
        }
    }
}

void StartDepositBalance()
{
    cout << "____________________________________________________\n";
    cout << "\t\tDeposit Balance Screen\n";
    cout << "____________________________________________________\n\n";
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    UpdetInfoClineForDepositBalance(vClients, CurrentUser.AccountNumber);
}

void StartNormalWithDrowitBalance()
{
    cout << "____________________________________________________\n";
    cout << "\t\tNormal WithDrowit Balance Screen\n";
    cout << "____________________________________________________\n\n";
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    WithDrowBalance(vClients, CurrentUser.AccountNumber);
}

void StartQuickWithDrowitBalance()
{
    PrintQucikWithdrawBalance();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    QuickWithDrowBalance(vClients, CurrentUser.AccountNumber);
}

void StartCheckBalance()
{
    PrintCheckBalance(CurrentUser);
}

void BackToTransactionMenue()
{
    cout << "\nPress Enter to go back to Transaction Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    StartProgramTransaction(UserChoiseTransaction());
}

void StartProgramTransaction(enUserChoiseTransaction UserChoiseTransaction)
{
    system("clear");
    switch (UserChoiseTransaction)
{

case enQuickWithdraw:
    StartQuickWithDrowitBalance();
    BackToTransactionMenue();
    break;

case enNormalWithdraw:
    StartNormalWithDrowitBalance();
    BackToTransactionMenue();
    break;

case enDeposit:
    StartDepositBalance();
    BackToTransactionMenue();
    break;

case enCheckBalances:
    StartCheckBalance();
    BackToTransactionMenue();
    break;

default:
    StartProgramLogin();
    break;
}
}


int main()
{
    StartProgramLogin();
}
