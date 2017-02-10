#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "master.h"

/*Callback used in the qsort function, that compares the statistics, according to the choice (selection of avg, min or max) made by the user.*/
int compare(Stat *a,Stat *b)
{
	switch (a->mode)
	{
		case 0:
			if (a->response_avg <  b->response_avg) return -1;
			if (a->response_avg == b->response_avg) return 0;
			if (a->response_avg >  b->response_avg) return 1;
			break;
			
		case 1:
			if (a->response_min <  b->response_min) return -1;
			if (a->response_min == b->response_min) return 0;
			if (a->response_min >  b->response_min) return 1;
			break;
			
		case 2:
			if (a->response_max <  b->response_max) return -1;
			if (a->response_max == b->response_max) return 0;
			if (a->response_max >  b->response_max) return 1;
			break;
	}
	return 2;
}

/*Function that computes what is the Internet address with the best average/minimum/maximum response time, according to the choice made by the user*/ 
void best_response(Stat *a, int n, int ch)
{
	int i=0;
	int q;
	double tmp;
   	int k=0;
	switch (ch){		
		case 0:
			tmp=a[0].response_avg;
			for(i=0;i<n; ++i)
			{
				if(a[i].response_avg<tmp)
				{
					tmp=a[i].response_avg;
					k=i;
				}
			}
			printf("L'indirizzo con il minimo tempo medio di risposta e': %s\n\n", a[k].address);
			printf("Gli indirizzi ordinati per tempo medio di risposta risultano:\n\n");
			qsort((void*)a,n, sizeof(Stat), (void*)compare);
			for(q=0; q<n; q++)
				printf("%d) min: %g / avg: %g / max: %g indirizzo: %s\n", q+1,a[q].response_min,a[q].response_avg, a[q].response_max,a[q].address);
			break;
		
		case 1:
			tmp=a[0].response_min;
			for(i=0;i<n; ++i)
			{
				if(a[i].response_min<tmp)
				{
					tmp=a[i].response_min;
					k=i;
				}
			}
			printf("L'indirizzo con il tempo minimo di risposta e': %s\n\n", a[k].address);
			printf("Gli indirizzi ordinati per tempo minimo di risposta risultano:\n\n");
			qsort((void*)a,n, sizeof(Stat), (void*)compare);
			for(q=0; q<n; q++)
				printf("%d) min: %g / avg: %g / max: %g indirizzo: %s\n", q+1,a[q].response_min,a[q].response_avg, a[q].response_max,a[q].address);
			break;
		
		case 2:
			tmp=a[0].response_max;
			for(i=0;i<n; ++i)
			{
				if(a[i].response_max<tmp)
				{
					tmp=a[i].response_max;
					k=i;
				}
			}
			printf("L'indirizzo con il minore tempo massimo di risposta e': %s\n\n", a[k].address);
			printf("Gli indirizzi ordinati per tempo massimo di risposta risultano:\n\n");
			qsort((void*)a,n, sizeof(Stat), (void*)compare);
			for(q=0; q<n; q++)
				printf("%d) min: %g / avg: %g / max: %g indirizzo: %s\n", q+1,a[q].response_min,a[q].response_avg, a[q].response_max,a[q].address);
			break;
	}		
}

/*Function that allocates the statistics structure*/
Stat* alloca_stat(int dim)
{
	Stat *c;
	c=(Stat*)malloc(dim*sizeof(Stat));
	if(c==NULL)
		return 0;
	return c;
}

void dealloca_stat(Stat *c)
{
	free(c);
	return;
}