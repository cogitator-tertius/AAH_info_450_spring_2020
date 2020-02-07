#include<iostream>
using namespace std;

int main()
{
    char inputString[100];

    cout << "Enter a name:" << endl;

    cin.getline(inputString, 100);

    for(int i = 0; i < 100; i++)
    {
        if(inputString[i] == '\0'){
            cout << "Your name has " << i  << " characters." << endl;
            break;
        }
    }
    return 0;
}