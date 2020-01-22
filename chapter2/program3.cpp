// This program converts gallons to liters.


#include <iostream>
using namespace std;

int main()
{
    int gallons;
    int liters;

    cout << "Enter the number of gallons: ";
    cin >> gallons; // get input from user - hopefully it is int :P

    liters = gallons * 4; // convert gallons to liters
    cout << "Liters: " << liters;

    return 0;
}