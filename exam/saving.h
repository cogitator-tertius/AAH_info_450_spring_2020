#include<string>
#include<iostream>
using namespace std;
//Savings class functions
class savings : public account{
    private:
        int saving_buffer_size = 10;
    public:
    savings();
    savings(string input_name, long int input_tax_id, double input_starting_balance);
    void DoWithDraw(double withdraw_amount);
    void Display();
};
