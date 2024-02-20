#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace::std;

char foods[ 13 ][ 48 ] = { "",
                           "Pork XiaoLongBao (12)",
                           "Steamed Vegetable and Ground Pork Dumplings (8)",
                           "Steamed Shrimp and Pork Dumplings (8)",
                           "Steamed Shrimp and Pork Shao Mai (12)",
                           "Steamed Vegetarian Mushroom Dumplings (8)",
                           "Pork Buns (5)",
                           "Vegetable and Ground Pork Buns (5)",
                           "Red Bean Buns (5)",
                           "Sesame Buns (5)",
                           "Taro Buns (5)",
                           "Vegetarian Mushroom Buns (5)",
                           "Golden Lava Buns (5)" };

int price[ 13 ] = { 0, 250, 208, 232, 444, 216,
                      250, 250, 225, 225, 250, 275, 250 };

struct Date
{
   int year;
   int month;
   int day;
};

struct Account
{
   char email[ 40 ]; // used as the account number
   char password[ 20 ];
   char name[ 12 ];
   char address[ 80 ];
   char phone[ 12 ];
   int cart[ 13 ]; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
   char orderNumber[ 12 ];
   char email[ 40 ];
   Date deliveryDate;
   Date arrivalDate;
   int quantity[ 13 ]; // quantity[i] is the quantity of food #i in the order
};

// load all accounts details from the file Accounts.dat
void loadAccounts( vector< Account > &accounts );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// add a new account to the file Accounts.dat
void registration( vector< Account > &accounts );

// return true if there exists an account with specified email
bool exists( char email[], const vector< Account > &accounts );

// login and call shopping
void login( vector< Account > &accounts );

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid( char email[], char password[], int &accountIndex, vector< Account > &accounts );

// add chosen Foods to the shopping cart
void shopping( Account &account );

//  choose cuisines and quantities, and put into shopping cart
void ourCuisine( Account &account );

// display shopping cart, then continue shopping, update cart or check
void shoppingCart( Account &account );

// return true if the shopping cart is empty
bool emptyCart( const Account &account );

// display the shopping cart in account
bool displayCart( const Account &account );

// update the shopping cart in account
void updateCart( Account &account );

// generate a Bill and reset account.cart
void check( Account &account );

// compute the current date
void compCurrentDate( Date &currentDate );

// open the file Orders.txt and call displayOrderDetails twice
void createOrder( const Account &account, const Order &order );

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails( ostream &os, const Account &account, const Order &order );

// save all elements in accounts to the file Accounts.dat
void saveAccounts( const vector< Account > &accounts );

int main()
{
   vector< Account > accounts; // account details for all accounts
   loadAccounts( accounts );

   cout << "Welcome to DintaiFung Shopping Mall!\n\n";
   srand( static_cast< int >( time( 0 ) ) );

   int choice;

   while( true )
   {
      cout << "1. Registration\n";
      cout << "2. Login\n";
      cout << "3. End\n";

      do cout << "\nEnter your choice: ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         registration( accounts );
         break;

      case 2:
         login( accounts );
         break;

      case 3:
         cout << "Thank you! Goodbye!\n\n";
         saveAccounts( accounts );
         system( "pause" );
         return 0;
      }
   }

   system( "pause" );
}

// load all accounts details from the file Accounts.dat
void loadAccounts( vector< Account > &accounts )
{
    ifstream inFile("Accounts.dat", ios::in | ios::binary);
    if (!inFile) {

        cout << "\nError: Accounts.dat cannot open.\n";
    }
    inFile.clear();
    inFile.seekg(0, ios::beg);
    Account buf;
    while (inFile >> buf.email) {

        inFile >> buf.password >> buf.name >> buf.address >> buf.phone;
        for (int i = 1; i < 13; i++) {

            inFile >> buf.cart[i];
        }
        accounts.push_back(buf);
    }
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin >> string;

   if( strlen( string ) == 0 )
      exit( 0 );

   for( size_t i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void registration( vector< Account > &accounts )
{
   Account newAccount;

   cout << "Email address (Account number): ";
   cin >> newAccount.email;

   if( exists( newAccount.email, accounts ) )
   {
      cout << "\nYou are already a member!\n\n";
      return;
   }

   cout << "Password: ";
   cin >> newAccount.password;

   cout << "Name: ";
   cin >> newAccount.name;

   cout << "Shipping address: ";
   cin >> newAccount.address;

   cout << "Contact phone number: ";
   cin >> newAccount.phone;

   for( int i = 1; i <= 12; i++ )
      newAccount.cart[ i ] = 0;

   accounts.push_back( newAccount );

   cout << "\nRegistration Completed!\n\n";
}

bool exists( char email[], const vector< Account > &accounts )
{
   for( size_t i = 0; i < accounts.size(); i++ )
      if( strcmp( email, accounts[ i ].email ) == 0 )
         return true;
   return false;
}

// login and call shopping
void login( vector< Account > &accounts )
{
   char email[ 40 ];
   char password[ 20 ];

   int accountIndex;
   while (true) {
       cout << "Email address (0 to end): ";
       cin >> email;
       if (email[1]=='\0' && email[0]=='0') {

           return;
       }
       cout << "Password: ";
       cin >> password;
       if (valid(email, password, accountIndex, accounts)) {

           break;
       }
   }

   shopping( accounts[ accountIndex ]);
}

bool valid( char email[], char password[], int &accountIndex,
            vector< Account > &accounts )
{
   for( size_t i = 0; i < accounts.size(); i++ )
      if( strcmp( email, accounts[ i ].email ) == 0 &&
          strcmp( password, accounts[ i ].password ) == 0 )
      {
         accountIndex = i;
         return true;
      }

   cout << "\nInvalid account number or password. Please try again.\n\n";
   return false;
}

void shopping( Account &account )
{
   int choice;
   while( true )
   {
      cout << "\n1. Our Cuisine\n"
           << "2. Shopping Cart\n"
           << "3. End\n";

      do cout << "\nEnter your choice: ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
         case 1:
         ourCuisine( account ); // choose cuisines and quantities, and put into shopping cart
         break;

         case 2:
         shoppingCart( account ); // display shopping cart, then continue shopping, update cart or check
         break;

         case 3:
         return;

         default: // display error if user does not select valid choice
         cout << "Incorrect Choice!\n";
         break;
      }
   }
}

//  choose cuisines and quantities, and put into shopping cart
void ourCuisine( Account &account )
{
    for (int i = 1; i <= 12; i++) {
      cout << setw( 2 ) << i << ". " << setw( 48 ) << left << foods[ i ]
           << setw( 5 ) << right << price[ i ] << endl;
    }

    int choice= 999;
    int quantity= 999;

    while (true) {

        cout << "\nEnter your choice ( 0 to end ): ";
        cin >> choice;
        if (choice == 0) {

            return;
        }
        cout << "Enter the quantity ( 0 ~ 100 ): ";
        cin >> quantity;
        account.cart[choice] += quantity;
    }

}

// display shopping cart, then continue shopping, update cart or check
void shoppingCart( Account &account )
{
   while( true )
   {
      if( emptyCart( account ) )
      {
         cout << "Your Shopping Cart is empty!\n";
         return;
      }
      else
      {
         displayCart( account );
         int choice;
         while( true )
         {
            cout << "\n1. Continue Shopping\n"
               << "2. Update Cart\n"
               << "3. Check\n"
               << "4. End\n";

            do cout << "\nEnter your choice (1~4): ";
            while( ( choice = inputAnInteger( 1, 4 ) ) == -1 );

            switch( choice )
            {
               case 1:
               ourCuisine( account );
               return;

               case 2:
               updateCart( account );
               break;

               case 3:
               check( account );
               return;

               case 4:
               return;
            }
         }
      }
   }
}

bool emptyCart( const Account &account )
{
   for( int i = 1; i <= 12; i++ )
      if( account.cart[ i ] > 0 )
         return false;
   return true;
}

bool displayCart( const Account &account )
{
   cout << "Your Shopping Cart Contents:\n\n";
   cout << setw( 4 ) << "Code" << setw( 48 ) << "Item" << setw( 7 ) << "Price"
        << setw( 10 ) << "Quantity" << setw( 10 ) << "Subtotal" << endl;

   int total = 0;
   for( int i = 1; i <= 12; i++ )
      if( account.cart[ i ] > 0 )
      {
         cout << setw( 4 ) << i << setw( 48 ) << foods[ i ]
              << setw( 7 ) << price[ i ]
              << setw( 10 ) << account.cart[ i ]
              << setw( 10 ) << account.cart[ i ] * price[ i ] << endl;
         total += account.cart[ i ] * price[ i ];
      }

   cout << "\nTotal Cost: " << total << endl;
   return true;
}

void updateCart( Account &account )
{
    int productCode= 999;
    int quantity = 999;
    while (true) {

        cout << "\nEnter the product code: ";
        cin >> productCode;
        if (account.cart[productCode] != 0) {

            break;
        }
    }

    cout << "\nEnter the quantity: ";
    cin >> quantity;
    account.cart[productCode] = quantity;

    displayCart( account );
}

void check( Account &account )
{
   Order order;

   order.orderNumber[ 0 ] = rand() % 10 + 'A';
   for( int i = 1; i <= 9; i++ )
      order.orderNumber[ i ] = rand() % 10 + '0';
   order.orderNumber[ 10 ] = '\0';

   for( int i = 1; i <= 12; i++ )
      order.quantity[ i ] = account.cart[ i ];

   compCurrentDate( order.deliveryDate );

   cout << "\nEnter arrival date";
   cout << "\nyear: ";
   cin >> order.arrivalDate.year;
   cout << "month: ";
   cin >> order.arrivalDate.month;
   cout << "day: ";
   cin >> order.arrivalDate.day;

   createOrder( account, order );

   for( int i = 1; i <= 12; i++ )
      account.cart[ i ] = 0;

   cout << "\nAn order has been created.\n";
}

void compCurrentDate( Date &currentDate )
{
   tm structuredTime;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   currentDate.year = structuredTime.tm_year + 1900;
   currentDate.month = structuredTime.tm_mon + 1;
   currentDate.day = structuredTime.tm_mday;
}

void createOrder( const Account &account, const Order &order )
{
   ofstream outFile( "Orders.txt", ios::out );

   if( !outFile )
   {
      cout << "File Orders.dat could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   displayOrderDetails( cout, account, order );
   displayOrderDetails( outFile, account, order );

   outFile.close();

   return;
}

void displayOrderDetails( ostream &os, const Account &account, const Order &order )
{
   os << "\nOrder number: " << order.orderNumber << endl;
   os << "Delivery Date: " << order.deliveryDate.year << "/"
      << order.deliveryDate.month << "/" << order.deliveryDate.day << endl;
   os << "Arrival Date: " << order.arrivalDate.year << "/"
      << order.arrivalDate.month << "/" << order.arrivalDate.day << endl;
   os << "Recipient: " << account.name << endl;
   os << "Contact Phone Number: " << account.phone << endl;
   os << "Shipping address: " << account.address << endl;

   os << "\nShopping details:\n\n";
   os << setw( 4 ) << "Code" << setw( 48 ) << "Item" << setw( 7 ) << "Price"
      << setw( 10 ) << "Quantity" << setw( 10 ) << "Subtotal" << endl;

   int total = 0;
   for( int i = 1; i <= 12; i++ )
      if( order.quantity[ i ] > 0 )
      {
         os << setw( 4 ) << i << setw( 48 ) << foods[ i ]
            << setw( 7 ) << price[ i ] << setw( 10 ) << order.quantity[ i ]
            << setw( 10 ) << order.quantity[ i ] * price[ i ] << endl;
         total += order.quantity[ i ] * price[ i ];
      }

   os << "\nTotal Cost: " << total << endl;
}

// save all elements in accounts to the file Accounts.dat
void saveAccounts( const vector< Account > &accounts )
{
    ofstream outFile("Accounts.dat", ios::out | ios::binary);
    if (!outFile) {

        cout << "\nError: Accounts.dat cannot open.\n";
    }
    outFile.clear();
    outFile.seekp(0, ios::beg);
    for (int i = 0; i < accounts.size(); i++) {

        outFile << accounts[i].email << " " << accounts[i].password << " "
                << accounts[i].name << " " << accounts[i].address << " "
                << accounts[i].phone;
        for (int j = 1; j < 13; j++) {

            outFile << " " << accounts[i].cart[j];
        }
        outFile << '\n';
    }
}