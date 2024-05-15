#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UserFileName = "Users.txt";


void ShowMainMenue();
void ShowTransactionsMenue();
void ShowMangeUsersMenue();
void  LoginScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};
struct sUser
{
    string Username;
    string Userpassword;
    int Permissions;
    bool MarkForDelete = false;
};

enum enMangeUsersOptions 
{
    eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
    eUpdateUser = 4, eFindUser = 5, MainMenue = 6
};
enum enMainMenuePermissions 
{
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
    pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
};

sUser CurrentUser;

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

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
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
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

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
bool CheackAccessPermission(enMainMenuePermissions Permission)
{
    if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
        return true;

    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;
    else
        return false;
}


void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAccessDeniedmessage()
{
    cout << "\n-----------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n-----------------------------------\n";
}
void ShowAllClientsScreen()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pListClients))
    {
        ShowAccessDeniedmessage();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

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

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

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

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

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

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedmessage();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}
void ShowUpdateClientScreen()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        ShowAccessDeniedmessage();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowAddNewClientsScreen()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        ShowAccessDeniedmessage();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedmessage();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions
{
    eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 
};
enum enMainMenueOptions 
{
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eShowTransactionsMenue = 6, MangeUsers = 7, Logout = 8
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }

    }

}
void ShowTransactionsMenue()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedmessage();
        GoBackToMainMenue();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}


void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;

    case enMainMenueOptions::MangeUsers:
        system("cls");
        ShowMangeUsersMenue();
        break;
    
    case enMainMenueOptions::Logout:
        system("cls");
        //ShowEndScreen();
        LoginScreen();
        break;
    }

}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Mange Users.\n";
    cout << "\t[8] Login.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give  access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }


    cout << "\nTransactions? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }


    cout << "\nManage Users? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }

    return Permissions;
}
short ReadMangeUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
void GoBackToMangeUsersMenue()
{
    cout << "\n\nPress any key to go back to MangeUsersMenue...";
    system("pause>0");
    ShowMangeUsersMenue();

}

sUser ConvertLinetoUser(string Line, string Seperator = "#//#")
{

    sUser User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Seperator);

    User.Username = vUserData[0];
    User.Userpassword = vUserData[1];
    User.Permissions = stoi(vUserData[2]);

    return User;

}
string ConvertUserToLine(sUser User, string Seperator = "#//#")
{

    string stUserRecord = "";

    stUserRecord += User.Username + Seperator;
    stUserRecord += User.Userpassword + Seperator;

    stUserRecord += to_string(User.Permissions);

    return stUserRecord;

}
vector <sUser> LoadUsersDataFromFile(string FileName)
{

    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(UserFileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoUser(Line);

            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return vUsers;

}

void PrintUserLine(sUser User)
{

    cout << "| " << setw(15) << left << User.Username;
    cout << "| " << setw(10) << left << User.Userpassword;
    cout << "| " << setw(40) << left << User.Permissions;
}
void ShowAllUsersScreen()
{


    vector <sUser> vUsers = LoadUsersDataFromFile(UserFileName);

    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "PassWord";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else

        for (sUser User : vUsers)
        {

            PrintUserLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
bool UserExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoUser(Line);
            if (User.Username == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return false;


}

sUser ReadNewUser()
{
    sUser User;

    cout << "Enter Username? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.Username);

    while (UserExistsByAccountNumber(User.Username, UserFileName))
    {
        cout << "\nUser with [" << User.Username << "] already exists, Enter another User? ";
        getline(cin >> ws, User.Username);
    }


    cout << "Enter Password? ";
    getline(cin, User.Userpassword);

    User.Permissions = ReadPermissionsToSet();

    return User;

}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UserFileName, ConvertUserToLine(User));

}
void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();

}

bool FindUserByUsername(string Username, vector <sUser> vUsers, sUser& User)
{

    for (sUser C : vUsers)
    {

        if (C.Username == Username)
        {
            User = C;
            return true;
        }

    }
    return false;

}
bool MarkClientForDeleteByUsername(string Username, vector <sUser>& vUsers)
{

    for (sUser& C : vUsers)
    {

        if (C.Username == Username)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sUser> SaveUsersDataToFile(string FileName, vector <sUser> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sUser C : vUsers)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertUserToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vUsers;

}

bool DeleteUserByUsername(string Username, vector <sUser>& vUsers)
{

    if (Username == "Admin")
    {
        cout << "\n\nYou cannot Delete This User.";
        return false;

    }

    sUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserLine(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(UserFileName, vUsers);

            //Refresh Clients 
            vUsers = LoadUsersDataFromFile(UserFileName);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }

}

string ReadUsername()
{
    string Username = "";

    cout << "\nEnter Username? ";
    cin >> Username;
    return Username;

}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UserFileName);
    string Username = ReadUsername();
    DeleteUserByUsername(Username, vUsers);

}

sUser ChangeUserRecord(string Username)
{
    sUser User;

    User.Username = Username;

    cout << "\n\nEnter Username? ";
    getline(cin >> ws, User.Username);

    cout << "Enter Password? ";
    getline(cin, User.Userpassword);



   // cout << "Enter AccountBalance? ";
   // cin >> Client.AccountBalance;

    return User;

}

bool UpdateUserByUsername(string Username, vector <sUser>& vUsers)
{

    sUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserLine(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sUser& C : vUsers)
            {
                if (C.Username == Username)
                {
                    C = ChangeUserRecord(Username);
                    break;
                }

            }

            SaveUsersDataToFile(UserFileName, vUsers);

            cout << "\n\nUser Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nUsers with Username (" << Username << ") is Not Found!";
        return false;
    }

}
void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UserFileName);
    string Username = ReadUsername();
    UpdateUserByUsername(Username, vUsers);

}
void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UserFileName);
    sUser User;
    string Username = ReadUsername();
    if (FindUserByUsername(Username, vUsers, User))
        PrintUserLine(User);
    else
        cout << "\nClient with Username[" << Username << "] is not found!";

}

void PerfromMangeUsersOption(enMangeUsersOptions MangeUsersOption)
{
    switch (MangeUsersOption)
    {
    case enMangeUsersOptions::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackToMangeUsersMenue();
        break;
    }
    case enMangeUsersOptions::eAddNewUser:
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToMangeUsersMenue();
        break;

    case enMangeUsersOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToMangeUsersMenue();
        break;

    case enMangeUsersOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToMangeUsersMenue();
        break;

    case enMangeUsersOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToMangeUsersMenue();
        break;

    case enMangeUsersOptions::MainMenue:
        system("cls");
        ShowMainMenue();
        break;
    }

}
void ShowMangeUsersMenue()
{
    if (!CheackAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        ShowAccessDeniedmessage();
        GoBackToMainMenue();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\t\Mange Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] MainMenue.\n";
    cout << "===========================================\n";
    PerfromMangeUsersOption((enMangeUsersOptions)ReadMangeUsersMenueOption());
}
bool FindByUsernameAndPassword(string Username,string Password, sUser& User)
{
    vector <sUser> vUsers;

    vUsers = LoadUsersDataFromFile(UserFileName);


    for (sUser U : vUsers)
    {

        if (U.Username == Username && U.Userpassword == Password)
        {
            User = U;
            return true;
        }


    }
    return false;

}

bool  LoadUserInfo(string Username, string Password)
{

    if (FindByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;

}

void LoginScreen()
{

    bool LoginFaild = false;


    string userName;
    string Password;
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
        cin >> userName;
        cout << "Enter Password? ";
        cin >> Password;

        LoginFaild = !LoadUserInfo(userName, Password);
    
    }while (LoginFaild);
 
    ShowMainMenue();
}

int main()

{
    LoginScreen();
    system("pause>0");
    return 0;
}