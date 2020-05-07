#include"account.h"
#include"creditcard.h"
        creditCard::creditCard()
        {
            // No params, per spec. Should probably set some defaults for this stuff - never hurts
            // to have a plan for obvious scenarios!
        }
        creditCard::creditCard(string input_name, long int input_tax_id, double input_starting_balance)
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
        void creditCard::DoCharge(string charge_name, double charge_amount)
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
        void creditCard::MakePayment(double payment_amount)
        {
            // Should this show up as a transaction in the buffer?
            // Implementation depends on time available.
            MakeDeposit(payment_amount);
        }
        void creditCard::Display()
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
