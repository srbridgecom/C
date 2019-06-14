C++, Bubble sort program

 Print	 Email
 
Category: C++

Published on Friday, 22 April 2011 01:42

Written by Ryan Bridglal

Hits: 513

/* bubblesort.cpp : Defines the entry point for the console application.

create a bubble sort program = COMPLETE

After the first pass, the largest number on top, then	 = COMPLETE

follow through with the others. = COMPLETE

Modify the sort and check for swaps. If the data is	 = COMPLETE

already in order, terminate program. If swaps have

been made, another pass is required.

C++, How To program, Exercise 7.12

Ryan Bridglal 04/10/2011




*/

//headers

#include "stdafx.h"

#include "iostream"

#include "stdio.h"

//global declare

using namespace std;

//bubble sort function

void bubbleSort(int *array, int length)

{

     int iSort, jSort;

 

     for ( iSort = 0; iSort < 10; iSort++ )

     {

          for ( jSort = 0; jSort < iSort; jSort++ )

          {

               if (array[iSort] > array[jSort] )

               {

                    //perform the swap

                    int tempSwap = array[iSort];

                    array[iSort] = array[jSort];

                    array[jSort] = tempSwap;

               }

          }

     }

}

 

 

//output gui from array

void outputGUI(int *array,int length)

{

                    int iSort = 0;

                    for ( iSort = 0; iSort < 10; iSort++ )

                    cout << array[iSort] << "\n";

}

 

 

//main program

void main()

{


     //into gui

     cout << "This bubble Sort program will sort the number 1 to 10 in decending order!\n\n";

 

     //array to sort

     int arraySort[]={ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

 

     //call bubblesort function

     bubbleSort(arraySort,10);

 

     //call outputgui function

     outputGUI(arraySort,10);

 

     //wait user input and exit

     cout << "\n";

     system("Pause");

 
}
