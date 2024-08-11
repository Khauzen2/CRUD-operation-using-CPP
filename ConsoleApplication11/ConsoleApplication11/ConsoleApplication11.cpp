#include <iostream> 
#include<fstream> 
#include<string> 
#include<iomanip> 
#include<vector>
 
using namespace std; 
const string ClientFileName = "Clients.txt";
         
struct sClient{ 
    string AccountNumber; 
    string PinCode; 
    string Name; 
    string Phone; 
    string AccountBalance; 
    bool DeletMark = false; 
  };  

sClient ReadRecord() {
    sClient Client; 
    cout << "Enter Client Data Please \n"; 
    cout << "Enter Account Number :"; 
    getline(cin>>ws, Client.AccountNumber); 

    cout << "Enter PinCode :";
    getline(cin, Client.PinCode);
    cout << "Enter Your Name :";
    getline(cin, Client.Name);
    cout << "Enter Phone :";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance :";
    getline(cin, Client.AccountBalance); 
    return Client; 

 } 

string ConvertRecorToLine(sClient Client , string Delim = "#//#") {
    string S2 = ""; 
    S2 += Client.AccountNumber + Delim; 
    S2 += Client.PinCode + Delim;
    S2 += Client.Name + Delim;
    S2 += Client.Phone + Delim;
    S2 += Client.AccountBalance; 
    return S2; 
} 
 
vector <string> splitString(string s , string delim="#//#") {
    vector<string>vString; 
    int pos = 0; 
    string sWords = " "; 
    while ((pos = s.find(delim)) != std::string::npos) {
        sWords = s.substr(0, pos); 
        if (sWords != " ") {
            vString.push_back(sWords); 
           
        }   
        s.erase(0, pos + delim.length()); 
    }
    if (s != "") {
        vString.push_back(s);
    }
    return vString; 
} 
 
sClient convertLineToRecord(string Line , string Delim = "#//#") {
    vector<string>vString; 
    sClient Client;  
    vString = splitString(Line); 
    Client.AccountNumber = vString[0]; 
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = vString[4]; 
    return Client;  
} 

void PrintClientsRecord(sClient Client) {
   
    cout << "The Following is the extracted Client Record \n\n\n";  
    cout << "\nAccount Number :" << Client.AccountNumber; 
    cout << "\nPin Code        :" << Client.PinCode;
    cout << "\nName            :" << Client.Name;
    cout << "\nPhone           :" << Client.Phone;
    cout << "\nAccount Balance :" << Client.AccountBalance;


}
void AddDataLineToFile(string FileName, string stDataLine) {
    fstream MyFile;
    MyFile.open(ClientFileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << stDataLine << endl;
        MyFile.close();
    }

}
void AddNewClient() {
    sClient Client;
    Client = ReadRecord();
    AddDataLineToFile(ClientFileName, ConvertRecorToLine(Client));
}
 
void AddClients() {
    char Add = 'y'; 
    do {
        system("cls");
        AddNewClient();
        cout << "Client Add successfully Do you want to add more ?(Y / N) \n"; 
        cin >> Add; 
    } while (toupper(Add) == 'Y'); 
       
}  

vector<sClient> LoadDataFromFile(string FileName) {
    vector<sClient> vClient; 
    
    fstream MyFile; 
    MyFile.open(ClientFileName, ios::in); 
    if (MyFile.is_open()) {
        string Line;
        sClient Client; 
        while (getline(MyFile , Line))
        {
            Client = convertLineToRecord(Line); 
            vClient.push_back(Client); 

        }
        MyFile.close(); 
    }
    return vClient; 


}

//void PrintClientRecord(sClient Client) {
//    cout << "account Number is : "<< Client.AccountNumber;
//    cout << "\nPin code is : " << Client.PinCode;
//    cout << "\nName is : " << Client.Name;
//    cout << "\nPhone is  is : " << Client.Phone;
//    cout << "\nAccount Balance is :" << Client.AccountBalance;
//    cout << endl; 
//} 
void PrintClientRecord(sClient Client)
{
    //std::cout.setf(std::ios::left);

    cout << "|  " <<left  << setw(15) << Client.AccountNumber;
    cout << "|  " << left << setw(10) << Client.PinCode;
    cout << "|  " << left << setw(40) << Client.Name;
    cout << "|  " << left << setw(12) << Client.Phone;
    cout << "|  " << left << setw(12) << Client.AccountBalance;
    cout << endl;
}

void PrintAllClientsData(vector<sClient>vClient) {
    cout << "\n\t\t\t\t\tClient List(" << vClient.size() << ") Client(s).";
    cout << "\n____________________________________________________________________________________________________________\n";
    cout << "|  " << left << setw(15) << "Account Number";
    cout << "|  " << left << setw(10) << "Pin Code";
    cout << "|  " << left << setw(40) << "Client Name";
    cout << "|  " << left << setw(12) << "Phone";
    cout << "|  " << left << setw(12) << "Balance";
    cout << "\n____________________________________________________________________________________________________________\n";
    for (sClient Client : vClient) {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n______________________________________________________________________________________________________________\n";

}
 

 
bool FindClientByAccountNumber(string AccountNumber , sClient& Client) {
    vector<sClient>vClient = LoadDataFromFile(ClientFileName); 
    for (sClient q : vClient) {
        if (q.AccountNumber == AccountNumber) {
            Client = q;  
            return true; 
        }
    }
    return false; 
}
string ReadAccountNumber() {
    string AccountNumber;
    cout << "Please Enter The Account Number you are searching for\n";
    cin >> AccountNumber;
    return AccountNumber;
} 


bool FindClientByAccountNumber(string AccountNumber,vector<sClient>vClient ,  sClient& Client) {
   
    for (sClient q : vClient) {
        if (q.AccountNumber == AccountNumber) {
            Client = q;
            return true;
        }
    }
    return false;
} 

bool MarkDeletRecord(string AccountNumber  , vector<sClient>& vClient) {
     
    for (sClient& q : vClient) {
        if (q.AccountNumber == AccountNumber) {
            q.DeletMark = true; 
            return true; 
        }
    } 
    return false; 
    } 
vector <sClient> SaveClientToFile(string FileName , vector<sClient>&vClient) { 
    fstream MyFile; 
    MyFile.open(ClientFileName, ios::out); 
    string DataLine; 
    if (MyFile.is_open()) {
        for (sClient w : vClient) {
            if (w.DeletMark == false) {
                DataLine = ConvertRecorToLine(w); 
                MyFile << DataLine << endl; 
            }
        } 
        MyFile.close(); 
    }
    return vClient; 

}

bool DeletClientByAccountNumber(string AccountNumber , vector<sClient>vClient) {
    sClient Client; 
    char Answer = 'n';  

    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        PrintClientRecord(Client);  
        cout << "Are you sure You want to Delete this record ? (Y / N) \n"; 
        cin >> Answer;  
        if (Answer == 'Y' || Answer == 'y') {
            MarkDeletRecord(AccountNumber, vClient); 
            SaveClientToFile(ClientFileName, vClient);
            vClient = LoadDataFromFile(ClientFileName); 
            cout << "\n\nClient Deleted Successfully."; 
            return true; 
        }
    }
    else { 
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}  

sClient ChangClientRecord(string AccountNumber) {

    sClient Client; 
    Client.AccountNumber = AccountNumber; 

    cout << "Enter Pin Code : "; 
    getline(cin >> ws, Client.PinCode); 

    cout << "Enter Name : ";
    getline(cin >> ws, Client.Name);

    cout << "Enter Phone : ";
    getline(cin >> ws, Client.Phone);

    cout << "Enter Account balance : ";
    getline(cin >> ws, Client.AccountBalance); 
    return Client; 
}

bool UpdatClientRecord(string AccountNumber , vector<sClient>& vClient) { 
    sClient Client; 
    char answer = 'n'; 
     
    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        PrintClientRecord(Client); 
        cout << "\n\n Are you sure you want to edit this record (Y/N)\n"; 
        cin >> answer; 
        if (answer == 'y' || answer == 'Y') {
            for (sClient & q : vClient) {
                if (q.AccountNumber == AccountNumber) {
                    q = ChangClientRecord(AccountNumber); 
                    break; 
                }
            } 
            SaveClientToFile(ClientFileName, vClient); 
            cout << "Client update successfully \n"; 
            return true; 

        }
    }
    else {
        cout << "We didnt find the Account Number " << AccountNumber << "here We sorry \n"; 
        return false; 
    }
     

} 

void ShowMenuScreen() {
    cout << "==============================================\n";  
    cout << "\t\t Main Menu Screen\n"; 
    cout << "==============================================\n"; 
    cout << "\t\t[1] Show Client List.\n"; 
    cout << "\t\t[2] Add New Clients.\n";
    cout << "\t\t[3] Delet Client.\n";
    cout << "\t\t[4] Update Client Info.\n";
    cout << "\t\t[5] Find Client .\n";
    cout << "\t\t[6] Exit.\n";
    cout << "==============================================\n"; 
    cout << "Chose what do you want to do ? [1 to 6] ?\n"; 
    

 
} 

void ShowBackMainMenu() {
    cout << "\n\nPress Any Key To back to Main Menu \n\n";
    system("pause");
    system("cls"); 
    ShowMenuScreen(); 
} 



int main()
{  
 //   AddClients(); 
 //
 ///*   sClient Client; 
 //   string AccountNumber = ReadAccountNumber();*/
 //  
 //  /* if (FindClientByAccountNumber(AccountNumber, Client)) {
 //       PrintClientRecord(Client); 
 //   }
 //   else {
 //       cout << "\n\nAccount Number  "<< AccountNumber <<" Not Found; ";
 //   }*/ 

 //   vector<sClient>vClient = LoadDataFromFile(ClientFileName); 
 //   string AccountNumber = ReadAccountNumber();
 //   DeletClientByAccountNumber(AccountNumber, vClient); 
 //   UpdatClientRecord(AccountNumber, vClient);  
    vector<sClient>vClient = LoadDataFromFile(ClientFileName);
    sClient Client; 
    ShowMenuScreen();  
    do {
        short Number;
        cin >> Number;
        switch (Number)
        {
        case 1:
            system("cls");
            PrintAllClientsData(vClient);
            ShowBackMainMenu();
            break;
        case 2:
            system("cls");
            AddNewClient();
            ShowBackMainMenu();
            break;

        case 3:
            system("cls");
            DeletClientByAccountNumber(ReadAccountNumber(), vClient);
            ShowBackMainMenu();
            break;

        case 4:
            system("cls");
            UpdatClientRecord(ReadAccountNumber(), vClient);
            ShowBackMainMenu();
            break;
        case 5:
            system("cls");

            FindClientByAccountNumber(ReadAccountNumber(), vClient, Client);
            PrintClientRecord(Client);
            ShowBackMainMenu();
            break;
        case 6:
            system("pause");
            exit(0); 


        default:
            break;
        }
    } while (true); 
  
    system("pause");
    return 0; 
}

