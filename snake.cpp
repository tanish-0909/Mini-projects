#include<iostream>
//#include<conio.h> // console i/o
#include <ncurses.h>
#include <unistd.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y; //head position
int tailX[100], tailY[100];
int ntail = 0;

int fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void setup() 
{
	//cout << "hi0\n";
	initscr();      // start ncurses
	//cout << "hi1\n";
	noecho();       // don't echo input
	//cout << "hi2\n";
	cbreak();       // disable line buffering
	//cout << "hi3\n";
	keypad(stdscr, TRUE);  // enable arrow keys
	//cout << "hi4\n";

	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw()
{
	clear(); // ncurses to clear the screen
	for(int i = 0; i < width; i++)
		//top wall
		printw("#");
	printw("\n");
	
	//print the map
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(j == 0)
				printw("#");
			else if(j == width - 1)
				printw("#");
			else if(i == y && j == x)
				printw("O");
			else if(i == fruitY && j == fruitX)
				printw("f");
			else
			{
				bool printed = false;
				for(int m = 0; m < ntail; m++)
					if(j == tailX[m] && i == tailY[m])
					{
						printw("o");
						printed = true;
					}
				if(!printed)
					printw(" ");
			}
		}
		printw("\n");
	}

	for(int i = 0; i < width; i++)
		//bottom wall
		printw("#");
	printw("\n\n\n\nScore: ");
	printw("%d", score);
	
}

void input()
{
	timeout(0);  // non-blocking getch()
	int ch = getch();
	switch(ch)
	{
		//move the snake with wasd
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			dir = STOP;
			gameOver = true;
			break;
	}
}

void logic()
{
	//follow the tail
	int prevX = x;
	int prevY = y;	
	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}

/*	if(x >= width || x <= 0 || y >= height || y <= 0)
	{	
		draw();
		gameOver = true;
		return;
	}*/ 
	if(x >= width) x = 0;
	else if(x <= 0) x = width-1;
	if(y >= height) y = 0;
	if(y <= 0) y = height - 1;

	for(int m = 0; m < ntail; m++)
	{
		if(x == tailX[m] && y == tailY[m])
		{
			gameOver = true;
			draw();
			return;
		}
	}


	
	if(x == fruitX && y == fruitY)
	{
		score++;
		fruitX = rand() % width;
        	fruitY = rand() % height;
		ntail++;
		for(int n1 = ntail-1; n1 >= 1; n1--)
		{
			tailX[n1] = tailX[n1-1];
			tailY[n1] = tailY[n1-1];
		}
		tailX[0] = prevX;
		tailY[0] = prevY;
	} else {
		for(int i = ntail-1; i >= 1; i--)
        	{
        	        tailX[i] = tailX[i-1];
        	        tailY[i] = tailY[i-1];
        	}
        	tailX[0] = prevX;
        	tailY[0] = prevY;
	}
}


int main(void)
{
	setup();

	while(!gameOver )
	{
		draw();
		input();
		logic();
		usleep(400000 - score * 20000);		
		if(score == 1)
			printw("Score: %d. YOU WIN !!!\n", score);
		
	}
	printw("\n\nGame Over!! press x to exit");
	timeout(0);  // non-blocking getch()
        int ch = getch();
	while(ch != 'x')
		ch = getch();
	endwin();       // restore terminal before exiting
    	return 0;
}

