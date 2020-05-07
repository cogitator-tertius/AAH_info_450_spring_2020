#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

string reverse(string *s1);

int main()
{
    string userInput;
    bool mainLoop = true;

    cout << "This program accepts a string and returns it reversed from front to back." << endl;
    cout << "It will repeat until the user presses enter on an empty line." << endl;

    // Accept input string from user until an empty string is provided.
    while(mainLoop == true)
    {
        cout << "Please enter a string to be reversed: ";
        getline(cin, userInput);
        if(userInput == "\0")
            {
                mainLoop = false;
                continue;
            }
        reverse(&userInput);
        cout << userInput << endl;
    }
    return 0;
}

//Not really sure why this function needs to return a string since we are working with pointers
//and manipulating the string directly but... ¯\_(ツ)_/¯
string reverse(string *s1)
{
    string temp;
    // Get length of string provided by user
    int length = s1->length();
    for(int i = 0; i < length; i++)
    {
        //Set temporary string to last non-null character in string
        temp = s1->back();
        //Insert last character in string at index i
        s1->insert(i, temp);
        //Delete last character of string after it has been inserted
        s1->pop_back();
    }
    return *s1;
}