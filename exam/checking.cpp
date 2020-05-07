#include"account.h"
#include"checking.h"

    checking::checking()
    {
        // No params, per spec. Should probably set some defaults for this stuff - never hurts
        // to have a plan for obvious scenarios!
    }

    checking::checking(string input_name, long int input_tax_id, double input_starting_balance)
    {
            SetName(input_name);
            SetTaxID(input_tax_id);
            SetBalance(input_starting_balance);
            numberDeposits = 1;
            numberWithdraws = 0;
    }
    void checking::WriteCheck(int check_number, double check_amount)
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
    void checking::Display()
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