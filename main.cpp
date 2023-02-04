// #########################################################################################
// ##                                                                                     ##
// ##                                 Version 0.1 - alpha                                 ##
// ##                                                                                     ##
// #########################################################################################
// ##    MIT License                                                                      ##
// ##                                                                                     ##
// ##    Copyright (c) 2023 Aditya Aparadh                                                ##
// ##                                                                                     ##
// ##    Permission is hereby granted, free of charge, to any person obtaining a copy     ##
// ##    of this software and associated documentation files (the "Software"), to deal    ##
// ##    in the Software without restriction, including without limitation the rights     ##
// ##    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        ##
// ##    copies of the Software, and to permit persons to whom the Software is            ##
// ##    furnished to do so, subject to the following conditions:                         ##
// ##                                                                                     ##
// ##    The above copyright notice and this permission notice shall be included in all   ##
// ##    copies or substantial portions of the Software.                                  ##
// ##                                                                                     ##
// ##    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       ##
// ##    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         ##
// ##    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      ##
// ##    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           ##
// ##    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    ##
// ##    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    ##
// ##    SOFTWARE.                                                                        ##
// #########################################################################################

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#define WINDOWS
using namespace std;

struct entry
{
    string date;
    float amount;
    int type;
    string note;
};
vector<entry> entries;
float balance;
int entrynum;

string get_current_date();
void initialize();
void menu();
void adddebit();
void addcredit();
void transactionhistory();
void editbalance();
void writedatafile();
void exit();
void exportmenu();
void csvexport();
void jsonexport();
void clearscreen();

int main()
{
    initialize();
    return 0;
}

void menu()
{
    clearscreen();
    cout << "##################################" << endl;
    cout << "##                              ##" << endl;
    cout << "##         CASHFLO CLI          ##" << endl;
    cout << "##          v0.1 - alpha        ##" << endl;
    cout << "##                              ##" << endl;
    cout << "##################################" << endl
         << endl
         << endl;
    cout << "Current Balance:  Rs. " << balance << endl
         << endl
         << endl;
    cout << "1. Add Debit Record\n2. Add Credit Record\n3. View Transaction History\n4. Edit Balance\n5. Export\n\n0.Exit\n\n\nPlease Enter your option number:\n";
    int menuinput;

    cin >> menuinput;

    switch (menuinput)
    {
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
    case 5:
        exportmenu();
        break;
    case 0:
        exit();
        break;
    default:
        clearscreen();
        cout << "Please choose a valid option!\n\n\n";
        system("pause");
        menu();
        break;
    }
}

void initialize()
{
    fstream data("data.txt");
    string entriesstring1, entriesstring2;

    getline(data, entriesstring1);
    balance = stof(entriesstring1);
    getline(data, entriesstring2);
    entrynum = stoi(entriesstring2);
    entries.resize(entrynum);
    int counter = 0;
    string temp;
    getline(data, temp);
    while (counter < entrynum)
    {
        string temp1 = "0", temp2 = "0";
        getline(data, entries[counter].date);
        getline(data, temp1);
        getline(data, temp2);
        getline(data, entries[counter].note);
        entries[counter].amount = stof(temp1);
        entries[counter].type = stoi(temp2);
        string temp;
        getline(data, temp);
        counter++;
    }
    data.close();
    menu();
}
string get_current_date()
{
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm *tm = localtime(&t);
    stringstream ss;
    ss << put_time(tm, "%d-%m-%Y");
    return ss.str();
}
void writedatafile()
{
    ofstream data("data.txt", ios::trunc);
    data << balance << endl;
    data << entrynum << endl;
    data << endl;
    int counter = 0;
    while ((counter) < entrynum)
    {
        data << entries[counter].date << endl;
        data << entries[counter].amount << endl;
        data << entries[counter].type << endl;
        data << entries[counter].note << endl
             << endl;
        counter++;
    }
    data.close();
}
void adddebit()
{
    clearscreen();
    float debitamount;
    string debitnote;
    cout << "Entered Fast Entry mode" << endl
         << "[0 to go back to menu]" << endl
         << endl;
    cout << "Please Enter the Amount to Debit:\n";
    cin >> debitamount;
    if (debitamount == 0)
    {
        menu();
    }
    else
    {
        cin.ignore();
        cout << "Please Enter the Note: \n";
        getline(cin, debitnote);
        if (debitnote == "0")
        {
            menu();
        }
        else
        {
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
            adddebit();
        }
    }
}
void addcredit()
{
    clearscreen();
    float creditamount;
    string creditnote;
    cout << "Entered Fast Entry mode" << endl
         << "[0 to go back to menu]" << endl
         << endl;
    cout << "Please Enter the Amount to Credit:\n";
    cin >> creditamount;
    if (creditamount == 0)
    {
        menu();
    }
    else
    {
        cin.ignore();
        cout << "Please Enter the Note: \n";
        getline(cin, creditnote);
        if (creditnote == "0")
        {
            menu();
        }
        else
        {
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
            addcredit();
        }
    }
}
void transactionhistory()
{
    clearscreen();
    cout << " TRANSACTION HISTORY\n\n\n";
    int counter = 0;
    while (counter < entrynum)
    {
        if (entries[counter].type == 0)
        {
            cout << "Transaction Type: Debit" << endl;
        }
        else if (entries[counter].type == 1)
        {
            cout << "Transaction Type: Credit" << endl;
        }
        else if (entries[counter].type == 2)
        {
            cout << "Balance Adjust" << endl;
        }
        cout << "Date: " << entries[counter].date << endl;
        cout << "Amount: Rs. " << entries[counter].amount << endl;
        cout << entries[counter].note << endl
             << endl
             << endl;
        counter++;
    }
    int returntomenu;
    cout << "\n\n[0 to go back]:";
    cin >> returntomenu;
    menu();

};
void editbalance()
{
    clearscreen();
    cout << "Old Balance: Rs. " << balance;
    cout << "\n\n\nPlease enter the new Balance" << endl;
    float newbalance, difference;
    cin >> newbalance;
    difference = newbalance - balance;
    cout << "\n\n\nDifference in Balance is: " << difference;
    string date = get_current_date();
    string editnote;
    cin.ignore();
    cout << "\n\nEnter the note: " << endl;
    getline(cin, editnote);
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
void exit()
{
    clearscreen();
}
void exportmenu()
{
    clearscreen();
    cout << "Please choose the export format: \n\n1.CSV\n2.JSON\n\n0.Back to Main Menu" << endl
         << endl
         << endl;
    int exportmenuinput;
    cin >> exportmenuinput;

    switch (exportmenuinput)
    {
    case 1:
        csvexport();
        break;
    case 2:
        jsonexport();
        break;
    case 0:
        menu();
        break;
    default:
        clearscreen();
        cout << "Please choose a valid option!\n\n\n";
        system("pause");
        exportmenu();
        break;
    }
}
void csvexport()
{
    system("type nul > export.csv");
    ofstream data("export.csv", ios::trunc);
    data << "Transaction Type, Transaction Date, Amount, Notes" << endl;
    int counter = 0;
    while ((counter) < entrynum)
    {

        if ((entries[counter].type) == 0)
        {
            data << "Debit, ";
        }
        else if ((entries[counter].type) == 1)
        {
            data << "Credit, ";
        }
        else if ((entries[counter].type) == 2)
        {
            data << "Balance Adjust, ";
        }

        data << entries[counter].date << ", ";
        data << entries[counter].amount << ", ";
        data << entries[counter].note << endl;
        counter++;
    }
    data.close();
    clearscreen();
    cout << "CSV Exported Successfully!\n\n\n\n\n";
    system("pause");
    menu();
}
void jsonexport()
{
    system("type nul > export.json");
    ofstream data("export.json", ios::trunc);
    data << "[" << endl;
    int counter = 0;
    while ((counter) < entrynum)
    {
        data << "{" << endl;
        if ((entries[counter].type) == 0)
        {
            data << "\"Transaction Type\": \"Debit\"," << endl;
        }
        else if ((entries[counter].type) == 1)
        {
            data << "\"Transaction Type\": \"Credit\"," << endl;
        }
        else if ((entries[counter].type) == 2)
        {
            data << "\"Transaction Type\": \"Balance Adjust\"," << endl;
        }

        data << "\"Transaction Date\": \"" << entries[counter].date << "\"," << endl;
        data << "\"Amount\": " << entries[counter].amount << "," << endl;

        if (counter == entrynum - 1)
        {
            data << "\"Notes\": \"" << entries[counter].note << "\"" << endl
                 << "}" << endl;
        }
        else
        {
            data << "\"Notes\": \"" << entries[counter].note << "\"" << endl
                 << "}," << endl;
        }
        counter++;
    }
    data << "]";
    data.close();
    clearscreen();
    cout << "JSON Exported Successfully!\n\n\n\n\n";
    system("pause");
    menu();
}
void xlsxexport()
{
    system("type nul > export.csv");
    ofstream data("export.csv", ios::trunc);
    data << "Transaction Type, Transaction Date, Amount, Notes" << endl;
    int counter = 0;
    while ((counter) < entrynum)
    {

        if ((entries[counter].type) == 0)
        {
            data << "Debit, ";
        }
        else if ((entries[counter].type) == 1)
        {
            data << "Credit, ";
        }
        else if ((entries[counter].type) == 2)
        {
            data << "Balance Adjust, ";
        }

        data << entries[counter].date << ", ";
        data << entries[counter].amount << ", ";
        data << entries[counter].note << endl;
        counter++;
    }
    data.close();
    system("Excel /e /a \"export.csv\" \"export.xlsx\" ");
    system("pause");
    clearscreen();
    cout << "XLSX Exported Successfully!\n\n\n\n\n";
    system("pause");
    menu();
}
void clearscreen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}
