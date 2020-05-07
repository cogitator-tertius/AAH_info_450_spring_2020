#include<string>
#include<iostream>
using namespace std;
//Checking class functions
class checking : public account
{
    private:
        int last10checks[10];
        int check_buffer_size=10;
    public:
    checking();
    checking(string input_name, long int input_tax_id, double input_starting_balance);
    void WriteCheck(int check_number, double check_amount);
    void Display();
};