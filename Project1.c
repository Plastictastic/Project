#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <time.h>


//Sandoval Bank of NY
//Startpage: Enter username and PIN (or enter "new" to create new account)
//Account Creation: create username, randomly generates pin
//Main Menu: Withdrawl, Deposit, Transaction History, Transfer, Logout
int Startpage();
int MainMenu();
void AccountCreation(char*);
void checklogin(int, char*);
static char actacc[3], anykey[]="(Press any key to continue...)";


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
	int i=0, entlen, accnum;
	printw("Welcome to Sandoval Bank of NY!\n");
	printw("===============================\n\n");
	printw("Please enter your account number to begin\n(or enter 'new' to create a new account): ");
	refresh();
	scanw("%s",entered);
	entlen = strlen(entered); //length of entered string
	accnum = atoi(entered);

	while(entered[i]) //changes entered to lowercase
	{
		entered[i] = putchar(tolower(entered[i]));
		i++;
	}

	// printw("%s",entered);  //was used to check lowercase conversion
	// refresh();
	// getch();


	if (entlen!=2 && strcmp(entered, "new") != 0)
	{
		clear();
		refresh();
		printw("Invalid account number.\n\n%s",anykey);
		getch();
		Startpage();
	}
	if (strcmp(entered,"new")==0)
	{
		AccountCreation(entered);
	}

	if (entlen==2 && accnum <100)
	{
		checklogin(accnum, entered);
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

int MainMenu()
{
	int ch;
	keypad(stdscr, TRUE);
	noecho();
	clear();
	printw("Main Menu\n");
	printw("=========\n\n");
	//*printw("Current Balance: $%d\n", balance);
	printw("1) Withdrawal (F1)\n2) Deposit (F2)\n3) Transaction History (F3)\n4) Transfer (F4)\n5) Logout (F5)");
	refresh();
	ch = getch();
	if (ch == KEY_F(1))
	{
		clear();
		refresh();
		printw("How much would you like to withdraw?: $");
	}

	if (ch == KEY_F(2))
	{
		clear();
		refresh();
		printw("How much would you like to deposit?: $");
	}

	if (ch == KEY_F(3))
	{
		clear();
		refresh();
	}

	if (ch == KEY_F(4))
	{
		clear();
		refresh();
	}

	if (ch == KEY_F(5))
	{
		clear();
		refresh();
		Startpage();
	}
	else
	{
		MainMenu();
	}
}

void AccountCreation(char *entered)
{	
	int i,h;
	char check[7],chpin[4];
	clear();
	printw("Account Creation\n");
	printw("================\n\n");

	FILE *accinf = fopen("AccInf.csv","r+");

	int commapos;

	while(fgets(check,7,accinf)) 
	{
		if (strlen(check)==4)
		{
			commapos = (ftell(accinf)-1);
			time_t t;
			srand((unsigned) time(&t)); //starts random number seeding
			for(i=0; i<4; i++)
			{
			    h = (rand()%9);//generates number from 0 to 9
				chpin[i] = (h+'0'); //the +'0' converts int to char
			}
			

			printw("Account created.\nYour account number is: %.*s",2,check);
			printw("\nYour PIN number is: %.*s\n\n",4,chpin);
			printw("(These numbers are important, so don't forget them!)\n\n%s)",anykey);
			break;
		}

		if (feof(accinf)) 
		{
			printw("Account limit reached. No new accounts\ncan be created at this time.\n\n%s",anykey);
			refresh();
			getch();
			Startpage();
		}
	}

	rewind(accinf);
	fseek(accinf,commapos,SEEK_SET);
	fprintf(accinf,"%-.4s",chpin);

	fclose(accinf);
	refresh();
	getch();
	Startpage();
}       

void checklogin(int accnum, char *entered)
{
	FILE *accinf = fopen("AccInf.csv","r+");

	char acchar[3], check[10], pin[4];
	int i = 0;

	for(i=0; i!=2; i++)
	{
		acchar[i] = entered[i];
	}
	
	acchar[2] = ',';


	while(fgets(check,10,accinf))
	{
		printw("\n%c%c",check[0],check[1]);
		if (check[4]=='\0')
		{
			clear();
			printw("Invalid PIN.\n\n%s",anykey);
			break;
		}
		if (check[0] == acchar[0] && check[1] == acchar[1] && check[4] != '\0') 
		{
			clear();
			printw("%c%c%c%c\n\nEnter PIN: ",check[3],check[4],check[5],check[6]);
			refresh();
			scanw("%s",pin);

			if (check[3] == pin[0] )
			{
				if(check[4] == pin[1])
				{
					if(check[5] == pin[2])
					{
						if(check[6] == pin[3])
						{
							printw("PIN has been validated.\n\n");
							printw("Press any key to continue...");
							getch();
							fclose(accinf);
							MainMenu();
						}
					}
				}

			}
			//printw("[[%c%c and %c%c]]",check[0], check[1],acchar[0], acchar[1]);
			
		}
		else
		{
			//do nada
		}
	}

	fclose(accinf);

	refresh();
	getch();
	Startpage();
}
