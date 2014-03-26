/*
 * =====================================================================================
 *
 *       Filename:  wilson.c
 *
 *    Description:  Wilson prime search.
 *
 *        Version:  2.0
 *        Created:  15/11/10 17:19:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Sanz (Fs), frasanz@bifi.es
 *        Company:  BIFI, Universidad de Zaragoza
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "wilson.h"
#define LINESZ 256

int main()
{
	FILE * fi;
	FILE * fo;
	u64 primo;
	u64 compr;
	u64 m1, m2, i, tmp, temp2;
	representacion mu;
	char buff[LINESZ];
	char buff2[LINESZ];
	double invprimo;


	/* Open input and output files */
	fi=fopen("numbers","r");
	if(fi==NULL)
	{
		printf("Error opening numbers.\n");
		exit(-1);
	}
	fo=fopen("output","a+");
	if(fo==NULL)
	{
		printf("Error opening output\n");
		exit(-1);
	}

	/* To the begining of fo */
	fseek(fo,0L, SEEK_SET);


	/* We read fi and fo to check if some number is done.*/
	while (fgets (buff, LINESZ, fi)) {
		if(fgets(buff2, LINESZ,fo))
		{
			/*We can read*/
			sscanf(buff,"%lld",&primo);
			sscanf(buff2,"%lld",&compr);
			if(primo!=compr)
			{
				printf("Both numbers must be the same\n");
				exit(-555);
			}
		}
		else
		{
			/* We start with the calculation*/
			sscanf(buff,"%lld",&primo);
			invprimo=1.0/primo;
			printf("Doing the test to the prime:%lld\n", primo);
			m1=0;
			m2=1;
			for(i=2;i<=primo-1;i++)
			{
				tmp = m2*i;
				//m1 = (trunc(1.0*tmp*invprimo)+m1*i);
			  //m1 = m1 - (trunc(1.0*m1*invprimo))*primo;
				m1 = (tmp/primo+m1*i)%primo;
				if(tmp>primo)
					m2 = tmp - (trunc(invprimo*tmp))*primo;
				else
					m2 = tmp;
				printf("%d\n",m2);
				//m2 = tmp % primo;
			}
			/* We write in the output file */
			/* the prime, the prime² and the module*/
			/* If it is a wilson prime, the module must equals 0*/
			fprintf(fo,"%lld %lld %lld \n",primo, primo*primo, (m1*primo+m2+1)%(primo*primo));
		}
	}
	fclose(fi);
	fclose(fo);
	return 0;
}

