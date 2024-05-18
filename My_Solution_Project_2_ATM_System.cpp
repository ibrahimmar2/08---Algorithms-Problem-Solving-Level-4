#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>



using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowTransactionsMenue();
void LoginScreen();



struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

sClient CurrentClient;

enum enOpQucikDraw
{
    e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5,
    e600 = 6, e800 = 7, e1000 = 8 , eExit = 9

};


enum enTransactionsMenueOptions
{
    eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eShowTotalBalance = 4, eShowMainMenue = 5
};


vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}


vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}




string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}



int ReadDepositAmount()
{
    double Amount;
    cout << "\nEnter a Positive Deposit Amount ?";

    cin >> Amount;

    while (Amount <= 0)
    {
        cout << "\nEnter a Positive Deposit Amount ?";

        cin >> Amount;
    }

    return Amount;
}

void PerfromDepositScreen()
{
    int Amount = ReadDepositAmount();


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount , vClients);
    CurrentClient.AccountBalance += Amount;
}



void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\t\tDeposit Screen\n";
    cout << "\n-----------------------------------\n";


    cout << "\nyour is Balances: " << CurrentClient.AccountBalance << endl;


    PerfromDepositScreen();

}

int ReadWithDrawAmount()
{
    int Amount;
    cout << "\nEnter an amount multipl of 5's ?";

    cin >> Amount;

    while (Amount % 5 != 0)
    {
        cout << "\nEnter an amount multipl of 5's ?";

        cin >> Amount;
    }

    return Amount;
}



void PerfromWithDrawScreen()
{
    int Amount = ReadWithDrawAmount();




    //Validate that the amount does not exceeds the balance
    while (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice. \n";
        cout << "Press AnyKey to continue...... ";
        system("pause>0");
    }
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount * -1, vClients);
    CurrentClient.AccountBalance -= Amount;
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n-----------------------------------\n";

    cout << "\nyour is Balances: " << CurrentClient.AccountBalance << endl;


    PerfromWithDrawScreen();
}


void QucikDrawScreen(double Amount)
{


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount * -1, vClients);
    CurrentClient.AccountBalance -= Amount;

}

short ReadQucikDraw()
{
    cout << "Choose what Withdraw from[1] to [8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}


void PerfromQucikDraw(enOpQucikDraw OpQucikDraw)
{
    {
        switch (OpQucikDraw)
        {
        case enOpQucikDraw::e20:
        {
            QucikDrawScreen(20);
            GoBackToTransactionsMenue();
            break;
        }

        case enOpQucikDraw::e50:
        {
            QucikDrawScreen(50);
            GoBackToTransactionsMenue();
            break;
        }


        case enOpQucikDraw::e100:
        {
            QucikDrawScreen(100);
            GoBackToTransactionsMenue();
            break;
        }
        case enOpQucikDraw::e200:
        {
            QucikDrawScreen(200);
            GoBackToTransactionsMenue();
            break;

        }
        case enOpQucikDraw::e400:
        {
            QucikDrawScreen(400);
            GoBackToTransactionsMenue();
            break;

        }
        case enOpQucikDraw::e600:
        {
            QucikDrawScreen(600);
            GoBackToTransactionsMenue();
            break;

        }
        case enOpQucikDraw::e800:
        {
            GoBackToTransactionsMenue();
            QucikDrawScreen(800);
            break;

        }
        case enOpQucikDraw::e1000:
        {
            QucikDrawScreen(1000);
            GoBackToTransactionsMenue();
            break;

        }        
        case enOpQucikDraw::eExit:
        {

            GoBackToTransactionsMenue();
            break;

        }
        }

    }
}


void ShowWithَQucikDrawScreen()
{    
    cout << "\n===================================\n";
    cout << "\t\tQucik Withdraw ";
    cout << "\n===================================\n";
    cout << "\t[1] 20\t\t [2] 50\n";
    cout << "\t[3] 100\t\t [4] 200\n";
    cout << "\t[5] 400\t\t [6] 600\n";
    cout << "\t[7] 800\t\t [8] 1000\n";
    cout << "\t[9] Exit";
    cout << "\n===================================\n";
    
    cout << "your is Balances: " << CurrentClient.AccountBalance << endl;
     

    PerfromQucikDraw((enOpQucikDraw)ReadQucikDraw());
}




void ShowCheckToBalancesScreen()
{

    cout << "\n===================================\n";
    cout << "\tCheck balance Screen ";
    cout << "\n===================================\n";
    cout << "your Balances is : " << CurrentClient.AccountBalance << endl;

}



short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{

    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eQuickWithdraw:
    {
        system("cls");
        ShowWithَQucikDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eNormalWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowCheckToBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {
        system("cls");
        LoginScreen();
        break;

    }

    }

}


void ShowTransactionsMenue()
{
    

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balances.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

bool FindByAccountNumber(string AccountNumber, string PinCode, sClient& Client)
{
    vector <sClient> vClients;

    vClients = LoadCleintsDataFromFile(ClientsFileName);


    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }


    }
    return false;

}


bool  LoadUserInfo(string AccountNumber, string PinCode)
{

    if (FindByAccountNumber(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;

}

void LoginScreen()
{

    bool LoginFaild = false;


    string AccountNumber;
    string PinCode;
    do
    {
        system("cls");

        cout << "\n*******************************************\n";
        cout << "\t\tLogin Screen\n";
        cout << "*******************************************\n";

        if (LoginFaild)
        {
            cout << "\nInvlaid Username/Password!\n";
        }

        cout << "Enter Username? ";
        cin >> AccountNumber;
        cout << "Enter Password? ";
        cin >> PinCode;

        LoginFaild = !LoadUserInfo(AccountNumber, PinCode);

    } while (LoginFaild);

    ShowTransactionsMenue();
}



int main()
{
    LoginScreen();
        
}

