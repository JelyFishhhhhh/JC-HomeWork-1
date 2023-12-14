#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

int adultTicketPrice[ 13 ][ 13 ] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,  260,  310,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,  260,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

struct Reservation
{
   char reservationNumber[ 12 ]; // used to identify a reservation
   char trainNumber[ 8 ];        // used to identify a train
   char idNumber[ 12 ];          // the id number of the contact person
   char phone[ 12 ];             // the (local or mobile) phone number of the contact person
   char date[ 12 ];              // outbound date
   int originStation;            // the origin station code
   int destinationStation;       // the destination station code
   int carClass;                 // the car class code; 1:standard car, 2:business car
   int adultTickets;             // the number of adult tickets
   int concessionTickets;        // the number of concession tickets
};

struct Train
{
   char trainNumber[ 8 ];          // used to identify a train
   char departureTimes[ 13 ][ 8 ]; // the departure time of a train for each station,
};   // departureTimes[ 0 ] is not used
     // departureTimes[ i ] is the departure time of a train for station #i

char southboundStations[ 13 ][ 12 ] = { "",
   "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli",
   "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

char northboundStations[ 13 ][ 12 ] = { "",
   "Zuoying", "Tainan", "Chiayi", "Yunlin", "Changhua", "Taichung",
   "Miaoli", "Hsinchu", "Taoyuan", "Banqiao", "Taipei", "Nangang" };

Train southboundTimetable[ 100 ];
Train northboundTimetable[ 100 ];

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

void makingReservation( int numSouthboundTrains, int numNorthboundTrains );

bool suitable( Reservation &reservation, int numSouthboundTrains, int numNorthboundTrains );

// loads the southbound timetable from the file "Southbound timetable.txt"
void loadSouthboundTimetable( int &numSouthboundTrains );

// loads the northbound timetable from the file "Northbound timetable.txt"
void loadNorthboundTimetable( int &numNorthboundTrains );

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo( Reservation &reservation );

// save reservation to the end of the file Reservation details.dat
void saveReservation( Reservation reservation );

void reservationHistory( int numSouthboundTrains, int numNorthboundTrains );

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation( fstream &ioFile, Reservation &reservation );

void displayReservations( Reservation reservation, int numSouthboundTrains, int numNorthboundTrains );

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void displayReservation( Reservation reservation, Train trainTimetable[ 100 ], char stations[ 13 ][ 12 ] );

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";
   srand( static_cast< unsigned int >( time( 0 ) ) );

   int numSouthboundTrains;
   int numNorthboundTrains;

   loadSouthboundTimetable( numSouthboundTrains );
   loadNorthboundTimetable( numNorthboundTrains );

   int choice;
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Booking\n"
         << "2. Booking History\n"
         << "3. End Program";

      do cout << "\n? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
         case 1:
            makingReservation( numSouthboundTrains, numNorthboundTrains );
            break;
         case 2:
            reservationHistory( numSouthboundTrains, numNorthboundTrains );
            break;
         case 3:
            cout << "Thank you. Goodbye.\n\n";
            system( "pause" );
            return 0;
         default: // displayReservation error if user does not select valid choice
            cout << "Incorrect Choice!\n";
            break;
      }
   }
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin >> string;

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void makingReservation( int numSouthboundTrains, int numNorthboundTrains )
{
   Reservation reservation;

   do
   {
      cout << "Origin Station\n"
         << "1. Nangang\n" << "2. Taipei\n" << "3. Banqiao\n" << "4. Taoyuan\n"
         << "5. Hsinchu\n" << "6. Miaoli\n" << "7. Taichung\n" << "8. Changhua\n"
         << "9. Yunlin\n" << "10. Chiayi\n" << "11. Tainan\n" << "12. Zuoying";

      do cout << "\n? ";
      while( ( reservation.originStation = inputAnInteger( 1, 12 ) ) == -1 );

      cout << "\nDestination Station\n"
         << "1. Nangang\n" << "2. Taipei\n" << "3. Banqiao\n" << "4. Taoyuan\n"
         << "5. Hsinchu\n" << "6. Miaoli\n" << "7. Taichung\n" << "8. Changhua\n"
         << "9. Yunlin\n" << "10. Chiayi\n" << "11. Tainan\n" << "12. Zuoying";

      do cout << "\n? ";
      while( ( reservation.destinationStation = inputAnInteger( 1, 12 ) ) == -1 );

      cout << "\nTrain Number: ";
      cin >> reservation.trainNumber;

   } while( !suitable( reservation, numSouthboundTrains, numNorthboundTrains ) );

   cout << "\nDeparture Date: ";
   cin >> reservation.date;

   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

   do cout << "\n? ";
   while( ( reservation.carClass = inputAnInteger( 1, 2 ) ) == -1 );

   cout << "\nHow many adult tickets? ";
   cin >> reservation.adultTickets;

   cout << "\nHow many concession tickets? ";
   cin >> reservation.concessionTickets;

   if( reservation.originStation < reservation.destinationStation )
      displayReservation( reservation, southboundTimetable, southboundStations );
   else
   {
      reservation.originStation = 13 - reservation.originStation;
      reservation.destinationStation = 13 - reservation.destinationStation;

      displayReservation( reservation, northboundTimetable, northboundStations );

      reservation.originStation = 13 - reservation.originStation;
      reservation.destinationStation = 13 - reservation.destinationStation;
   }

   inputContactInfo( reservation );

   cout << "\nReservation Completed!\n\n";

   saveReservation( reservation );
}

// Check whether the train number matches to the originStation and destinationStation
bool suitable( Reservation &reservation, int numSouthboundTrains, int numNorthboundTrains )
{
   // North Bound (trainNumber => even)
   if((reservation.originStation > reservation.destinationStation)){

      // trainNumber pre-Filter
      if(atoi(reservation.trainNumber)% 2){

         cout<< "\nSorry, there is no suitable train for outbound time.\n\n";
         return false;
      }

      for(int i= 1; i< numNorthboundTrains; i++){

         if(atoi(reservation.trainNumber) != atoi(northboundTimetable[i].trainNumber)){

            continue;
         }

         if((northboundTimetable[i].departureTimes[13- reservation.originStation][1] != '\0') && (northboundTimetable[i].departureTimes[13- reservation.destinationStation][1] != '\0')){

            return true;
         }
      }
   }
   
   // South Bound (trainNumber => odd)

   else if((reservation.originStation < reservation.destinationStation)){

      // trainNumber pre-Filter

      if(!(atoi(reservation.trainNumber)% 2)){

         cout<< "\nSorry, there is no suitable train for outbound time.\n\n";
         return false;
      }

      for(int i= 1; i< numSouthboundTrains; i++){


         if(atoi(reservation.trainNumber) != atoi(southboundTimetable[i].trainNumber)){

            continue;
         }

         if((southboundTimetable[i].departureTimes[reservation.originStation][1] != '\0') && (southboundTimetable[i].departureTimes[reservation.destinationStation][1] != '\0')){

            return true;
         }
      }
   }
   
   // Same Station / else

   cout<< "\nSorry, there is no suitable train for outbound time.\n\n";
   return false;
}

// loads the southbound timetable from the file "Southbound timetable.txt" into southboundTimetable
void loadSouthboundTimetable( int &numSouthboundTrains )
{

   numSouthboundTrains= 1;
   ifstream inFile("Southbound timetable.txt", ios::in);
   if(!inFile){

      cout<< "Error: File Cannot be Opened.\n";
   }
   while(inFile>> southboundTimetable[numSouthboundTrains].trainNumber){

      for(int i= 1; i< 13; i++){

         inFile>> southboundTimetable[numSouthboundTrains].departureTimes[i];
      }
      numSouthboundTrains++;
   }
   inFile.close();
}

// loads the northbound timetable from the file "Northbound timetable.txt" into northboundTimetable
void loadNorthboundTimetable( int &numNorthboundTrains )
{

   numNorthboundTrains= 1;
   ifstream inFile("Northbound timetable.txt", ios::in);
   if(!inFile){

      cout<< "Error: File Cannot be Opened.\n";
   }
   while(inFile>> northboundTimetable[numNorthboundTrains].trainNumber){

      for(int i= 1; i< 13; i++){

         inFile>> northboundTimetable[numNorthboundTrains].departureTimes[i];
      }
      numNorthboundTrains++;
   }
   inFile.close();
}

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo( Reservation &reservation )
{
   cout << "\nContact Person Information\n\n";

   cout << "Identification: ";
   cin >> reservation.idNumber;

   cout << "\nPhone No: ";
   cin >> reservation.phone;

   for( int k = 0; k < 8; k++ ){

      reservation.reservationNumber[ k ] = rand() % 10 + '0';
   }
   reservation.reservationNumber[ 8 ] = '\0';
   cout << "\nReservation Number: " << reservation.reservationNumber << endl;
}


// save reservation to the end of the file Reservation details.dat
void saveReservation( Reservation reservation )
{

   fstream outFile("Reservation details.dat", ios::out | ios::binary);
   
   /*    Identification | Reservation Num | Phone Num     */

   outFile  << reservation.idNumber<<" "
            << reservation.reservationNumber<< " "
            << reservation.phone<< " ";

   /*    Date | Train Num | From | To     */

   outFile  << reservation.date<< " "
            << reservation.trainNumber<< " "
            << reservation.originStation<< " "
            << reservation.destinationStation<< " ";
   
   /*    Adult | Concession | Class    */

   outFile  << reservation.adultTickets<< " "
            << reservation.concessionTickets<< " "
            << reservation.carClass<< "\n";

   outFile.close();
}

void reservationHistory( int numSouthboundTrains, int numNorthboundTrains )
{

   Reservation reservation;
   fstream inFile("Reservation details.dat", ios::in | ios::binary);
   while( !existReservation( inFile, reservation ) );

   if( reservation.originStation < reservation.destinationStation ){

      displayReservations( reservation, numSouthboundTrains, numNorthboundTrains );
   }
   else{

      displayReservations( reservation, numSouthboundTrains, numNorthboundTrains );
   }

}

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation( fstream &ioFile, Reservation &reservation )
{
   cout << "Identification: ";
   char idNumber[ 12 ];
   cin >> idNumber;

   cout << "\nReservation Number: ";
   char reservationNumber[ 12 ];
   cin >> reservationNumber;

   while(ioFile>> reservation.idNumber){

      ioFile>> reservation.reservationNumber>> reservation.phone
            >> reservation.date>> reservation.trainNumber>> reservation.originStation>> reservation.destinationStation
            >> reservation.adultTickets>> reservation.concessionTickets>> reservation.carClass;

      if(atoi(reservation.idNumber) != atoi(idNumber)){

         continue;
      }
      if(atoi(reservation.reservationNumber) == atoi(reservationNumber)){

         return true;
      }
   }
   cout<< "\nReservation record does not exist or cannot be found in this system.\n";
   return false;
}

void displayReservations( Reservation reservation, int numSouthboundTrains, int numNorthboundTrains )
{
   if( reservation.originStation < reservation.destinationStation )
   {
      displayReservation( reservation, southboundTimetable, southboundStations );
   }
   else
   {

      reservation.originStation = 13 - reservation.originStation;
      reservation.destinationStation = 13 - reservation.destinationStation;

      displayReservation( reservation, northboundTimetable, northboundStations );

      reservation.originStation = 13 - reservation.originStation;
      reservation.destinationStation = 13 - reservation.destinationStation;
   }
}

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void displayReservation( Reservation reservation, Train trainTimetable[ 100 ], char stations[ 13 ][ 12 ] )
{

   // print title

   cout<< "\nTrip Details\n";

   // print thead

   cout  << right
         << setw(10)<< "Date"
         << setw(11)<< "Train No."
         << setw(9)<< "From"
         << setw(10)<< "To"
         << setw(11)<< "Departure"
         << setw(9)<< "Arrival"
         << setw(8)<< "Adult"
         << setw(12)<< "Concession"
         << setw(6)<< "Fare"
         << setw(10)<< "Class"
         << '\n';

   // print tbody
   
   cout  << right
         << setw(10)<< reservation.date
         << setw(11)<< reservation.trainNumber
         << setw(9)<< stations[reservation.originStation]
         << setw(10)<< stations[reservation.destinationStation];
   
   for(int i= 1; i< 100; i++){

      if(atoi(trainTimetable[i].trainNumber) != atoi(reservation.trainNumber)){

         continue;
      }
      
      cout<< setw(11)<< trainTimetable[i].departureTimes[reservation.originStation];
      cout<< setw(9)<< trainTimetable[i].departureTimes[reservation.destinationStation];
      break;
   }

   if(reservation.carClass == 1){
      
      cout  << setw(5)<<   adultTicketPrice[reservation.destinationStation][reservation.originStation]
            <<"*"
            << setw(2)<<   reservation.adultTickets
            << setw(8)<<   adultTicketPrice[reservation.destinationStation][reservation.originStation]/ 2
            << "*"
            << setw(3)<<   reservation.concessionTickets;
      
      cout  << setw(6)<<   (reservation.adultTickets* adultTicketPrice[reservation.destinationStation][reservation.originStation]) + 
                           (reservation.concessionTickets* adultTicketPrice[reservation.destinationStation][reservation.originStation]/ 2);
   }

   else{

      cout  << setw(5)<<   adultTicketPrice[reservation.originStation][reservation.destinationStation]
            << "*"
            << setw(2)<<   reservation.adultTickets
            << setw(8)<<   adultTicketPrice[reservation.originStation][reservation.destinationStation]/ 2
            << "*"
            << setw(3)<<   reservation.concessionTickets;
      
      cout  << setw(6)<<   (reservation.adultTickets* adultTicketPrice[reservation.originStation][reservation.destinationStation]) + 
                           (reservation.concessionTickets* adultTicketPrice[reservation.originStation][reservation.destinationStation]/ 2);
   }

   cout<< setw(10)<< (reservation.carClass== 1? "Standard": "Business");

   cout<< '\n';
}