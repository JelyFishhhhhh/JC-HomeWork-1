#include <iostream>
using namespace std; 

int main()
{
   int number;

   cout << "Enter a 5-digit positive integer: ";
   cin >> number;

   if((number/ 10000== number% 10)&& ((number/ 1000)% 10== (number% 100)/ 10)){
      cout << number << " is a palindrome!!!\n";
      return 0;
   }
   
   cout << number << " is not a palindrome!!!\n";
   return 0;
}