#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;


struct entry{
    string date;
    float amount;
    int type;
    string note;
};
vector<entry> entries;
float balance;
int entrynum;
string path = "C:\\Users\\Aditya\\Desktop\\Programming\\Cashflo";

string get_current_date();
void initialize();
void menu();
void adddebit();
void addcredit();
void transactionhistory();
void editbalance();
void writedatafile();
void exit();


int main(){
    initialize();
    return 0;
}

void menu(){
    system("cls");
    cout << "Current Balance:  Rs. " << balance <<endl << endl << endl;
    cout << "1. Add Debit Record\n2. Add Credit Record\n3. View Transaction History\n4. Edit Balance\n\n0.Exit\n\n\nPlease Enter your option number!\n";
    int menuinput;
    cin >> menuinput;

    switch(menuinput){
        case 1: 
        adddebit();
        break;
        case 2:
        addcredit();
        break;
        case 3:
        transactionhistory();
        break;
        case 4:
        editbalance();
        break;
        case 0:
        exit();
        break;
        default:
        system("cls");
        cout << "Please choose a valid option!\n\n\n";
        system("pause");
        menu();
        break;
        }

}

void initialize(){
    chdir(path.c_str());
    fstream data("data.txt");
    string entriesstring1, entriesstring2;

    getline(data, entriesstring1);
    balance = stof(entriesstring1);
    getline(data, entriesstring2);
    entrynum = stoi(entriesstring2);
    entries.resize(entrynum);
    // cout << "Balance is: " << balance << "Entrynum is : " << entrynum << endl;
    // system("pause");
    int counter = 0;
    string temp;
    getline(data, temp);
    while (counter < entrynum){
        string temp1 = "0", temp2="0";
        getline(data, entries[counter].date);
        getline(data, temp1);
        getline(data, temp2);
        getline(data, entries[counter].note);
        entries[counter].amount = stoi(temp1);
        entries[counter].type;
            string temp;
            getline(data, temp);
        counter++;
}
data.close();
menu();
}

string get_current_date() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm *tm = localtime(&t);
    stringstream ss;
    ss << put_time(tm, "%d-%m-%Y");
    return ss.str();
}

void writedatafile(){
    chdir(path.c_str());
    ofstream data("data.txt", ios::trunc);
    data << balance <<endl;
    data << entrynum << endl;
    data << endl;
    int counter = 0;
    while((counter) < entrynum){
        data << entries[counter].date << endl;
        data << entries[counter].amount << endl;
        data << entries[counter].type << endl;
        data << entries[counter].note << endl <<endl;
        counter++;
    }
    data.close();
}

void adddebit(){
    system("cls");
    float debitamount;
    string debitnote;
    cout << "Please Enter the Amount to Debit:\n";
    cin >> debitamount;
    cin.ignore(); 
    cout << "Please Enter the Note: \n";
    getline(cin, debitnote);
    string date = get_current_date();

    entry debitentry;
    debitentry.amount = debitamount;
    debitentry.note = debitnote;
    debitentry.type = 0;
    debitentry.date = date;

    entries.push_back(debitentry);

    balance -= debitamount;
    entrynum++;
    writedatafile();
    menu();
}
void addcredit(){
    system("cls");
    float creditamount;
    string creditnote;
    cout << "Please Enter the Amount to Credit:\n";
    cin >> creditamount;
    cin.ignore(); 
    cout << "Please Enter the Note: \n";
    getline(cin, creditnote);
    string date = get_current_date();

    entry debitentry;
    debitentry.amount = creditamount;
    debitentry.note = creditnote;
    debitentry.type = 1;
    debitentry.date = date;

    entries.push_back(debitentry);

    balance += creditamount;
    entrynum++;
    writedatafile();
    menu();
};
void transactionhistory(){
    system("cls");
    cout << " TRANSACTION HISTORY\n\n\n";

    int counter = 0;
    while(counter<entrynum){
        if(entries[counter].type == 0){
            cout << "Transaction Type: Debit" << endl;
        }else if(entries[counter].type == 1){
            cout << "Transaction Type: Credit" << endl;
        }else if(entries[counter].type == 2){
            cout << "Balance Adjust" << endl;
        }
        cout<< "Date: " << entries[counter].date << endl;
        cout << "Amount: Rs. " << entries[counter].amount << endl;
        cout << entries[counter].note << endl <<endl<<endl;
        counter++;
    }
    system("pause");
    menu();
};
void editbalance(){
        system("cls");
        cout << "Old Balance: Rs. " << balance;
        cout << "\n\n\nPlease enter the new Balance"<< endl;
        float newbalance,difference;
        cin >> newbalance;
        difference = newbalance - balance;
        cout<< "\n\n\nDifference in Balance is: " << difference;
        string date = get_current_date();
        string editnote;
        cin.ignore();
        cout << "\n\nEnter the note: " << endl;
        getline(cin,editnote);
        entry editentry;
        editentry.amount = difference;
        editentry.note = editnote;
        editentry.type = 2;
        editentry.date = date;

        entries.push_back(editentry);

        balance = newbalance;
        entrynum++;
        writedatafile();
        menu();
};

void exit(){};