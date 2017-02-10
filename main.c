#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "master.h"

int main(int argc, char** argv )
{	
	pid_t pid = 0;
	int status;
	Stat *b=alloca_stat(argc-2);//allocate the space for a number of structure Stat equal to the number of address writed in the command line 
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
	else	//Only if the i have an adrress and one command like: avg, min or max 
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
			if(strncmp(http,argv[i],http_len))//evaluate whether the ith address has been entered correctly
			{
				printf("Errore nell'inserimento dell'indirizzo: %s\n\n", argv[i]);
				k++;
				continue;
			}
			
			pid = fork(); //span a child process
			if (pid < 0)
			{printf("Cannot fork!!\n");
					exit(1);
			}
			if (pid == 0)
			{				
				execl("C:/cygwin64/home/Fabio/Progetti/http_ping/http.exe","http.exe",argv[i], (char*) NULL);
				break;				
			}
		}
		//father process
		while(1){
			if(waitpid(-1, &status, WNOHANG)>0){
				rcv++;
				r=fopen("C:/cygwin64/home/Fabio/Progetti/http_ping/response.txt", "r");
				if(r==NULL)
					return -1;
				printf("\n\t------------Risultati------------\n\n");
				for(j=0;  feof(r)==0; j++)
				{
					fscanf(r, "%lf",&b[j].response_min);
					fscanf(r, "%lf",&b[j].response_avg);
					fscanf(r, "%lf",&b[j].response_max);
					fscanf(r, "%s", b[j].address);
					b[j].mode=e;
				}
				fclose(r);
				best_response(b,j-1,e);					
			}
		
			if(rcv==argc-2){
				remove("C:/cygwin64/home/Fabio/Progetti/http_ping/response.txt");
				dealloca_stat(b);
				break;
			}
		}
	}
	return 0;
}


