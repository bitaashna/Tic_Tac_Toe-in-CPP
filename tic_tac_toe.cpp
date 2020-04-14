 
#include <bits/stdc++.h>
using namespace std;

char ash[3][3];

struct Move
{
	int row , col;
};

char p='X';
char o='O';

int MovesL(char ash[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(ash[i][j]=='_')
				return 1;
		}
	}
	return 0;
}

int evaluate(char ash[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if(ash[i][0]==ash[i][1] and ash[i][1]==ash[i][2] and ash[i][1]=='p')
			return 10;
		if(ash[i][0]==ash[i][1] and ash[i][1]==ash[i][2] and ash[i][1]=='o')
			return -10;
	}
	for (int i = 0; i < 3; i++)
	{
		if(ash[0][i]==ash[1][i] and ash[1][i]==ash[2][i] and ash[2][i]=='p')
			return 10;
		if(ash[0][i]==ash[1][i] and ash[1][i]==ash[2][i] and ash[2][i]=='o')
			return -10;
	}
	if(ash[0][0]==ash[1][1] and ash[1][1]==ash[2][2] and ash[2][2]=='p')
		return 10;
	if(ash[0][0]==ash[1][1] and ash[1][1]==ash[2][2] and ash[2][2]=='o')
		return -10;
	if(ash[2][0]==ash[1][1] and ash[1][1]==ash[0][2] and ash[2][0]=='p')
		return 10;
	if(ash[2][0]==ash[1][1] and ash[1][1]==ash[0][2] and ash[2][0]=='o')
		return -10;

	return 0;
}

int minmax(char ash[3][3], int d, bool im)
{
	int score = evaluate(ash);
	if(score == 10)
		return 10;
	if(score == -10)
		return -10;

	if(MovesL(ash)==0)
		return 0;

	if(im)
	{
		int b= -100000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(ash[i][j]=='_')
				{
					ash[i][j]=p;
					b=max(b,minmax(ash,d+1, !im));
					ash[i][j]='_';
				}				
			}
		}
		return b;
	}
	else
	{
		int b= 100000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(ash[i][j]=='_')
				{
					ash[i][j]=o;
					b=min(b,minmax(ash,d+1, !im));
					ash[i][j]='_';
				}				
			}
		}
		return b;	
	}
}

Move fbestmove(char ash[3][3])
{
	int bestval= -100000000;
	Move fbestMove;
	fbestMove.row = -1;
	fbestMove.col = -1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(ash[i][j]=='_')
			{
				ash[i][j] = p;
				int temp = minmax(ash, 0 , false);
				ash[i][j]='_';
				if(temp>bestval)
				{
					fbestMove.row=i;
					fbestMove.col=j;
					bestval=temp;
				}
			}
		}
	}
	return fbestMove;
}

int main()
{
	while(true)
	{
		cout << "Welcome to Tic-Tac-Toe game by BitAashna , Aashna Chourasia. Enter N for new game or any other key to exit" << endl;
		char as;
		cin >> as;
		if(as=='N' or as=='n')
		{
			for(int i=0; i<3 ; i++)
				for(int j=0; j<3 ; j++)
					ash[i][j]='_';
			cout << "Simple rules : enter row no. and column no. respectively for your choice , you are O , i am X , so lets play, choose your first entry." << endl;
			while(MovesL(ash))
			{
				int r , c, testing;
				cin >> r >> c;
				while(ash[r-1][c-1]!='_')
				{
					cout << "Wrong Move. You can't overwrite me. Re-enter your move." << endl;
					cout << ash[0][0] << "|" << ash[0][1] << "|" << ash[0][2] << endl << ash[1][0] << "|" << ash[1][1] << "|" << ash[1][2] << endl << ash[2][0] << "|" << ash[2][1] << "|" << ash[2][2] << endl;
					cin >> r >> c;
				}
				ash[r-1][c-1]=o;
				cout << ash[0][0] << "|" << ash[0][1] << "|" << ash[0][2] << endl << ash[1][0] << "|" << ash[1][1] << "|" << ash[1][2] << endl << ash[2][0] << "|" << ash[2][1] << "|" << ash[2][2] << endl;
				testing = evaluate(ash);
				if(testing<0)
				{
					cout << "You won!" << endl;
					break;
				}
				Move mv = fbestmove(ash);
				ash[mv.row][mv.col]=p;
				cout << "Now my move." << endl;
				cout << ash[0][0] << "|" << ash[0][1] << "|" << ash[0][2] << endl << ash[1][0] << "|" << ash[1][1] << "|" << ash[1][2] << endl << ash[2][0] << "|" << ash[2][1] << "|" << ash[2][2] << endl;
				testing = evaluate(ash);
				if(testing > 0)
				{
					cout << "I won , you lost!" << endl;
					break;
				}
			}
			if(evaluate(ash)==0)
				cout << "It's a Draw...why not u play once more..." << endl;
		}
		else
			return 0;
	}
}