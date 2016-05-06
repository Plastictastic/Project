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
	printw("Enter Username (or enter 'new' to create new account): ");
	refresh();
	scanf("%s",entered);
	entlen = strlen(entered); //length of entered string

	//for(i=0; i!= entlen; i++) //changes entered to lowercase
	//{
	//	putchar(tolower(entered[i]));
	//}


	if (entlen>12)
	{
		printw("Invalid username. (No greater than 12 characters)\n\n");
		Startpage();
	}
	//if (strcmp(entered,"new")==0)
	//{
		//AccountCreation();
	//	printw("\n account creation");
	//	refresh();
	//	getch();
	//}
	else
	{
		printw("Account does not exist\n\nPress any key to continue...");
		refresh();
		getch();
	}
	return 0;
}