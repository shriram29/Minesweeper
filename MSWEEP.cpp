#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>

using namespace std;

void replay();
int random(int, int);
void reveal(int);
void title();


 main()
{
	   char dateStr [9],timeStr [9];
		_strdate( dateStr);
		_strtime( timeStr );
	   ofstream gamelog("GameLOG.txt",ios::app);
	   system("cls");
	   int b;
	   do
	   {
		title();
	   cout<< "Enter number of squares per side (2 - 10)" <<"\n";
	   cin >> b;
	   }while(b < 1 && b >= 10);
	   int board[9][9];             //0 - 8 = # of mines, 9 is mine
	   int revealed[9][9];  //1 is revealed
	   int i = 0;
	   int j = 0;
		   int x = 0;
	   int y = 0;
	   int z;                               //number of mines
	   int q;

	   int dead = 0;
	   do
	   {
			 cout << "How many mines? (1 - " << ((b*b)-1) << ")" << endl;
			 cin >> z;
	   }while(z <= 0 && z >= ((b*b)-1));

	   gamelog<<"______________________________\n"
		  <<"         Minesweeper\n"
		  <<b<<" x "<<b<<" game with "<<z<<" mines \nPlayed at "<<dateStr<<"  "<<timeStr<<"\n";
	   for(i=0;i<b;i++)
			 for(j=0;j<b;j++)
				    board[i][j] = 0;
	   i = random(i, b);
	   j = random(j, b);
	   cout << "Generating board..." << endl;
	   do
	   {
			 i+=3;
			 j+=6;
			 x = random(i, b);
			 y = random(j, b);
			 if(board[y][x] != 9)
			 {
				    board[y][x] = 9;
				    z--;
				    if((y-1) >= 0)
				    if(board[y-1][x] != 9)
						  board[y-1][x]++;
				    if((y-1) >= 0 && (x-1) >= 0)
				    if(board[y-1][x-1] != 9)
						  board[y-1][x-1]++;
				    if((x-1) >= 0)
				    if(board[y][x-1] != 9)
						  board[y][x-1]++;
				    if((y+1) < b)
				    if(board[y+1][x] != 9)
						  board[y+1][x]++;
				    if((y+1) < b && (x+1) < b)
				    if(board[y+1][x+1] != 9)
						  board[y+1][x+1]++;
				    if((x+1) < b)
				    if(board[y][x+1] != 9)
						  board[y][x+1]++;
				    if((y-1) >= 0 && (x+1) < b)
				    if(board[y-1][x+1] != 9)
						  board[y-1][x+1]++;
				    if((y+1) < b && (x-1) >= 0)
				    if(board[y+1][x-1] != 9)
						  board[y+1][x-1]++;
			 }
	   }while(z>0);
	   for(i = 0; i < b; i++)
			 for(j=0;j<b;j++)
				    revealed[i][j]=0;
	   do
	   {
			 system("cls");
			 q = 0;
			 z = 0;
			 cout << "   ";
			 for(i=0;i<b;i++)
				    cout << i << " ";
			 cout << endl;
			 for(i=0;i<b;i++)
			 {
				    for(j=0;j<b;j++)
				    {
						  if(j==0)
								cout << i << " |";
						  if(revealed[i][j]==1)
								reveal(board[i][j]);
						  else
								cout << "_|";
						  if(j==(b-1))
								cout << endl;
						  if(board[i][j]!=9 && revealed[i][j]==1)
								q++;
						  if(board[i][j] == 9)
								z++;
				    }
			 }
			 if(q >= ((b*b) - z))
			 {
				    cout << "You win!" << endl;
				    gamelog<<"You won the game !! :) ";
				    dead = 1;
			 }
			 if(dead == 0)
			 {
			 cout << "X: ";
			 cin >> x;
			 cout << "Y: ";
			 cin >> y;
			 }
			 if(board[y][x] == 9)
			 {
				    system("cls");
				    cout << "You hit a mine!" << endl;
				    cout << "   ";
				    gamelog<<" You lost the game !! :( ";
				    for(i=0;i<b;i++)
						  cout << i << " ";
				    cout << endl;
				    dead = 1;
				    for(i=0; i<b; i++)
				    {
						  for(j=0;j<b;j++)
						  {
								if(j==0)
									   cout << i << " |";
								if(board[i][j]==9)
									   revealed[i][j]=1;
								if(revealed[i][j]==1)
									   reveal(board[i][j]);
								else
									   cout << "_|";
								if(j==(b-1))
									   cout << endl;
						  }
				    }

			 }
			 if(board[y][x]==0)
			 {
				    revealed[y][x] = 1;
				    for(i=0;i<b;i++)
				    {
						  for(j=0;j<b;j++)
						  {
								if(i>(y-2)&&i<(y+2))
									   if(j>(x-2)&&j<(x+2))
											 if(board[i][j]!=9)
											   revealed[i][j]=1;
						  }
				    }
			 }
			 if(board[y][x]>0 && board[y][x]<9)
				    revealed[y][x] = 1;
	   } while(dead == 0);
	   gamelog<<"\n";
	     gamelog<<"\n______________________________" ;
		 gamelog.close();
	   if (dead == 1)
			 replay();
}

void replay()
{
	   char a;
	   cout << "1) Replay 2) Quit" << endl;
	   cin >> a;
	   switch(a)
	   {
			 case '1':
				    main();
				    break;
			 case '2':
				    cout << "Quit" << endl;
				    break;
			 default:
				    cout << "Invalid input" << endl;
				    replay();
				    break;
	   }
}

void reveal(int x)
{
	   if(x == 0)
			 cout << "o|";
	   else if(x == 9)
			 cout << "x|";
	   else
			 cout << x << "|";
}

int random(int i, int b)
{
	   long ran;
	   int t = time(0);
	   int s;
	   srand(t);
	   ran = rand();
	   ran >>= ran / (ran * i) + (i * 1337);
	  ran = ran % b;
	   return ran;
}

void title()
{

cout<<"\n  __  __ _                                                   "
<<"\n |  \\/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ "
<<"\n | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|"
<<"\n | |  | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   "
<<"\n |_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   "
<<"\n                                            |_|             \n\n"
<<"\t\t\tDeveloped by Shriram"
<<"\n Rules :"
	   <<" \n 1. You must enter the Size of your game board"
	   <<" \n 2. Next you must enter the no of mines you need in your board"
	   <<" \n 3. Once the board is created you will be asked to enter the x and y coordinate of the place you wish to select"
	   <<" \n 4. The number  that appears in the place you selected is the no of mines arround your place"
	   <<" \n 5. You loose if you hit a mine, Simple :)\n\n\n";
getch();
}
