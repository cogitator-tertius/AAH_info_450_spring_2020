#include<string>
#include<iostream>
using namespace std;
//CreditCard class functions
class creditCard : public account{
    private:
        long int cardnumber;
        string last10charges[10];
        int credit_card_buffer_size = 10;
    public:
        creditCard();
        creditCard(string input_name, long int input_tax_id, double input_starting_balance);
        void DoCharge(string name, double amount);
        void MakePayment(double amount);
        void Display();
};