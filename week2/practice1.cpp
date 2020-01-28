#include <iostream>
using namespace std;

int main()
{
    int input;
    int squared;

    cout << "This program accepts a positive integer and computes the square." << endl;
    while(true) // Loops until user breaks it by entering 0
    {
        cout << "Please enter a positive integer: ";
        cin >> input;

        if(input == 0)
        {
            break; // this is how to quit the loop
        }
        else if(input < 0)
        {
            cout << "You have entered a negative value. This program accepts positive values only!" << endl;
        }
        else
        {
            squared = input * input;
            cout << "The square of the value you entered is " << squared << "." << endl;
        }
        
        cout << "Enter another value to square, or enter 0 to quit." << endl;
    }

    system("pause");
    return 0;
}