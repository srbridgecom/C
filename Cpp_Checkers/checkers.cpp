/* Category: C++
Published on Tuesday, 13 May 2011 00:10
Written by Ryan Bridglal
Hits: 0
Original Code posted @ gone
Ryan J. Bridglal,  
November 2011
*/

// checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "stdlib.h"
#include "ctype.h"

using namespace std;
//REGULAR PROTOTYPES

int getxcoord(void);
int getycoord(void);
void showboard(int matrix[8][8]);
char convert(int number);

//Checker Piece Class for Inheritance

class checkerpiece
{
protected:
	int x;
	int y;
	bool king;
	bool selected;
public:
	int givexposition(void);
	int giveyposition(void);
	void select(void);
	void unselect(void);
	bool whetherselected(void);
	void showpos();
	//bool alljump(void);  <- Implement This!
	checkerpiece(int startx, int starty, bool kingship = 0);
};

void checkerpiece::showpos() {
   cout << (char)(x+'A') << y+1;
}

int checkerpiece::givexposition(void)
{
	return(x);
}

int checkerpiece::giveyposition(void)
{
	return(y);
}

void checkerpiece::select(void)
{
	showpos();
	selected = 1;
}

void checkerpiece::unselect(void)
{
	selected = 0;
}

bool checkerpiece::whetherselected(void)
{
	return(selected);
}

checkerpiece::checkerpiece(int startx, int starty, bool kingship)
{
	x = startx;
	y = starty;
	king = kingship;
}

//White Piece

class wpiece : public checkerpiece
{
public:
	bool moveup(int nextx, int nexty, int matrix[8][8]);
	bool jumpup(int nextx, int nexty, int matrix[8][8]);
	wpiece(int startx = -1, int starty = -1, bool kingship = 0);
};

bool wpiece::jumpup(int nextx, int nexty, int matrix[8][8]) {
	if(nextx == x + 2 && nexty == y + 2 && matrix[x+1][y+1] == 2 )
	{
		cout << "jumped up right" << endl;
		matrix[x][y] = 0;
		matrix[x+1][y+1] = 0; // remove opponent
		matrix[nextx][nextx] = 1;

		x = nextx;
		y = nexty;

		return(1);
	}
	if(nextx == x - 2 && nexty == y + 2 && matrix[x-1][y+1] == 2)
	{
		cout << "jumped up left" << endl;
		matrix[x][y] = 0;
		matrix[x-1][y+1] = 0; // remove opponent
		matrix[nextx][nextx] = 1;

		x = nextx;
		y = nexty;
		return(1);
	}

	cout << "No Jump - sorry" << endl;

	return(0);
}


bool wpiece::moveup(int nextx, int nexty, int matrix[8][8])
{
	cout << "try moving " << x << "," << y << " to " << nextx << "," << nexty << endl;
	if((nextx == x + 1 ) && ( nexty == y + 1 ) && ( matrix[nextx][nexty] == 0))
	{
		cout << "moved up right" << endl;
		matrix[x][y] = 0;
		matrix[nextx][nexty] = 1;
		
		x=nextx;
		y=nexty;

		return(1);
	}
	if(nextx == x - 1 && nexty == y + 1 && matrix[nextx][nexty] == 0)
	{
		cout << "moved up left" << endl;
		matrix[x][y] = 0;
		matrix[nextx][nexty] = 1;

		x=nextx;
		y=nexty;
		return(1);
	}

	cout << "no move - sorry" << endl;

	return(0);
}

wpiece::wpiece(int startx, int starty, bool kingship):checkerpiece(startx, starty, king)
{
	x = startx;
	y = starty;
	king = kingship;
}

//CLASS-RELATED PROTOTYPES

void printpieces(wpiece whitepiece[12]);
int findpiece(wpiece whitepiece[12], int x, int y);

////////
//MAIN//
////////
int _tmain(int argc, _TCHAR* argv[])
{
	int matrix[8][8] = {	1,0,1,0,0,2,0,2,
				0,1,0,0,0,0,2,0,
				1,0,1,0,0,2,0,2,
				0,1,0,0,0,0,2,0,
				1,0,1,0,0,2,0,2,
				0,1,0,0,0,0,2,0,
				1,0,1,0,0,2,0,2,
				0,1,0,0,0,0,2,0};
				
	int xposition;
	int yposition;
	int xposition2;
	int yposition2;
	int index;

	wpiece whitepiece[12] = {wpiece(0,0,0),wpiece(2,0,0),wpiece(4,0,0),wpiece(6,0,0),wpiece(1,1,0),wpiece(3,1,0),
	                         wpiece(5,1,0),wpiece(7,1,0),wpiece(0,2,0),wpiece(2,2,0),wpiece(4,2,0),wpiece(6,2,0)};
	
	
	printpieces(whitepiece);

	bool turn = 0;

	showboard(matrix);

	while(turn == 0)
	{
		cout << "=-WHITE'S TURN-=" << endl;
		cout << "Enter coordinates of piece to move" << endl;
		xposition = getxcoord();
		yposition = getycoord();

		while((index=findpiece(whitepiece, xposition, yposition)) == 12)
		{
			cout << "No White Piece found - Enter coordinates of piece to move" << endl;
			xposition = getxcoord();
			yposition = getycoord();
		}

		cout << "Where do you want to move it?" << endl;
		xposition2 = getxcoord();
		yposition2 = getycoord();

		while(findpiece( whitepiece, xposition2, yposition2) != 12)
		{
			//cout << findpiece(whitepiece, xposition2, yposition2) << endl;
			cout << "Already a Piece there - Enter different place to move" << endl;
			xposition2 = getxcoord();
			yposition2 = getycoord();
		}

		if ( ! whitepiece[index].moveup(xposition2, yposition2, matrix) && 
		     ! whitepiece[index].jumpup(xposition2, yposition2, matrix) ) {
			cout<< "Not a valid move - Enter different place to move" << endl;
		}

		showboard(matrix);
	}

	return (0);
}


//FUNCTIONS

int getxcoord(void)
{
	char letter;
	int x = 9;

	cout << "A - H: ";
	
	while(x == 9)
	{
		cin >> letter;
		letter = toupper(letter);
		x=letter-'A' + 1;
	}

	return(x-1);
}

int getycoord(void)
{
	int y = 9;

	cout << "1 - 8: ";
	cin >> y;	
	while(y < 1 || y > 8)
	{
		cout << "Please give a number from 1 to 8: ";
		cin >> y;
	}

	return(y-1);
}

int findpiece(wpiece whitepiece[12], int x, int y)
{
	int finder;

	cout << "finding piece at " << x << "," << y;
	for (finder = 0; finder < 12; finder++)
	{
		if (whitepiece[finder].givexposition() == x && whitepiece[finder].giveyposition() == y)
		{
			cout << " returns " << finder << " ";
			whitepiece[finder].select();
			cout << endl;
			return(finder);
		}
	}
	cout << " returns " << finder << endl;

	return(finder);
}

void showboard(int matrix[8][8])
{
	int x;
	int y;

	cout <<  "\n  A   B   C   D   E   F   G   H  " << endl;
	cout <<    "|---|---|---|---|---|---|---|---|" << endl;

	for(y = 7; y >= 0; y--)
	{
		for(x = 0; x < 8; x++)
		{
			cout << "| " << convert(matrix[x][y]) << " ";
		}

		cout <<  "| " << y+1 << endl << "|---|---|---|---|---|---|---|---|" << endl;
	}
	cout << endl;
}

char convert(int number)
{
	switch(number)
	{
		case 0	:	return(' ');
					break;
		case 1	:	return('w');
					break;
		case 2	:	return('b');
					break;
		case 3	:	return('W');
					break;
		case 4	:	return('B');
					break;
		default	:	return('!');
	}
}


void printpieces(wpiece whitepiece[12])
{
	int count;

	for(count = 0; count < 12; count++)
	{
		cout << "White Piece Index Number " << count << " has coordinates: " << whitepiece[count].givexposition() << ", " << whitepiece[count].giveyposition() << endl;
	}
}
