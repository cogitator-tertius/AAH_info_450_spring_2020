#include <iostream>
using namespace std;

double calculateCircumference(double radius);
const double pi = 3.14159265358979323846;

int main()
{

double userInput;
double result;

cout << "Enter the radius of a circle to calculate the circumference: ";
cin >> userInput;

result = calculateCircumference(userInput);

cout << "The circumference of the circle is " << result << ".";

return 0;
}

double calculateCircumference(double radius)
{
    double circumference;
    circumference = pi * (2 *radius);
    return circumference; 
}