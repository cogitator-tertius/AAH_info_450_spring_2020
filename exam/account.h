#include<string>
#include<iostream>
using namespace std;
// Base class
class account 
{
    private:
        string name;
        int taxID;
        double balance;
        //bool valid_input;
        int transaction_buffer_size=10;
    protected:
        int numberDeposits = 0;
        int numberWithdraws = 0;
        double transaction_record[10];
    public:
        account();
        account(string input_name, long int input_tax_id, double input_starting_balance);
        void SetName(string input_name);
        void SetTaxID(long int input_tax_id);
        void SetBalance(double input_balance);
        string GetName();
        double GetBalance();
        long int GetTaxID();
        void MakeDeposit(double deposit_amount);
        virtual void Display();
};
