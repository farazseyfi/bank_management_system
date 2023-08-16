#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{
    int account_number;
    char name[50];
    int deposit;
    char type;

public:
    void create_account(); //function to get data from the user
    void show_account() const; //function to show data on the screen
    void modify(); //function to modify account data
    void dep(int); //function to accept deposit amount and add to balance
    void draw(int); //function to accept withdrawal amount and subtract from balance
    void report() const; //function to show account data in tabular format
    int retacnumber() const; //function to return account number
    int returndeposit() const; //function to return balance amount
    char returntype() const; //function to return type of account
};

void account::create_account()
{
    cout << "\nEnter The account No. : ";
    cin >> account_number;
    cout << "\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin >> deposit;
    cout << "\n\n\nAccount Created..";
}

void account::show_account() const
{
    cout << "\nAccount No. : " << account_number;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void account::modify()
{
    cout << "\nAccount No. : " << account_number;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << account_number << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacnumber() const
{
    return account_number;
}

int account::returndeposit() const
{
    return deposit;
}

char account::returntype() const
{
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);


int main()
{
    char ch;
    int num;
    //intro();
    do
    {
        system("cls");
        cout << "Optional assigment for ENSC 251 (Simon fraser University), created by Faraz Seyfi & Ali-Aryo" << endl;
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            modify_account(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using our bank management system software!";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "Error in file opening, try again";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacnumber() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account_data.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "Error in file opening,Try again" << endl;
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.retacnumber() == n)
        {
            ac.show_account();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account_data.dat", ios::binary);
    if (!inFile)
    {
        cout << "Error in file opening, try again"<< endl;
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacnumber() != n)
        {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account_data.dat");
    rename("Temp.dat", "account_data.dat");
    cout << "\n\n\tRecord Deleted!"<<endl ;
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "Error in file opening, try again"<<endl;
        return;
    }
    cout << "Account holders list: " << endl;
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account_data.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "Error in file opening, try again"<< endl;
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.retacnumber() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.returndeposit() - amt;
                if ((bal < 500 && ac.returntype() == 'S') || (bal < 1000 && ac.returntype() == 'C'))
                    cout << "Insufficient balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

