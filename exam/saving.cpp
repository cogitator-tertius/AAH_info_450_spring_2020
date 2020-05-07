#include"account.h"
#include"saving.h"

    savings::savings()
    {
        // No params, per spec. Should probably set some defaults for this stuff - never hurts
        // to have a plan for obvious scenarios!
    }
    savings::savings(string input_name, long int input_tax_id, double input_starting_balance)
    {
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits = 1;
            numberWithdraws = 0;
    }
    void savings::DoWithDraw(double withdraw_amount)
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
    void savings::Display()
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
