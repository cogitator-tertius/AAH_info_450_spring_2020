#include<string>
#include<iostream>
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
        account(string account_name, long tax_id, double starting_balance)
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
        void SetTaxID(long tax_id)
        {
            int length = 0;
            long n = tax_id;
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
            printf("Account Name: %s\nTax ID: %d\nAvailable Balance: $%.2f\n", name, taxID, balance);
        }
};