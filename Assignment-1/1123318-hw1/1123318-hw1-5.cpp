#include <iostream>
using namespace std;

int main()
{
   int year;
   cout << "Enter a year ( 1583-3000 ): ";
   cin >> year;

   if(((!(year% 4))&& (year% 100))|| (!(year% 400))){
      cout << "Year " << year << " is a leap year.\n";
      return 0;
   }

   cout << "Year " << year << " is a common year.\n";
   return 0;
}