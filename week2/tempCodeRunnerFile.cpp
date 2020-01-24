/* I think this is the best way to check for primes
    that I can come up with that doesn't require a
    more hardcore math excursion. Input a number and
    see if it is a prime or not! Obviously integers
    only. Use caution and expect a really big number
    to take a really long time... */

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int input;
    bool isPrimeNumber = true;
    int rootOfInput;
    //const int timesSix = 6;
    
    cout << "Enter an integer to see if it is a prime number: ";
    cin >> input;

    if(input%2 == 0 || input%3 == 0)
        {
        isPrimeNumber = false;
        }
    else
        {
        rootOfInput = sqrt(input);
        cout << "rootOfInput: " << rootOfInput << endl;
        system("pause");
        int i;
        //int iMultiplied;
        for(i = 1; i <= rootOfInput; i++)
            {

            int primeChkA = 6 * i + 1;
            int primeChkB = 6 * i - 1;
            cout << "PrimeChkA: " << primeChkA << " PrimeChkB: " << primeChkB << endl;
            system("pause");
            
            if(rootOfInput%(6*i + 1) == 0 || rootOfInput%(6*i - 1) == 0)
                {
                isPrimeNumber = false;
                }
            }
        }
    if(isPrimeNumber == false)
    {
        cout << "The number you entered is NOT a prime number." << endl;
    }
    else
    {
        cout << "The number you have entered is almost certainly a prime number..." << endl;
    }

    return 0;
}