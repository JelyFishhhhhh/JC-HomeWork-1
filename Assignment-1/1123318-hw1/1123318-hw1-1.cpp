#include <iostream>
using namespace std;

int main()
{
   int number;

   cout << "Enter a positive integer: ";
   cin >> number;
   
   if(number% 2){
      cout << "The integer " << number << " is odd.\n";
      return 0;
   }

   cout << "The integer " << number << " is even.\n";
   return 0;
}