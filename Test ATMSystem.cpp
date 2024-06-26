#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
enum enMainScreenOptions {QuickWithDrow = 1, WithDrow = 2, Deposit = 3, ShowBalance = 4, Back = 5};
enum enQuickWithDrow
{
    One = 1, Tow = 2, Three = 3, Four = 4, Five = 5, Six = 6, Eight = 7, OneThousend = 8;
};
const  string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";
void ShowMainMenue();
short ReadScreenChoise();
void BackToTransationScreen();
void ShowTransactionScreen();

struct sClient {
	string AccountNumber;
	string PinCode; string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};









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
    vector <sClient> vClients;
    fstream MyFile;
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

short ReadScreenChoise()
{
    short Choise = 0;
    cout << "What do you want to choise ?" << endl;
    cin >> Choise;
    return Choise;
}
void PreformQuickWithDrow(enQuickWithDrow Quick)
{
    sClient Client;
    switch (Quick)
    {
    case One:
       return Client.AccountBalance - 100;
        break;
    case Tow:
        return Client.AccountBalance - 200;
        break;
    case Three:
        return Client.AccountBalance - 300;
        break;
    case Four:
      return   Client.AccountBalance - 400;
        break;
    case Five:
        return Client.AccountBalance - 500;
        break;
    case Six:
        return Client.AccountBalance - 600;
        break;
    case Eight:
        return Client.AccountBalance - 800;
        break;
    case OneThousend:
        return Client.AccountBalance - 1000;
        break;
    }





}

void QuickWithDrowScreen()
{


    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick WithDrow\n";
    cout << "===========================================\n";
    cout << "\t[1] 100\t[2] 200\n";
    cout << "\t[3] 300\t[4] 400\n";
    cout << "\t[5] 500\t[6] 600\n";
    cout << "\t[7] 800\t[8] 1000\n";
    cout << "\t[9] Back to main menue"
    cout << "===========================================\n";

    PreformQuickWithDrow(enQuickWithDrow(ReadScreenChoise()));

}
void PreformLogInScreen(enMainScreenOptions Main)
{

    switch (Main)
    {
    case QuickWithDrow:
        system("cls");
        QuickWithDrowScreen();

        break;
    case WithDrow:
        break;
    case Deposit:
        break;
    case ShowBalance:
        break;
    case Back:
        break;
    default:
        break;
    }












}
void LogInScreen()
{


    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransaction Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick WithDrow.\n";
    cout << "\t[2]WithDrow.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4]show Balance.\n";
    cout<<"\t[5] Back to main menue"
    cout << "===========================================\n";
    PreformLogInScreen(enMainScreenOptions(ReadScreenChoise()));

}


int main()
{

    LoginScreen();

}


