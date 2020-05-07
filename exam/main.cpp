// How much shorter would this be in Python? That would be an interesting math problem to model!

#include<iostream>
#include<string>
using namespace std;

// Base class functions
void SetName(string input_name);
void SetTaxID(long int input_tax_id);
void SetBalance(double input_balance);
string GetName();
double GetBalance();
long int GetTaxID();
void MakeDeposit(double deposit_amount);
void Display();

//Checking class functions
void WriteCheck(int check_number, double check_amount);

//Savings class functions
void DoWithDraw(double withdraw_amount);

//CreditCard class functions
void DoCharge(string name, double amount);
void MakePayment(double amount);

class account {
    private:
        string name;
        int taxID;
        double balance;
        //bool valid_input;
        int transaction_buffer_size = 10;
    protected:
        int numberDeposits = 0;
        int numberWithdraws = 0;
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
            numberDeposits++;
            numberWithdraws;
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

class checking : public account{
    private:
        int last10checks[10];

        // I suppose this is outside the specs, but it makes it easier to modify the logic
        // to put this in a variable rather than hard code it.
        int check_buffer_size = 10;
    public:
    checking()
    {
        // No params, per spec. Should probably set some defaults for this stuff - never hurts
        // to have a plan for obvious scenarios!
    }

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
        // Need to add handling for negative check numbers?
        if(check_amount <= 0)
        {
            cout << "Check amount must be greater than $0. \nPlease enter the check amount: $";
            cin >> check_amount;
            WriteCheck(check_number, check_amount);
        }
        else
        {   // If the transaction arrays are not full, add one to it and increment the number of withdraws
            // If the array with checknumbers is full, shift each check number to the previous index in the
            // array, then put the new transaction in the last index (in this case, 9).
            if(numberWithdraws < check_buffer_size)
            {
                last10checks[numberWithdraws] = check_number;
                transaction_record[numberWithdraws] = check_amount;
            }
            else
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
    }
    void Display()
    {
        // Print the basic account info... I'm still salty about printf and string objects >:(
        printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Balance: $%.2f\n", GetName().c_str(), GetTaxID(), GetBalance());

        // Print check #'s and amounts, stop early if there are less than 10 checks in register
        for(int i = 0; i < check_buffer_size; i++)
        {
            if(numberWithdraws == i)
            {
                cout << endl;
                break;
            }
            printf("Check #: %d   Amount: $%.2f \n", last10checks[i], transaction_record[i]);
        }

        // Print some info about the total number of transactions, so we can actually use the number of deposits
        // for something!
        printf("Total transactions: %d Deposits: %d Withdrawals: %d \n", numberDeposits + numberWithdraws, numberDeposits, numberWithdraws);
    }
};
class savings : public account{
    // Originally I was going to have the Display() method print out the the activity in an
    // accounting style T-chart, and transact type would determine which side the entry was printed
    // on. Requirement was removed from spec though maybe I'll take another pass at it later...
    private:
        //int last10transactTypes[10];
        int saving_buffer_size = 10;
    public:
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

        //print withdraws, stop early if there are less than 10 withdraws
        for(int i = 0; i < saving_buffer_size; i++)
        {
            if(numberWithdraws == i)
            {
                cout << endl;
                break;
            }
            printf("Withdrawal: ($%.2f) \n", transaction_record[i]);
        }
        // Print some info about the total number of transactions
        printf("Total transactions: %d Deposits: %d Withdraws: %d \n", numberDeposits + numberWithdraws, numberDeposits, numberWithdraws);
    }
};
class creditCard : public account{
    private:
        long int cardnumber;
        string last10charges[10];
        int credit_card_buffer_size = 10;
    public:
        creditCard()
        {
            // No params, per spec. Should probably set some defaults for this stuff - never hurts
            // to have a plan for obvious scenarios!
        }
        creditCard(string input_name, long int input_tax_id, double input_starting_balance)
        {

            // This is not behaving well at the moment, and I don't have a ton of time.
            // The loop creates a 16-digit pseudorandom card number using srand and
            // rand. srand gets the value of the counter so that the card has a different
            // set of 4umbers in each group.
            // long long int temp = 0;
            // for(int i = 1; i < 5; i++)
            // {
            //     srand(i);
            //     temp *= 10000;
            //     temp += rand() % 5000 + 4000;
            //     cout << "CC: " << temp << endl; 
            // }
            cardnumber = 42949672;
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits = 1;
            numberWithdraws = 0;
        }
        void DoCharge(string charge_name, double charge_amount)
        {
            // Will come back to this, probably a better way to handle it. if with a ternary?
            if(charge_name.empty())
            {
                cout << "There must be a name provided with the charge.\nPlease enter a valid name: ";
                getline(cin, charge_name);
                DoCharge(charge_name, charge_amount);
            }
            else if(charge_amount <= 0)
            {
                cout << "Credit card charge amount must be greater than $0.\nPlease enter a valid charge amount: $";
                cin >> charge_amount;
                DoCharge(charge_name, charge_amount);
            }
            else
            {
                if(numberWithdraws < credit_card_buffer_size)
                {
                    last10charges[numberWithdraws] = charge_name;
                    transaction_record[numberWithdraws] = charge_amount;
                }
                else
                {
                    for(int i = 1; i < credit_card_buffer_size; i++)
                    {
                        last10charges[i - 1] = last10charges[i];
                        transaction_record[i - 1] = transaction_record[i]; 
                    }
                    last10charges[credit_card_buffer_size - 1] = charge_name;
                    transaction_record[credit_card_buffer_size - 1] = charge_amount;
                }
                
            }
            // The available credit is considered as available balance in the account.
            // Charges are equivalent to withdraws in this use case.
            SetBalance((GetBalance() - charge_amount));
            numberWithdraws++;
        }
        void MakePayment(double payment_amount)
        {
            // Should this show up as a transaction in the buffer?
            // Implementation depends on time available.
            MakeDeposit(payment_amount);
        }
        void Display()
        {
            // Print basic account info. Should be it's own function IMHO.
            printf("\nAccount Name: %s\nTax ID: %ld\nAvailable Credit: $%.2f\nCard #: %ld\n\nCharges:\n", GetName().c_str(), GetTaxID(), GetBalance(),cardnumber);
            // Print numbered list of charges and amounts.
            for(int i = 0; i < credit_card_buffer_size; i++)
            {
                // slightly different implementation, a little shorter
                if(numberWithdraws == i){break;}
                printf("%d. %s Amount: $%.2f\n", i+1, last10charges[i].c_str(), transaction_record[i]);
            }
            cout << endl;
            // Print info about total number and type of transactions.
            printf("Total transactions: %d Payments: %d Charges: %d \n", numberDeposits + numberWithdraws, numberDeposits, numberWithdraws);
        }
};

int main(){
    // Not sure you wanted to be able to enter the values, but I 
    // started that way before writing a few simple tests.
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

    // War... war never changes. Just like the starting balance...
    const double _startingBalance = 100;
    bool testsEnabled = false; //enable to run tests
    int userMenuSelection;
    double userDoubleInput;
    string userStringInput;
    int userIntegerInput;

    // set up checking account
    string checkingName = "Mike Check";
    long int checkingTaxId = 654874123;
    account *account1;
    checking checkingaccount(checkingName, checkingTaxId, _startingBalance);
    account1 = &checkingaccount;
    checkingaccount.Display();

    if(testsEnabled){
        checkingaccount.MakeDeposit(100.1);
        checkingaccount.Display();
        for(int i = -1; i < 12; i++)
        {
            checkingaccount.WriteCheck((1000 + i), (i));
            cout << "Writing check #" << i << "... current checking balance is $" << checkingaccount.GetBalance() << endl;
        }
        checkingaccount.Display();
    }

    // set up savings account
    string savingsName = "Best for last";
    long int savingsTaxId = 951753684;
    account *account2;
    savings savingaccount(savingsName, savingsTaxId, _startingBalance);
    account2 = &savingaccount;
    savingaccount.Display();

    if(testsEnabled){
        savingaccount.MakeDeposit(100.01);
        savingaccount.Display();
        for(int i = -1; i < 12; i++)
        {
            savingaccount.DoWithDraw(i + .25);
            cout << "Withdrawal #" << i << "... current savings balance is $" << savingaccount.GetBalance() << endl;
        }
    savingaccount.Display();
    }

    // set up credit card account
    string creditCardName = "Just Charge It";
    long int creditCardTaxId = 852963741;
    account *account3;
    creditCard creditaccount(creditCardName, creditCardTaxId, _startingBalance);
    account3 = &creditaccount;
    creditaccount.Display();

    if(testsEnabled){
        creditaccount.DoCharge("Banana hammock",50);
        creditaccount.Display();
        creditaccount.MakePayment(69);
        creditaccount.Display();
    }

    while(userMenuSelection != 0)
    {
        // print the header with balance info.
        printf("Checking balance: $%.2f Savings balance: $%.2f Credit Card Balance: $%.2f\n", checkingaccount.GetBalance(), savingaccount.GetBalance(), creditaccount.GetBalance());
        cout << " 1. Savings Deposit" << endl;
        cout << " 2. Savings Withdrawal" << endl;
        cout << " 3. Checking Deposit" << endl;
        cout << " 4. Write A Check" << endl;
        cout << " 5. Credit Card Payment" << endl;
        cout << " 6. Make A Charge" << endl;
        cout << " 7. Display Savings" << endl;
        cout << " 8. Display Checking" << endl; 
        cout << " 9. Display Credit Card" << endl; 
        cout << " 0. Exit" << endl;
        cout << "\n Please enter your selection: ";
        cin >> userMenuSelection;

        switch(userMenuSelection)
        {
            case 1:
                cout << "Enter the deposit amount: $";
                cin >> userDoubleInput;
                savingaccount.MakeDeposit(userDoubleInput);
                break;
            case 2:
                cout << "Enter the withdrawal amount: $";
                cin >> userDoubleInput;
                savingaccount.DoWithDraw(userDoubleInput);
                break;
            case 3:
                cout << "Enter the deposit amount: $";
                cin >> userDoubleInput;
                checkingaccount.MakeDeposit(userDoubleInput);
                break;
            case 4:
                cout << "Enter the check number: ";
                cin >> userIntegerInput;
                cout << "Enter the check amount: $";
                cin >> userDoubleInput;
                checkingaccount.WriteCheck(userIntegerInput, userDoubleInput);
                break;
            case 5:
                cout << "Enter the payment amount: $";
                cin >> userDoubleInput;
                creditaccount.MakePayment(userDoubleInput);
                break;
            case 6:
                cout << "Enter the charge amount: $";
                cin >> userDoubleInput;
                userStringInput.clear();
                cout << "Enter a name for the charge: ";
                // for some reason it keeps skipping this input - probably since the object already
                // exists. For now, here's janky fix...
                //if(userStringInput.empty()){(cin,userStringInput); cout << userStringInput;}
                cin >> userStringInput;
                creditaccount.DoCharge(userStringInput, userDoubleInput);
                break;
            case 7:
                cout << "--- Savings Account ---";
                savingaccount.Display();
                cout << "\nPress any key to continue...";
                system("pause");
                break;
            case 8:
                cout << "--- Checking Account ---";
                checkingaccount.Display();
                system("pause");
                break;
            case 9:
                cout << "--- Credit Card Account ---";
                creditaccount.Display();
                system("pause");
                break;
            case 0:
                cout << "You have selected exit.";
                system("pause");
                break;
            default:
                cout << "Invalid selection. Please try again.";
                break;                
        }                                         
    }
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