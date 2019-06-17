Ryan Bridglal 2011

headers*/
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "iostream"
#include "iomanip"

//global declare
using namespace std;

//70 positions
const int finishLine = 70;

//prototype functions to call
void moveTortoise (int *);
void moveHare(int *);
void outputGuiRace( int *,int *);

//main code
int main()
{
	//declare variables
    	int tortoise = 1, hare = 1, timer = 0;

	//randon # gen
    	srand( time( 0 ) );

	//outgui begin race
    	cout << "This is the Turtle and Hare Race!\n\n"
		<< "H = Hare and T = Turtle.\n\nREADY......SET.......\n\n"
		<< "BANG!\n\nAND THEY'RE OFF!\n\n\n";
       
    	//race functions being called while turtle/hare ISNOT at finishline
    	while ( tortoise != finishLine && hare != finishLine ) 
	{
	moveTortoise(&tortoise);
        moveHare(&hare);
        outputGuiRace(&tortoise,&hare);
        ++timer;
	} 

    	//test for winner and output
    	if ( tortoise >= hare )
		cout << "\n\nTORTOISE WINS!!! YAY!!!\n HE GETS CARROTS AND LETTUCE!\n\n";
	else
		cout << "Hare wins. Yuch.\n But, HE STILL GETS CARROTS AND LETTUCE!\n\n";
   
	cout << "Elapsed Time is: " << timer << " seconds" << "\n", system("Pause");
	
	return 0; //exit
}


//move tortoise
void moveTortoise(int *tortoisePointer)
{
   	int x = 1 + rand() % 10; //gen random int for range

   	//determine pace
   	if ( x >= 1 && x <= 5 )        		// fast plod
      		*tortoisePointer += 3;
   	else if ( x == 6 || x == 7 )   		// slip
      		*tortoisePointer -= 6;
   	else                           		// slow plod 8 to 10
      		++( *tortoisePointer );

   	//test for turtle start at 1, no then move to position 1
   	if ( *tortoisePointer < 1 ) 
      		*tortoisePointer = 1; 

   	//Test for is turtle at finishline
   	else if ( *tortoisePointer > finishLine )
      		*tortoisePointer = finishLine;
}


//move hare
void moveHare(int *harePointer)
{
	int y = 1 + rand() % 10; //gen random int for range

    	// determine which move to make
    	if ( y >= 1 && y <= 5 )        		// fast plod
       		*harePointer += 3;
    	else if ( y == 6 || y == 7 )   		// slip
       		*harePointer -= 6;
    	else                           		// slow plod 8 to 10
       	++( *harePointer );
   
	//test for Hare to start at 1, no then move to position 1
    	if ( *harePointer < 1 )
       		*harePointer = 1;

    	//Test for is hare at finishline
    	else if ( *harePointer > finishLine )
       		*harePointer = finishLine;
}


//output positions of animals
void outputGuiRace(int *pointerHare,int *pointerTortoise)
{
	//turtle bites the hare
    	if ( *pointerHare == *pointerTortoise ) 
      		cout << setw( *pointerTortoise ) << "TURTLE BITES HARE!!!OUCH!!!";

	//ouput turtle in front of hare....    H      T
    	else if ( *pointerHare < *pointerTortoise ) 
      		cout << setw( *pointerHare ) << "T" 
           	<< setw( *pointerTortoise - *pointerHare ) << "H";

	//ouput Hare in front of turtle....    T      H
    	else
      		cout << setw( *pointerTortoise ) << "H" 
           	<< setw( *pointerHare - *pointerTortoise ) << "T";

    cout << "\n";
}
