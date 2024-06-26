// Bank Project part 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
enum enMainScreenOptions {ClientList=1,AddClinet=2,DeleteClinet=3,UpdateClinet=4,FindClient=5,Transaction=6,Logout=7};
const  string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";
void ShowMainMenue();
short ReadScreenChoise();
void BackToTransationScreen();
void ShowTransactionScreen();

struct sClient{ string AccountNumber;
string PinCode; string Name;
string Phone;
double AccountBalance;
bool MarkForDelete = false;
};

//                      Add Client 
vector<string> SplitString(string S1, string Delim){
            vector<string> vString;
            short pos = 0;
            string sWord;
            // define a string variable  // use find() function to get the position of the delimiters 
            while ((pos = S1.find(Delim)) != std::string::npos) {
                sWord = S1.substr(0, pos);
                // store the word 
                if (sWord != "") {
                    vString.push_back(sWord);
                }
                S1.erase(0, pos + Delim.length());
            } if (S1 != "") {
                vString.push_back(S1); // it adds last word of the string.  
            }
            return vString;
        }
sClient ReadNewClient(){
            sClient Client;
            cout << "Enter Account Number? ";
            // Usage of std::ws will extract allthe whitespace character   
            getline(cin >> ws, Client.AccountNumber);
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
 string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
            string stClientRecord = "";
            stClientRecord += Client.AccountNumber + Seperator;
            stClientRecord += Client.PinCode + Seperator;
            stClientRecord += Client.Name + Seperator;
            stClientRecord += Client.Phone + Seperator;
            stClientRecord += to_string(Client.AccountBalance);
            return stClientRecord;
        }

 











 void AddDataLineToFile(string FileName, string stDataLine) {
     fstream MyFile;
   
     MyFile.open(FileName, ios::out | ios::app);
     if (MyFile.is_open()) {
         MyFile << stDataLine << endl;
         MyFile.close();

     }
 }
 

void AddNewClient() {
            sClient Client;
            Client = ReadNewClient();
            AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
        }
void AddClients() { 
    char AddMore = 'Y';
    do {
        system("cls");  
        cout << "Adding New Client:\n\n"; 
        AddNewClient();   
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";  
        cin >> AddMore; 
    }
    while (toupper(AddMore) == 'Y');
}
void ShowAddClientsScreen()
{
    AddClients();
}

 
//                       Show All Client IN Table;
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
    sClient Client;
    vector<string> vClientData; 
    vClientData = SplitString(Line, Seperator);  
    Client.AccountNumber = vClientData[0]; 
    Client.PinCode = vClientData[1];  
    Client.Name = vClientData[2]; 
    Client.Phone = vClientData[3];  
    Client.AccountBalance = stod(vClientData[4]);
    //cast string to double 
    return Client; 
}



vector <sClient> LoadCleintsDataFromFile(string FileName) {
    vector <sClient> vClients; fstream MyFile; 
    MyFile.open(FileName, ios::in);
    //read Mode
    if (MyFile.is_open())     {
        string Line; sClient Client;
        while (getline(MyFile, Line))      
        {
            Client = ConvertLinetoRecord(Line); 
            vClients.push_back(Client);   
        }      
        MyFile.close();  
    }
    return vClients;
} 
 
void PrintClientRecord(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;  
    cout << "| " << setw(10) << left << Client.PinCode;  
    cout << "| " << setw(40) << left << Client.Name; 
    cout << "| " << setw(12) << left << Client.Phone; 
    cout << "| " << setw(12) << left << Client.AccountBalance; 
} 
void PrintAllClientsData(vector <sClient> vClients) {
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
    for (sClient Client : vClients) { PrintClientRecord(Client);   
    cout << endl; }     cout << "\n_______________________________________________________";  
    cout << "_________________________________________\n" << endl; 
}


void ShowAllClientInTable()
{

   

    vector<sClient>vClient=LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClientsData(vClient);





}

//                  Find Client By Account Number;


void PrintClientCard(sClient Client) {
    cout << "\nThe following are the client details:\n"; 
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;   
    cout << "\nName         : " << Client.Name; 
    cout << "\nPhone        : " << Client.Phone; 
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
bool FindClientByAccountNumber(string AccountNumber, sClient& Client) {
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    for (sClient C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            Client = C; return true; 
        } 
    } 
    return false;
} 



 
string ReadClientAccountNumber() 
{
    string AccountNumber = ""; 
cout << "\nPlease enter AccountNumber? "; 
cin >> AccountNumber;
return AccountNumber;
}
void ShowFindClientByAccountNumberScreen()
{

    cout << "===========================================\n";
    cout << "\t\tFind Client Screen\n";
    cout << "===========================================\n";


    string AccountNumber = ReadClientAccountNumber();
    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
        cout << endl;

    }
    else
    {
        cout << "The Client of Account Number (" << Client.AccountNumber << ") is'nt found :-(" << endl;

    }






}
//                       Delete Client 

vector <sClient> DLoadCleintsDataFromFile(string FileName) {
    vector <sClient> vClients; fstream MyFile;
    MyFile.open(FileName, ios::in);
    //read Mode
    if (MyFile.is_open()) {
        string Line; sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
bool DFindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) { 
    
    for (sClient C : vClients) 
    {
        if (C.AccountNumber == AccountNumber) 
        { 
            Client = C; return
                true; 
        }
    } 
    return false;
}
vector <sClient> DSaveCleintsDataToFile(string FileName, vector<sClient> vClients) 
{
    fstream MyFile;   

    MyFile.open(FileName, ios::out);

    //overwrite 
    string DataLine; 
    if (MyFile.is_open())    
  { 

        for (sClient C : vClients)   
  { 
            if (C.MarkForDelete == false)             {
                //we only write records that are not marked for delete.   
                DataLine = ConvertRecordToLine(C); 
                MyFile << DataLine << endl;         
            }  
        }      
        MyFile.close();  
    }
    return
        vClients;
} 
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
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

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

    sClient Client;
    char Answer = 'n'; 
    if (DFindClientByAccountNumber(AccountNumber, vClients, Client)) 
    {

        PrintClientCard(Client); 
        cout << "\n\nAre you sure you want delete this client? y/n ? ";    
        cin >> Answer; 
        if (Answer == 'y' || Answer == 'Y') 
        {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients); 
            DSaveCleintsDataToFile(ClientsFileName, vClients);
            //Refresh Clients
            vClients = DLoadCleintsDataFromFile(ClientsFileName); 
            cout << "\n\nClient Deleted Successfully."; return
                true;   
        }   
    } 
    else    {    
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
        return false;
    }
} 

string DReadClientAccountNumber()
{ 
    string AccountNumber = "";  
    cout << "\nPlease enter AccountNumber? "; 
    cin >> AccountNumber;
    return AccountNumber; 
} 

void ShowDeletClientScreen()
{


    cout << "===========================================\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "===========================================\n";

    vector<sClient>vDClinet = DLoadCleintsDataFromFile(ClientsFileName);
    string ReadAccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(ReadAccountNumber, vDClinet);


}

//                        Updat Clinet And Addet To File;

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
    cin >> Client.AccountBalance; return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';
    if (DFindClientByAccountNumber(AccountNumber, vClients, Client))
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
            }    DSaveCleintsDataToFile(ClientsFileName, vClients);
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

void ShowUpdateClientScreen()
{

    cout << "===========================================\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "===========================================\n";



    vector<sClient>vClient = DLoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = DReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClient);


}

//                      Transaction 
enum enTransaction {
    enDeposit=1,enWithDrows=2,enTotalBalances=3,enBackToMainScreen=4
};
//                               Add Balance 
int ReadHowManyBalanceWantAdd()
{
    int BalanceAdd = 0;
    cout << "enter how much do you want to Add to your Account ?" << endl;
    cin >> BalanceAdd;
    return BalanceAdd;


}
string ReadClientAccountNumberTrans()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
bool FindClinetAccountNumberAndAdd(string AccountNumber, vector<sClient>& vClients,int BalanceAdd)
{ 
    
    sClient Client;
    char Answer = 'n';
    if (DFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << endl;
        BalanceAdd = ReadHowManyBalanceWantAdd();
        cout << "\n\nAre you sure you want Add Balance to this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                  C.AccountBalance =C.AccountBalance + BalanceAdd;
                    break;
                }
            }    DSaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nThe Process gone Successfully.your Balance is" << Client.AccountBalance+BalanceAdd << endl;
            return true;
        }
    }
    else
    {
       
       cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
       return false;
      
        
       
        
    }
}

void ShowClientAddBalance()
{
    cout << "===========================================\n";
    cout << "\t\t Deposit Screen\n";
    cout << "===========================================\n";




    int BalanceAdd = 0;
    sClient Client;
    vector<sClient>vClients = DLoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber=ReadClientAccountNumberTrans();
    FindClinetAccountNumberAndAdd(AccountNumber, vClients, BalanceAdd);
     
  


}
//                           Less Balance



int ReadHowManyBalanceWantWithDrow()
{
    int BalanceWithDrows = 0;
    cout << "enter how much do you want to Add to your Account ?" << endl;
    cin >> BalanceWithDrows;
    return BalanceWithDrows;


}

bool FindClinetAccountNumberWithDrow(string AccountNumber, vector<sClient>& vClients, int BalanceLess)
{

    sClient Client;
    char Answer = 'n';
    if (DFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << endl;
        BalanceLess = ReadHowManyBalanceWantAdd();
        cout << "\n\nAre you sure you want With Drow Balance to this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    if(BalanceLess<=C.AccountBalance){
                    C.AccountBalance = C.AccountBalance + (BalanceLess)*-1;
                    break;
                    }
                    else
                    {
                        cout << "Amount Exeeds the balance ,you can drowwith " << C.AccountBalance;
                        cout << endl;
                        cout << "pleas enter another withdrow amount :" << endl;
                        cin >> BalanceLess;
                    }
                }
            }    DSaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nThe Process gone Successfully.your Balance is" << Client.AccountBalance +( BalanceLess)*-1 << endl;
            return true;
        }
    }
    else
    {

        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;




    }
}
void ShowClientWithDrowBalance()
{

    cout << "===========================================\n";
    cout << "\t\tDrow With Screen\n";
    cout << "===========================================\n";

    int BalanceLess = 0;
    sClient Client;
    vector<sClient>vClients = DLoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumberTrans();
    FindClinetAccountNumberWithDrow(AccountNumber, vClients, BalanceLess);




}

//                               Sum of Balanceces





void PrintSumClientRecord(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

int SumOfAllBalances(vector<sClient>vClinet)
{
    
    int Sum = 0;

    for (sClient &SumOf : vClinet)
    {
        Sum += SumOf.AccountBalance;
    }

    return Sum;


}
void PrintAllClientsData(vector <sClient> vClients,int SumOfBalances) {

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }     cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    cout << "                           Total Balance :" <<SumOfBalances << endl;
}

void ShowSumOfBalancesScreen()
{

    cout << "===========================================\n";
    cout << "\t\t Sum Of Balances Screen\n";
    cout << "===========================================\n";

    vector<sClient>vClinet = DLoadCleintsDataFromFile(ClientsFileName);
    int Sum = SumOfAllBalances(vClinet);
    PrintAllClientsData(vClinet,Sum);


}





void BackToTransationScreen()
{
    cout << "pres any key to back to main screen \n" << endl;
    system("pause>0");
    ShowTransactionScreen();
}
void BackToMainScreen()
{
    cout << "pres any key to back to main screen \n" << endl;
    system("pause>0");
    ShowMainMenue();
}

void PreformTransactionScreen(enTransaction Transaction)
{

    switch (Transaction)
    {
    case enDeposit:
        system("cls");
        ShowClientAddBalance();
        BackToTransationScreen();
        break;
    case enWithDrows:
        system("cls");
        ShowClientWithDrowBalance();
        BackToTransationScreen();
        break;
    case enTotalBalances:
        system("cls");
        ShowSumOfBalancesScreen();
        BackToTransationScreen();
        break;
    case enBackToMainScreen:
        system("cls");
       ShowMainMenue();
        break;
  
    }


}
void ShowTransactionScreen()
{

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransaction Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2]WithDrows.\n";
    cout << "\t[3] TotalBalnces.\n";
    cout << "\t[4]BackToMainScreen.\n";

    cout << "===========================================\n";
    PreformTransactionScreen(enTransaction(ReadScreenChoise()));








}
//                                        Login Screen 











void PreformMainScreen(enMainScreenOptions Main)
{
   

    switch (Main)
    {

    case ClientList:


        system("cls");
        ShowAllClientInTable();
        BackToMainScreen();

        break;
       
    case  AddClinet:
        system("cls");
        ShowAddClientsScreen();
        BackToMainScreen();
        break;

    case DeleteClinet:
        system("cls");
        ShowDeletClientScreen();
        BackToMainScreen();




        break;
    case UpdateClinet:
        system("cls");
        ShowUpdateClientScreen();
        BackToMainScreen();


        break;
    case FindClient:
        system("cls");
        ShowFindClientByAccountNumberScreen();
        BackToMainScreen();

        break;
    case Transaction:
        system("cls");
        ShowTransactionScreen();

    

    case Logout:
        system("cls");
        BackToMainScreen();
        break;
    }











}
short ReadScreenChoise()
{
    short Choise = 0;
    cout << "What do you want to choise ?" << endl;
    cin >> Choise;
    return Choise;
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
        cout << "\t[6] Transaction.\n";
        cout << "\t[7] Mange Users.\n";
        cout << "\t[8] Logout.\n";   
        cout << "===========================================\n";
        PreformMainScreen(enMainScreenOptions(ReadScreenChoise()));
   }
       


















 




 
 
 
 
 
    

 
 

 
int main()
{
   
       
    ShowMainMenue();

   
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
