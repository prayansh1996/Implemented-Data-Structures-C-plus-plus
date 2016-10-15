#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED
#include <stdio.h>
#include "conio.h"
#include <iostream>
#include <windows.h>


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y);
void waitkey();
void sleep(int k)   {   Sleep(k);}
void getcursorpos(int &x, int &y)
{   POINT p;
    GetCursorPos(&p);
    x = p.x;
    y = p.y;
}

void gotoxy(int x, int y)
{
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

void waitkey()
{
   while (_kbhit()) getch(); // Empty the input buffer
   _getch(); // Wait for a key
   while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
}

void getxy(int &x, int&y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(console, &csbi))
	{
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;

	}
}

int getx()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
    return -1;
  return csbi.dwCursorPosition.X;
}

int gety()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
    return -1;
  return csbi.dwCursorPosition.Y;
}

void fill(int k, char ch)
{
    for(int i=0; i<k; i++)
    {   cout<<ch;}
}

void print(int arr[], int n)
{
    cout<<endl;
    for(int i=0; i<n; i++)
    {   cout<<arr[i]<<" ";}
}
//HOW TO USE GUIDE
/*gotoXY(int, int)
sleep(x ms)
WaitKey(); cin.get() ke jaise
cout<<string(100,'\b');
csbi gives location of console cursor
getx() gives the last written char like gety() gives curr line
*/

#endif // MISC_H_INCLUDED
