#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    int userInput[10];
    double mean;
    double meanOfSquares;
    double stdDeviation;
    int sumOfInputs = 0;
    int sumOfSquares = 0;

    cout << "Enter 10 whole numbers to calculate the mean and standard deviation." << endl;

    // Get ten numbers from the user, using counter as index.
    for(int i = 0; i < 10; i++)
    {
        cout << "Enter the number for index " << i << ": ";
        cin >> userInput[i];
        
        // Add each number to the sum of input numbers as we go along.
        sumOfInputs += userInput[i];
        
        // Once the last number is entered find the average and then start
        // standard deviation calculations.
        if(i == 9)
        {
            mean = sumOfInputs / (i + 1);
            
            // Use a different counter variable here to avoid bad behavior.
            for(int x = 0; x < 10; x++)
            {
                /* Loop back through the array, subtracting the average from
                each number and squaring the result before adding it to the
                sum of squared differences. */
                sumOfSquares += pow((userInput[x] - mean), 2);

                // Once the sum of squares has been calculated, find the average
                // and then take the square root to find the standard deviation!
                if(x == 9)
                {
                    meanOfSquares = sumOfSquares / (x + 1);
                    stdDeviation = sqrt(meanOfSquares);
                }
            }
        }
    }
    cout << "Results, " << mean << " , " << stdDeviation;
    return 0;
}