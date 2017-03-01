#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>
#include "master.h"
#include "http_ping.h"

int main(int argc, char** argv )
{	
	pid_t pid = 0;
	int status;
	Stat *b=alloca_stat(argc-2);//Allocate the space for a number of structure Stat equal to the number of address writed in the command line 
	int i,e,j;
	FILE *r;
	int rcv=0;
	int k=0;
	char *http = "http://";
	int http_len=strlen(http);
	
	/*Selection of the mode inserted by the user among the average, minimum and maximum options*/
	if((argc<2) || ((strcmp(argv[1], "-avg")  != 0) && (strcmp(argv[1], "-min" ) != 0) && (strcmp(argv[1], "-max")!= 0)))
	{
		printf("Errore nell'inserimento\n");
		return 0;
	}
	else	//Only if the I have an adrress and one command like: avg, min or max 
	{
		if(strcmp(argv[1],"-avg")==0)//Selecting mode
			e=0;
		else if(strcmp(argv[1],"-min")==0)
			e=1;
		else
			e=2;
		printf("%d",e);
		for(i=2; i!=argc; i++)
		{
			if(strncmp(http,argv[i],http_len))//Evaluate whether the ith address has been entered correctly
			{
				printf("Errore nell'inserimento dell'indirizzo: %s\n\n", argv[i]);
				k++;
				continue;
			}
			
			pid = fork(); //Span a child process
			if (pid < 0)
			{
				printf("Cannot fork!!\n");
				exit(1);
			}
			if (pid == 0)
			{		
				
				http_ping(2,&argv[i]);	
				exit(0);				
			}
		}
		//Father process
		while(1)
		{
			wait(&status);
			rcv++;

			r=fopen("C:/Windows/temp/temp.txt", "r");
			if(r==NULL)
			{
				return -1;
				printf("Error in file opening\n");
			}
			printf("\n\t------------Results------------\n\n");
			int fd=fileno(r);
			flock(fd,LOCK_EX);
			for(j=0;  feof(r)==0; j++)
			{
				fscanf(r, "%lf",&b[j].response_min);   
				fscanf(r, "%lf",&b[j].response_avg);
				fscanf(r, "%lf",&b[j].response_max);
				fscanf(r, "%s", b[j].address);
				b[j].mode=e;
			}
			flock(fd, LOCK_UN);
			fclose(r);
			best_response(b,rcv-1,e);
			if(rcv==argc-2)
			{
				fclose(fopen("C:/Windows/temp/temp.txt", "w"));
				dealloca_stat(b);
				break;
			}			
		}	
	}
}



