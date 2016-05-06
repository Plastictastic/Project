#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>


//Sandoval Bank of NY
//Startpage: Enter username and PIN (or enter "new" to create new account)
//Account Creation: create username, randomly generates pin
//Main Menu: Withdrawl, Deposit, Transaction History, Transfer, Logout
int Startpage();

void main()
{
	initscr();
	Startpage();
	getch();
	endwin();
}

int Startpage()
{
	clear();
	refresh();
	char user[12], entered[13];
	int i, entlen;
	printw("Welcome to Sandoval Bank of NY!\n");
	printw("===============================\n\n");
	printw("Please enter your account username to begin (or enter 'new' to create a new account): ");
	refresh();
	scanw("%s",entered);
	entlen = strlen(entered); //length of entered string

	//for(i=0; i!= entlen; i++) //changes entered to lowercase
	//{
	//	putchar(tolower(entered[i]));
	//}


	if (entlen!=6 && strcmp(entered, "new") != 0)
	{
		clear();
		refresh();
		printw("Invalid account username.\n\nPress any key to continue...");
		getch();
		Startpage();
	}
	//if (strcmp(entered,"new")==0)
	//{
		//AccountCreation();
	//	printw("\n account creation");
	//	refresh();
	//	getch();
	//}

	if (strcmp(entered, "new") == 0)
	{
		char desired[6];
		clear();
		refresh();
		printw("Please enter your desired username (no greater than 6 characters): ");
		refresh();
		scanw("%s",desired);
	}

	else
	{
		clear();
		refresh();
		printw("Account does not exist.\n\nPress any key to continue...");
		getch();
		Startpage();
	}
	return 0;
}