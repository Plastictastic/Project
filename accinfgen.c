#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// This file generates a csv file with account numbers
// 0-99. Can be used to reset all account info.


int main()
{
	int i, ones = 0,tens =0,hunds=0,thou=0,tenthou=0;
	char accnum[2];
	FILE *accinf = fopen("AccInf.csv","w");

	for (i=0; i!=100; i++) //from 0 to 10,000
	{
		accnum[0] = tens + '0';
		accnum[1] = ones + '0';

		printf("%c%c,\n", accnum[0],accnum[1]); //print accnum
		fprintf(accinf, "%c%c,\n", accnum[0],accnum[1]); //write accnum to csv

		ones +=1;

		if (ones == 10) 
			{
				tens+=1;
				ones = 0;
			}
		if (tens == 10) 
			{
				// hunds+=1;
				tens = 0;
				break;
			}
	}
	fclose(accinf);
	return 0;
}
