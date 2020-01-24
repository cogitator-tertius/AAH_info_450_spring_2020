#include <iostream>
using namespace std;

int main ()
{
    int a = 5;
    int b = 19;

    int iResult = b/a;
    cout << "iResult: " << iResult << endl;

    double dResult = b/a;
    cout << "dResult: " << dResult << endl;

    double dResult2 = (double) b/a;
    cout << "dResult2: " << dResult2 << endl;

    return 0;
}