// How much shorter would this be in Python? That would be an interesting math problem to model!
#include<iostream>
#include<string>
#include"account.h"
#include"checking.h"
#include"creditcard.h"
#include"saving.h" 
using namespace std;


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
    //checkingaccount.Display();

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
    //savingaccount.Display();

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
    //creditaccount.Display();

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
                //if(userStringInput.empty()){getline(cin,userStringInput); cout << userStringInput;}
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
                cout << "You have selected exit. ";
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