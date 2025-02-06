#include<vector>
#include <iostream>
#include<iomanip>
#include<string>
#include<fstream>


using namespace std;

const string filename = "Clients.txt";

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool markfordelete = false;
};

enum enoperationtype{listclient=1,addclient=2,deletclient=3,updateclient=4,findclient=5,transaction=6, exist = 7
};

enum enTransaction{Deposite=1,Withdraw=2,TotalBalances=3,MainMenue=4};

vector<string>SplitString(string s, string delim = "#//#")
{
    short pos = 0;
    string sword;
    vector<string>vstring;

    while ((pos = s.find(delim)) != std::string::npos)
    {
        sword = s.substr(0, pos);
        if (sword != " ")
        {
            vstring.push_back(sword);
        }
        s.erase(0, pos + delim.length());
    }

    if (s != "")
    {
        vstring.push_back(s);
    }

    return vstring;
}

stClient ConvertLineToRecord(vector<string> vstring,string Line)
{
    vstring = SplitString(Line);
    stClient Client;
    Client.AccountNumber = vstring[0];
    Client.PinCode = vstring[1];
    Client.Name = vstring[2];
    Client.Phone = vstring[3];
    Client.AccountBalance = stod(vstring[4]);

    return Client;
}

vector<stClient>LoadDataFromFileToVector()
{
    vector<stClient>vClient;
    
    fstream myfile;
    myfile.open(filename, ios::in);
    if (myfile.is_open())
    {
        string line;
        stClient c;
        vector<string>v;
        while (getline(myfile, line))
        {
            v = SplitString(line);
            c = ConvertLineToRecord(v, line);
            vClient.push_back(c);
        }
    }
    myfile.close();
    return vClient;
}

bool FindClientByAccountNumber(string Accountnumber, vector<stClient> vClients, stClient& client)
{
    for (stClient& c : vClients)
    {
        if (c.AccountNumber == Accountnumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}

void PrintClient(stClient client)
{
    cout << "\n--------------------------------------------\n";
    cout << "AccountNumber    :" << client.AccountNumber << endl;
    cout << "PinCode          :" << client.PinCode << endl;
    cout << "Name             :" << client.Name << endl;
    cout << "Phone            :" << client.Phone << endl;
    cout << "AccountBalance   :" << client.AccountBalance << endl;
    cout << "--------------------------------------------\n";
}

void showClient(stClient c)
{
    cout << "|" << left << setw(14) << c.AccountNumber ;
    cout << "|" << left << setw(16) << c.PinCode ;
    cout << "|" << left << setw(9) << c.Name ;
    cout << "|" << left << setw(12) << c.Phone ;
    cout << "|" << left << setw(12) << c.AccountBalance ;
}

void ShowClientList()
{
    vector<stClient>Client = LoadDataFromFileToVector();
        cout << "\n Client List[" << Client.size() << "] Client(s)\n";

        cout << "===================================================================================\n";
        cout << "|" << "AccountNumber" << " |" << "PinCode " << "        |" << "Name " <<     
            "    |" << "Phone" << "       |" << "AccountBalance\n";
        cout << "===================================================================================\n";
        for (stClient c : Client)
        {
            showClient(c);
            cout << "\n";
        }
        cout << "===================================================================================\n";
}

stClient ReadClientInfo()
{
    stClient Client;

    cout << "Enter Client Info To Add in File...\n";

    cout << "Enter AccountNumber..?\n";
    getline(cin >> ws, Client.AccountNumber);

    cout << "Enter PinCode..?\n";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name..?\n";
    getline(cin >> ws, Client.Name);

    cout << "Enter Phone..?\n";
    getline(cin >> ws, Client.Phone);

    cout << "Enter AccountBalance..?\n";
    cin >> Client.AccountBalance;

    return Client;

}

string ConvertRecordToLine(stClient Client,string seperator="#//#")
{
    string Line="";
    Line += Client.AccountNumber + seperator;
    Line += Client.PinCode + seperator;
    Line += Client.Name + seperator;
    Line += Client.Phone + seperator;
    Line += to_string(Client.AccountBalance);

    return Line;
}

bool AddNewClientToFile(string Line,string filename)
{
    fstream myfile;

    myfile.open(filename, ios::app | ios::out);
    if (myfile.is_open())
    {
        
        myfile << Line<<endl;
        myfile.close();
        return true;
    }
    return false;
}

string readaccountnumber()
{
    string number;

    cout << "Please enter account number to search ?...\n";
    cin >> number;

    return number;
}

bool _MarkForDelete(vector < stClient> &vClients, string Accountnumber)
{
    for (stClient& c : vClients)
    {
        if (c.AccountNumber == Accountnumber)
        {
            c.markfordelete = true;
            return true;
        }
        c.markfordelete = false;
    }
    return false;
}

bool AddClientsToFile(vector < stClient>& vClients, string accountnumber)
{
    fstream myfile;

    myfile.open(filename,  ios::out);
    if (myfile.is_open())
    {
        for (stClient c : vClients)
        {
            if (c.markfordelete == false)
            {
                string Line = ConvertRecordToLine(c);
                myfile << Line << endl;
            }
        }
        myfile.close();
        return true;
    }
    myfile.close();
    return false;
}

bool AddClientsToFile(vector < stClient>& vClients)
{
    fstream myfile;

    myfile.open(filename, ios::out);
    if (myfile.is_open())
    {
        for (stClient c : vClients)
        {
                string Line = ConvertRecordToLine(c);
                myfile << Line << endl; 
        }
        myfile.close();
        return true;
    }
    myfile.close();
    return false;
}

bool PrintClintifExist()
{
    string Accountnumber = readaccountnumber();
    vector<stClient> vClients = LoadDataFromFileToVector();
    stClient client;
    if (FindClientByAccountNumber(Accountnumber, vClients, client))
    {
        PrintClient(client);
        return true;
    }
    else
    {
        return false;
    }
}

bool DeleteClient()
{
    vector < stClient>vClients = LoadDataFromFileToVector();
    string accountnumber = readaccountnumber();
    stClient client;
    char sure;
    if (FindClientByAccountNumber(accountnumber, vClients, client))
    {
        cout << "this is your account...\n";
        PrintClient(client);
        cout << "Are you sure you want delete this account[y,n]\n";
        cin >> sure;
        if (sure == 'y' || sure == 'Y')
        {
            _MarkForDelete(vClients, accountnumber);
            AddClientsToFile(vClients, accountnumber);
        }
        return true;
    }
    else
    {
        cout << "not found your account number...\n";
        return false;
    }
}

stClient updatedate(stClient& client)
{
    stClient c;
    c.AccountNumber = client.AccountNumber;
    cout << "Enter PinCode...\n";
    getline(cin >> ws, c.PinCode);

    cout << "Enter name..\n";
    getline(cin, c.Name);

    cout << "Enter Phone..\n";
    getline(cin, c.Phone);

    cout << "Enter AccountBalance...\n";
    cin >> c.AccountBalance;

    return c;
}

bool UpdateClient()
{
    vector < stClient>vClients = LoadDataFromFileToVector();
    string accountnumber = readaccountnumber();
    stClient client;
    char sure;
    if (FindClientByAccountNumber(accountnumber, vClients, client))
    {
        cout << "this is your account...\n";
        PrintClient(client);
        cout << "Are you sure you want Update this account[y,n]\n";
        cin >> sure;
        if (sure == 'y' || sure == 'Y')
        {
            for (stClient &c : vClients)
            {
                if (c.AccountNumber == accountnumber)
                {
                    c = updatedate(c);
                }
            }
            AddClientsToFile(vClients, accountnumber);
            return true;
        }
        return true;
    }
    else
    {
        cout << "not found your account number...\n";
        return false;
    }
}

int readnumber(string massege)
{
    int number;

    cout <<massege ;
    cin >> number;

    return number;
}

void ShowClientsList()
{
    ShowClientList();
}

void ShowAddClient()
{
    cout << "\n------------------------------------\n";
    cout << "         Add New Client               \n";
    cout << "\n------------------------------------\n";
    AddNewClientToFile(ConvertRecordToLine(ReadClientInfo()), filename);
    cout << "\n------------------------------------\n";
}

void ShowDeleteClient()
{
    cout << "\n------------------------------------\n";
    cout << "         Delete Client               \n";
    cout << "\n------------------------------------\n";

    DeleteClient();

    cout << "\n------------------------------------\n";
}

void ShowUpdateClient()
{
    cout << "\n------------------------------------\n";
    cout << "         Update Client               \n";
    cout << "\n------------------------------------\n";

    UpdateClient();

    cout << "\n------------------------------------\n";

}

void ShowFindClient()
{
    cout << "\n------------------------------------\n";
    cout << "         Find Client               \n";
    cout << "\n------------------------------------\n";

    PrintClintifExist();

    cout << "\n------------------------------------\n";
}

void ShowExistMenue()
{
    cout << "\n------------------------------------\n";
    cout << "         Exist Menue               \n\n";
    cout << "\n------------------------------------\n";
    cout << "\n------------------------------------\n";
}

void TransactionMenueScreen();

void AddToAccountBalance(vector < stClient> &vClients,string accountnumber,int deposite)
{
    for (stClient& c : vClients)
    {
        if (c.AccountNumber == accountnumber)
        {
            c.AccountBalance += deposite;
        }
    }
}

bool ChangeAccountBalance(vector < stClient>& vClients, string accountnumber, int amount)
{
        AddToAccountBalance(vClients, accountnumber, amount);

        AddClientsToFile(vClients);
        cout << "Add Done successfully\n";
        return true;

    return true;
}

void _Deposite()
{
    string accountnumber;
    stClient client;
    int amount;
    vector < stClient> vClients= LoadDataFromFileToVector();

    cout << "Please Enter your accountnumber\n";
    cin >> accountnumber;

    if (FindClientByAccountNumber(accountnumber, vClients, client))
    {
        PrintClient(client);
        cout << "Plesae enter deposite amount ?\n";
        cin >> amount;

        bool sure;
        cout << "Are you sure you want to deposite this deposite[y=1,n=0] ?\n";
        cin >> sure;
        if (sure)
        {
            ChangeAccountBalance(vClients, accountnumber, amount);
        }
    }
    else
    {
        cout << "wrong accountnumber,please try again\n";
    }
}

void WithDraw()
{
    string accountnumber;
    stClient client;
    int amount;

    vector < stClient> vClients = LoadDataFromFileToVector();

    cout << "Please Enter your accountnumber\n";
    cin >> accountnumber;

    if (FindClientByAccountNumber(accountnumber, vClients, client))
    {
        PrintClient(client);
        do
        {
            cout << "Plesae enter Withdraw amount ?\n";
            cin >> amount;
            if (amount <= client.AccountBalance)
            {
                bool sure;
                cout << "Are you sure you want to withdraw this deposite[y=1,n=0] ?\n";
                cin >> sure;
                if (sure)
                {
                    ChangeAccountBalance(vClients, accountnumber, -amount);
                }
            }
            else
            {
                cout << "Not enough you can not withdraw more than " << client.AccountBalance << endl;
            }
        } while (amount > client.AccountBalance);
    }
    else
    {
        cout << "wrong accountnumber,to go main transaction \n";
    }
}

void ShowWithdrawScreen()
{
    cout << "\n-------------------------------------------\n";
    cout << "       Withdraw Screen           \n";
    cout << "\n-------------------------------------------\n";
    WithDraw();
}

void ShowDepositeScreen()
{
    cout << "\n-------------------------------------------\n";
    cout << "         Deposite Screen               \n";
    cout << "\n-------------------------------------------\n";
    _Deposite();
}

void ShowBalanceList(stClient client)
{
    cout << "|" << left << setw(15) << client.AccountNumber ;
    cout << "|" << left << setw(30) << client.Name ;
    cout << "|" << left << setw(15) << client.AccountBalance << "\n";
}

void ShowTotalBalancesMenue(vector<stClient>& Clients)
{
    double total_balances = 0;
    for (stClient& c : Clients)
    {
        ShowBalanceList(c);
        total_balances += c.AccountBalance;
    }
    cout << "===================================================================================\n";
    cout << "\t\t\t Total Balances = " << total_balances << "\n\n";
}

void ShowTotalBalances()
{
    vector<stClient>Clients = LoadDataFromFileToVector();
    cout << "\n Client List[" << Clients.size() << "] Client(s)\n";

    cout << "===================================================================================\n";
    cout << "|" << setw(15) << "AccountNumber" << "|" << setw(30) << "Client Name " << "|" << setw(15) << "AccountBalance\n";
    cout << "===================================================================================\n";

    ShowTotalBalancesMenue(Clients);

}

void ShowMainMenue();

void GoToMainMenue()
{
    cout << "Press any key to go main menue.....";
    system("pause>0");
    system("cls");
    ShowMainMenue();
}

void GoToTransactionMenue()
{
    cout << "Press any key to go main menue.....";
    system("pause>0");
    system("cls");
    TransactionMenueScreen();
}

void chooseFromTransactionMenue(enTransaction TransactionType)
{
    switch (TransactionType)
    {
    case enTransaction::Deposite:
        system("cls");
        ShowDepositeScreen();
        GoToTransactionMenue();
        break;
    case enTransaction::Withdraw:
        system("cls");
        ShowWithdrawScreen();
        GoToTransactionMenue();
        break;
    case enTransaction::TotalBalances:
        system("cls");
        ShowTotalBalances();
        GoToTransactionMenue();
        break;
    case enTransaction::MainMenue:
        system("cls");
        ShowMainMenue(); 
        break;
    default:
        break;
    }
}

void chooseFromMainMenue(enoperationtype optype)
{
    switch (optype)
    {
    case enoperationtype::listclient:
        system("cls");
        ShowClientsList();
        GoToMainMenue();
        break;
    case enoperationtype::addclient:
        system("cls");
        ShowAddClient();
        GoToMainMenue();
        break;
    case enoperationtype::deletclient:
        system("cls");
        ShowDeleteClient();
        GoToMainMenue();
        break;
    case enoperationtype::updateclient:
        system("cls");
        ShowUpdateClient();
        GoToMainMenue();
        break;
    case enoperationtype::findclient:
        system("cls");
        ShowFindClient();
        GoToMainMenue();
        break;
    case enoperationtype::exist:
        system("cls");
        ShowExistMenue();
        break ;
    case enoperationtype::transaction:
        system("cls");
        TransactionMenueScreen();

        break;
    }
}

void TransactionMenueScreen()
{
    cout << "\n==========================================================\n";
    cout << "                        Transaction Menue Screen                         \n";
    cout << "\n==========================================================\n";
    cout << "\t [1] Deposite. \n";
    cout << "\t [2] Withdraw. \n";
    cout << "\t [3] Total Balances. \n";
    cout << "\t [4] Main Menue. \n";

    cout << "\n==========================================================\n";
    chooseFromTransactionMenue((enTransaction)readnumber("Choose What to do [1:4]..?"));
}

void ShowMainMenue()
{
    cout << "\n==========================================================\n";
    cout << "                        Main Menue                          \n";
    cout << "\n==========================================================\n";
    cout << "\t [1] Show Client List. \n";
    cout << "\t [2] Add Client To List. \n";
    cout << "\t [3] Delet Client From List. \n";
    cout << "\t [4] Update Client From List. \n";
    cout << "\t [5] Find Client In List. \n";
    cout << "\t [6] Transaction Menue. \n";
    cout << "\t [7] End. \n";
    cout << "\n==========================================================\n";
    chooseFromMainMenue((enoperationtype)readnumber("Choose What to do [1:6]..?"));
}

int main()
{
    ShowMainMenue();
    // apply to extend
}