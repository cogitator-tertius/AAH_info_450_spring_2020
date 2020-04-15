/*
Write a program that generates a list of 1,000 random integers and writes them to a file.

Each integers, n, must match: -10000 < n < 10000

Use the rand function: rand()

Your program should require no user input, and should not print anything to the stdout (no cout, no printf)

Your program must write to a file called "randoms.txt"

Each line must only contain an integer and a newline (endl)
*/

#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;

void listGenerator(int list_length, vector<int> *number_list);

int main() 
{
    int list_length = 1000;
    vector<int> number_list;

    number_list.clear();
    listGenerator(list_length, &number_list);

    ofstream output_stream("randoms.txt");
    if(!output_stream)
    {
        cout << "Error opening file." << endl;
        return 1;
    }else
    {
        int i;
        for(i =0; i < list_length; i++)
        {
            output_stream << number_list[i] << endl;
        }
    }

    return 0;
}

void listGenerator(int list_length, vector<int> *number_list)
{
    int i;
    int random_value;
    for(i = 0; i < list_length; i++)
    {
        random_value = rand () % 20000 - 10000;
        number_list->push_back(random_value);
        //if(i % 20 == 0){cout << random_value << " " << i << endl;} 
    }
}