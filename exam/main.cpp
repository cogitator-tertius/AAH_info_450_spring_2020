#include<iostream>
#include<string>
using namespace std;

class account {
    private:
        string name;
        long taxID;
        double balance;
    protected:
        int numberDeposits;
        int numberWithdraws;
    public:
        account(){};
        account(string account_name, long int tax_id, double starting_balance)
        {
            SetName(account_name);
            SetTaxID(tax_id);
            SetBalance(starting_balance);
        }
        void SetName(string account_name)
        {
            if(account_name == "\0" || account_name == "")
            {
                cout << "Please enter a valid name for this account." << endl;
            }
            else{name = account_name;}            
        }
        void SetTaxID(long int tax_id)
        {
            int length = 0;
            long int n = tax_id;
            while(n !=0)
            {
                n /= 10;
                length++;
            }
            if(n != 9)
            {
                cout << "Please enter a valid 9-digit tax ID number." << endl;
            }
            else
            {
                taxID = tax_id;
            }
        }
        void SetBalance(double balance_amount)
        {
            if(balance_amount < 0)
            {
                cout << "Please enter a non-negative amount for the account balance." << endl;
            }
            else
            {
                balance = balance_amount;
            }
        }
        string GetName()
        {
            return name;
        }
        double GetBalance()
        {
            return balance;
        }
        long GetTaxID()
        {
            cout << taxID;
            return taxID;
        }
        void MakeDeposit(double deposit_amount)
        {
            if(deposit_amount <= 0)
            {
                cout << "Please enter a number greater than zero for deposit amount." << endl;
            }
            else
            {
                balance += deposit_amount;
            }            
        }
        virtual void Display()
        {
            printf("Account Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", name, GetTaxID(), GetBalance());
        }
};

int main()
{
    //char userInput[50];
    string input_name;
    double input_balance;
    long int input_tax_id;
    cout << "Account name? ";
    getline(cin, input_name);
    cout << "Starting balance? ";
    cin >> input_balance;
    cout << "9 digit tax id? ";
    cin >> input_tax_id;
    account a(input_name, input_tax_id, input_balance);
    a.Display();

    // if(err_msg)
    // {
    //     cout << err_msg;
    // }
    return 0;
}