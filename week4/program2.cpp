// Write a program that inputs the names of the students in the class (to a max of 30 names)

// Store them in a 2-dimensional array

// Then outputs the class list to the console when the user enters an empty string (by pressing enter)
#include<iostream>
#include<stdio.h>
using namespace std;


int main()
{
    char studentNameArray[30][100];
    //char userInput[100];
    int numberOfEntries = 0;
    int maximumNameCount = 30;
    int i = 0;

    cout << "Enter student names to store (max 30). Leave entry blank to print all stored names in order." << endl;

    // Allow the user to enter up to thirty names with a max length of 100 chars (99 if you count null character).
    for(i = 0; i < maximumNameCount; i++)
    {
        cout << "Please enter student for index " << i << ": ";
        cin.getline(studentNameArray[i], 100);
        
        // If there is nothing in any given entry string, move on to printing names again.
        if(studentNameArray[i][0]== '\0')
        {
            break;
        }        
    }

    // Keep track of how many names have been entered in case user enters less than 30.
    numberOfEntries = i;

    for(i = 0; i < numberOfEntries; i++)
    {
        cout << "studentNameArray[" << i << "] = " << studentNameArray[i] << endl;
    }
    return 0;
}

