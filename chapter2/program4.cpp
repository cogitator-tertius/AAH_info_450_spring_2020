/* This program converts gallons to liters using
    floating point numbers instead of intergers. */

    #include <iostream>
    using namespace std;

    int main()
    {
        double gallons;
        double liters;

        cout << "Enter number of gallons: ";
        cin >> gallons; // get input from user

        liters = gallons * 3.7854; // perform unit conversion

        cout << "Liters: " << liters;

        cin;

        return 0;
    }