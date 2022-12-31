#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;


struct entry{
    string date;
    int amount;
    int type;
    string note;
};
vector<entry> entries;
int entrynum;
string path = "C:\\Users\\Aditya\\Desktop\\Programming\\Cashflo";

void initialize();
void menu();

int main(){
    initialize();
    return 0;
}

void menu(){
    system("cls");
    cout << "1. Add Debit Record\n2. Add Credit Record\n3. View Transaction History\n4. Edit Balance\n\n\nPlease Enter your option number!\n";
    int menuinput;
    cin >> menuinput;

}

void initialize(){
    chdir(path.c_str());
    
}