/* I think this is the best way to check for primes
    that I can come up with that doesn't require a
    more hardcore math excursion. Input a number and
    see if it is a prime or not! Obviously integers
    only. Use caution and expect a really big number
    to take a really long time... */

#include <iostream>
using namespace std;

int main()
{
    int userInput;
    bool isPrimeNumber;
    int primeCandidate;

    do
    {
        isPrimeNumber = true; // We will test to see if it is NOT a prime
        
        cout << "Enter an integer to see if it is a prime number: "; // get user input
        cin >> userInput;
        if(userInput == 0){continue; } // if the user wants to quit, skip all this other junk

        primeCandidate =(int) userInput; // maybe overkill but...

        /* Easy prime check first, is it an even number?
            Is it an uneven multiple of 3?
        */
        if(primeCandidate%2 == 0 || primeCandidate%3 == 0)
            {
            isPrimeNumber = false;
            }
        else
            {
            /* Simple primality test implementation using trial division adapted
               from my mathematical structures textbook and wikipedia:
                a) to find a factor of a prime it is redundant to check past the
                root since the factors will repeat.
                
                ex - 144 = 12 x 12 = 6 x 24 = 3 x 48 = 2 x 72 = 72 x 2 = 48 x 3 = 24 x 6 = 12 x 12
                
                Initially I was using the math sqrt() function but I ran into
                trouble because modulus only works on integers. So instead I
                am checking for square root by raising the test integer to the
                2nd power.

                b) Primes after 3 take the form 6(x) +/- 1 with some exceptions

                ex - 5 7 11 13 17 19 23 25(not a prime) etc etc

                Since we know these two facts we can use multiples of 6 plus or minus 1
                up to the integer nearest to the root of a number to check whether it is
                a composite prime.

                Note: this program may be worth revisiting once we start working with arrays;
                storing an array of the first n primes would reduce need for computation in
                checking for composite numbers.
            */
            int i;

            for(i = 6; ((i -1) * (i - 1)) <= primeCandidate; i += 6) // this will catch 25 as a non-prime
                {
                // went ahead and split factors into their own variables to make things easier to read
                int primeChkA = i - 1;
                int primeChkB = i + 1;

                // The following two lines were for testing when I was having trouble with sqrt().
                //cout << "PrimeChkA: " << primeChkA << " PrimeChkB: " << primeChkB << endl;
                //system("pause");
                
                if(primeCandidate%(primeChkA) == 0 || primeCandidate%(primeChkB) == 0)
                    {
                    // modulus is still the easiest way, break to save a little time if we
                    // find a factor early instead of still running through the whole set
                    // of possible factors.
                    isPrimeNumber = false;
                    break;
                    }
                }
            }
        if(isPrimeNumber == false)
        {
            cout << "The number you entered is NOT a prime number." << endl;
        }
        else
        {
            cout << "The number you have entered is a PRIME number!" << endl;
        }

        cout << "You may enter another number to test, or enter 0 to exit." << endl;
    }while(userInput !=0);

    return 0;
}