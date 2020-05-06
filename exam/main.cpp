// How much shorter would this be in Python? That would be an interesting math problem to model!

#include<iostream>
#include<string>
using namespace std;

// Base class functions
void SetName(string input_name);
void SetTaxID(long int input_tax_id);
void SetBalance(double input_starting_balance);
string GetName();
double GetBalance();
long int GetTaxID();
void MakeDeposit(double deposit_amount);
void Display();

void WriteCheck(int check_number, double check_amount);

void DoWithDraw(double withdraw_amount);


class account {
    private:
        string name;
        int taxID;
        double balance;
        //bool valid_input;
        int transaction_buffer_size = 10;
    protected:
        int numberDeposits;
        int numberWithdraws;
        double transaction_record[10];
    public:
        account()
        {
            // No params, per spec. Should probably set some defaults for this stuff - never hurts
            // to have a plan for obvious scenarios!
        }
        account(string input_name, long int input_tax_id, double input_starting_balance)
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
            numberDeposits = 1;
            numberWithdraws = 0;
        }
        // I REALLY think that checking for errors in the name input should happen in it's own function... but
        // first things first.
        void SetName(string input_name)
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
        void SetTaxID(long int input_tax_id)
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
        void SetBalance(double input_balance)
        {
            if(input_balance < 0)
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
        string GetName()
        {
            return name;
        }
        double GetBalance()
        {
            return balance;
        }
        long int GetTaxID()
        {
            return taxID;
        }
        // Need to change this so that the initial deposit goes into the transaction record.
        void MakeDeposit(double deposit_amount)
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
        virtual void Display()
        {
            // If you saw my comments about printf, had to use the c_str() function in the string library to get it to play nice.
            // What kind of ding dong creates a printf() that can't take strings! C++ really showing it's age in some ways.
            // I did find sprintf() after the fact, but, low priority as it works for now!
            // This would have been much easier in Python ;)
            printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", GetName().c_str(), GetTaxID(), GetBalance());
        }
};

class checking : private account{
    private:
        int last10checks[10];

        // I suppose this is outside the specs, but it makes it easier to modify the logic
        // to put this in a variable rather than hard code it.
        int check_buffer_size = 10;
    checking()
    {
        // No params, per spec. Should probably set some defaults for this stuff - never hurts
        // to have a plan for obvious scenarios!
    }
    // This might work? Revisit when it's not 2:30 am, bruh.
    checking(string input_name, long int input_tax_id, double input_starting_balance)
    {
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits = 1;
            numberWithdraws = 0;
    }
    void WriteCheck(int check_number, double check_amount)
    {
        // Need to add handling for negative check amounts.

        // If the transaction arrays are not full, add one to it and increment the number of withdraws
        // If the array with checknumbers is full, shift each check number to the previous index in the
        // array, then put the new transaction in the last index (in this case, 9).
        if(numberWithdraws < check_buffer_size)
        {
            last10checks[numberWithdraws] = check_number;
            transaction_record[numberWithdraws] = check_amount;
        }
        // Will try without the array.size() in Savings, if it works there, I'll bring it up here.
        else// if(last10checks.length() == check_buffer_size)
        {
            // Move each record in the buffer to the preceding index, then put last
            // transaction into index 9.
            for(int i = 1; i < check_buffer_size; i++)
            {
                last10checks[i - 1] = last10checks[i];
                transaction_record[i - 1] = transaction_record[i];
            }
            last10checks[check_buffer_size - 1] = check_number;
            transaction_record[check_buffer_size -1] = check_amount;
        }
        // Almost forgot to subtract the withdraw from the balance!
        // double current_balance = GetBalance(); don't really need this
        SetBalance((GetBalance() - check_amount));
        // Increment the number of withdraws no matter which condition is true.
        numberWithdraws++;
    }
    void Display()
    {
        // Print the basic account info... I'm still salty about printf and string objects >:(
        printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", GetName().c_str(), GetTaxID(), GetBalance());

        // This should print a list of each check # and transaction in the buffer, up until
        // the last index OR an empty index in the array.
        for(int i = 0; i < check_buffer_size; i++)
        {
            if(!last10checks[i])
            {
                cout << endl;
                break;
            }
            printf("Check #: %d   Amount: $%.2f \n", last10checks[i], transaction_record[i]);
        }

        // Print some info about the total number of transactions, so we can actually use the number of deposits
        // for something!
        printf("Total transactions: %d Deposits: %d Withdraws: %d \n", numberDeposits + numberWithdraws, numberDeposits, numberWithdraws);
    }
};
class savings : public account{
    // Originally I was going to have the Display() method print out the the activity in an
    // accounting style T-chart, and transact type would determine which side the entry was printed
    // on. Requirement was removed from spec though maybe I'll take another pass at it later...
    //private:
        //int last10transactTypes[10];
        int saving_buffer_size = 10;
    savings()
    {
        // No params, per spec. Should probably set some defaults for this stuff - never hurts
        // to have a plan for obvious scenarios!
    }
    savings(string input_name, long int input_tax_id, double input_starting_balance)
    {
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits = 1;
            numberWithdraws = 0;
    }
    void DoWithDraw(double withdraw_amount)
    {
        // You can't withdraw a negative amount or nothing...
        if(withdraw_amount <= 0)
        {
            cout << "Withdrawal amount must be greater than $0. \n Please enter the withdrawal amount: ";
            cin >> withdraw_amount;
            DoWithDraw(withdraw_amount);
        }
        else
        {
            if(numberWithdraws < saving_buffer_size)
            {
                transaction_record[numberWithdraws] = withdraw_amount;
            }
            // Gonna test a more straightforward way to handle the buffer
            else
            {
                for(int i = 1; i < saving_buffer_size; i++)
                {
                    transaction_record[i - 1] = transaction_record[i];
                }
                transaction_record[saving_buffer_size - 1] = withdraw_amount;
            }
            
            SetBalance(GetBalance() - withdraw_amount);
            numberWithdraws++;
        }
        
    }
    void Display()
    {
        printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", GetName().c_str(), GetTaxID(), GetBalance());

        // This should print a list of each withdrawal in the buffer, up until
        // the last index OR an empty index in the array.
        for(int i = 0; i < saving_buffer_size; i++)
        {
            if(!transaction_record[i])
            {
                cout << endl;
                break;
            }
            printf("Withdrawal amount: ($%.2f) \n", transaction_record[i]);
        }

        // Print some info about the total number of transactions, so we can actually use the number of deposits
        // for something!
        printf("Total transactions: %d Deposits: %d Withdraws: %d \n", numberDeposits + numberWithdraws, numberDeposits, numberWithdraws);
    }
};

int main(){
    // Not sure if you wanted to be able to enter the values, but it was good practice for handling input!
    /*string input_name;
    double input_balance;
    long int input_tax_id;
    cout << "Account name? ";
    getline(cin, input_name);
    cout << "Starting balance? ";
    cin >> input_balance;
    cout << "9 digit tax id? ";
    cin >> input_tax_id;
    */
    // No need for the type cast here
    //input_tax_id = (long int)input_tax_id;
    string checkingName = "Checkmeout";
    long int checkingTaxId = 654874123;
    double startingBalance = 100;
    account *account1;
    checking checkingaccount(checkingName, checkingTaxId, startingBalance);
    account1 = &checkingaccount;
    cout << "Name: " << account1->GetName() << endl;
    account1->Display();
    account1->WriteCheck(1000, 25.25);
    account1->Display();

    /* Exception handling is a maybe but not a super high priority, need to finish logic first. Either way, users putting in
    weird input values is hardly exceptional behavior, so it should be handled elsewhere.
    try
    {
         code 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    */
    return 0;
}