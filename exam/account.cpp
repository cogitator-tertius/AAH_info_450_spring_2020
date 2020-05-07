#include"account.h"

        account::account()
        {
            // No params, per spec. Should probably set some defaults for this stuff - never hurts
            // to have a plan for obvious scenarios!
        }
        account::account(string input_name, long int input_tax_id, double input_starting_balance)
        {
            // I had an absolute nightmare getting this to work with a pointer, and I'll be damned if I know why.
            // ...
            // I was going to delete this comment, but I wanted to leave it for posterity's sake.
            // The problem was that, because using string type and not character arrays, my choice of printf()
            // for the fancy formatting really screwed me over. Even though one of the specifiers for arguments
            // in the documentation for printf (%s) is for a string of characters, they ain't the same thing.
            // So I probably spent 4 or 5 days thinking about and tinkering with this to make it work... which
            // it did. Except that I was using printf the wrong way.
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits++;
            numberWithdraws;
        }
        // I REALLY think that checking for errors in the name input should happen in it's own function... but
        // first things first.
        void account::SetName(string input_name)
        {
            // valid_input = ValidateTextInput(account_name);
            if(input_name.empty())
            {
                // Recursion makes sense here, right?
                cout << "Please enter a valid name for the account: ";
                getline(cin, input_name);
                SetName(input_name);
            }
            else
            {
                name = input_name;
            }
        }
        void account::SetTaxID(long int input_tax_id)
        {
            // Just checking for length with division. Could bear a re-visit to match pattern to SSNs:
            // AAA-BB-CCCC
            // No letter group can be all zeroes, AAA must not be over 740.
            // ...
            // A friend once told me "When you have a problem and you try to solve it with regular expressions,
            // then you have two problems."
            int length = 0;
            long int n = input_tax_id;
            while(n !=0)
            {
                n = n/10;
                length++;
            }
            if(length != 9)
            {
                //long int input_tax_id;
                cout << "Please enter a valid 9-digit tax ID number: ";
                cin >> input_tax_id;
                SetTaxID(input_tax_id);
            }
            else
            {
                taxID = input_tax_id;
            }
        }
        void account::SetBalance(double input_balance)
        {
            if(input_balance < 0 && numberDeposits == 0)
            {
                cout << "Please enter a positive amount for the initial account balance: $";
                cin >> input_balance;
                SetBalance(input_balance);
            }
            else
            {
                balance = input_balance;
            }
        }
        string account::GetName()
        {
            return name;
        }
        double account::GetBalance()
        {
            return balance;
        }
        long int account::GetTaxID()
        {
            return taxID;
        }
        // Need to change this so that the initial deposit goes into the transaction record.
        void account::MakeDeposit(double deposit_amount)
        {
            if(deposit_amount <= 0)
            {
                cout << "Please enter a number greater than zero for deposit amount: ";
                cin >> deposit_amount;
                MakeDeposit(deposit_amount);
            }
            else
            {
                balance += deposit_amount;
                numberDeposits++;
            }            
        }
        void account::Display()
        {
            // If you saw my comments about printf, had to use the c_str() function in the string library to get it to play nice.
            // What kind of ding dong creates a printf() that can't take strings! C++ really showing it's age in some ways.
            // I did find sprintf() after the fact, but, low priority as it works for now!
            // This would have been much easier in Python ;)
            printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", GetName().c_str(), GetTaxID(), GetBalance());
        }
