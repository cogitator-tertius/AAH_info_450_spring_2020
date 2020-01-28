#include <iostream>
using namespace std;

int main()
{
    int input = 1;
    const int leapYearDivisor = 4;
    const int centuryDivisor = 100;
    const int quadricentennialDivisor = 400;
    bool isLeapYear = false;

    cout << "This program accepts a year and determines whether it is a leapyear or not." << endl;

    while (input != 0)
    {
        cout << "Please enter the year you would like to check: ";
        cin >> input;

        // If the user enters 0 as the year skip the rest of the loop.
        if(input == 0)
        {
            continue;
        }

        // Check if the year is divisible by 4
        if(input%leapYearDivisor == 0)
        {
            isLeapYear = true;
        }

        // Check if the year is divisible by 100 - potentially not a leap year unless also divisible by 400
        if(input%centuryDivisor == 0)
        {
            isLeapYear = false;
        }

        // Check if the year is divisible by 400
        if(input%quadricentennialDivisor == 0)
        {
            isLeapYear = true;
        }

        if(isLeapYear == true)
        {
            cout << "The year you have entered is a leap year!" << endl;
        }
        else
        {
            cout << "The year you have entered is not a leap year :(" << endl;
        }

        cout << "You may enter another year to test, or enter 0 to quit." << endl;
    }
    system("pause");
    return 0;

}