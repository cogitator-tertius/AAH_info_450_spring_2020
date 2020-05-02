// Please implement the function, my_string_compare to mimic the cstring function, strcmp.
// Feel free to use: https://www.onlinegdb.com/online_c++_compiler  (OPEN IN A NEW TAB! )
// Watch the copy/paste.  Make sure I can read the code.  
// After you implement my_string_compare, this program should print:
// One  
// Two  
// Three  
#include <iostream>  
#include <cstring>  
using namespace std;  
int my_string_compare(char first[], char second[]);  
int main (){             
  char one[100] = "hi";    
  char two[100] = "there";     
  if (my_string_compare(one, two) < 0){       
    cout << "One" << endl;    
  }        
  strcpy(one, "hi");    
  strcpy(two, "hi");      
  if (my_string_compare(one, two) == 0){       
    cout << "Two" << endl;    
  }            

  strcpy(one, "there");    
  strcpy(two, "hi");     
  if (my_string_compare(one, two) > 0){       
    cout << "Three" << endl;    
  }        
  return 0;    
}    

int my_string_compare(char first[], char second[]){          
  //Use these for comparison purposes.
  int stringCompareResult = 0;
  int firstCharAsciiValue = 0;
  int secondCharAsciiValue = 0;
  
  //Iterate through each string until hitting the null character
  //and check to see if the characters match each other. If they don't
  //match return a value based on the comparison:
  // first > second = 1
  // first < second = -1
  //And if they match all the way up to the null character:
  // first == second = 0

  for(int i = 0; i < 100; i++)
  {
      // if we are at the null terminator for both strings then they match...
      if(first[i] == '\0' && second[i] == '\0')
      {
          stringCompareResult = 0;
          break;
      }
      //If the characters match, skip the rest and increment i by 1.
      if(first[i] == second[i])
      {
          continue;
      }
      //Cast chars to ascii int values
      firstCharAsciiValue = static_cast<int> (first[i]);
      secondCharAsciiValue = static_cast<int> (second[i]);
      
      //Compare ascii int values and set comparison result accordingly.
      if(firstCharAsciiValue > secondCharAsciiValue)
      {
          stringCompareResult = 1;
      }else if(firstCharAsciiValue < secondCharAsciiValue)
      {
          stringCompareResult = -1;
      }
      
      //We should only hit this break if the characters are not the same.
      break;
  }

  return stringCompareResult;    
}