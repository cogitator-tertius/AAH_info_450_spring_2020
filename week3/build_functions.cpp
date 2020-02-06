#include <iostream>
using namespace std;

char  get_user_input();
void to_upper_case(char &letter);

int main(){
  char user_input_letter;
  cout << "Type in a letter grade, lowercase or uppercase." << endl; 
  if ('0' != (user_input_letter = get_user_input())){
    to_upper_case(user_input_letter);
    switch (user_input_letter){
      case 'A': cout << "Super Great job on an A!" << endl;break;
      case 'B': cout << "Great job on a B!" << endl;break;
      case 'C': cout << "Good job on a C!" << endl;break;
      case 'D': cout << "Keep at it, you can get there." << endl;break;
      case 'F': cout << "F is for #fail" << endl;break;
      default : cout << "This is not a valid grade: " << user_input_letter << endl;
    }
  }
  // Pretty sure this should not print each time ;)
  cout << "You have entered 0.  Exiting." << endl; 
}
char  get_user_input(){
    // Get char from user, and give it back to, my dude, user_input_letter
   char inputChar;
   cin >> inputChar;
   return inputChar;
}
void to_upper_case(char &letter){
   // Static cast to int, subtract 32 to get capital letter, re-cast to char
   // as per ascii chart at: https://www.asciitable.xyz/
   int asciiCode;
   asciiCode = static_cast<int> (letter) - 32;
   letter = static_cast<char> (asciiCode);
}