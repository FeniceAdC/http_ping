#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>


/*Structure for the management of the statistics obtained by the multiple execution of the http_ping function*/
typedef struct Stat{
	double response_min; // Minimum computed response time 
	double response_avg; // Average computed response time
	double response_max; // Maximum computed response time
	int mode; /*Mode that is chosen by the user, when he executes the program (Three possible choices: -avg for the ordering according to the average of response
	          times, -min for the ordering according to the minimum of the response times and -max for the ordering according to the maximum of response times)*/
	char address[100]; //Variable for storing the website address
}Stat;

int compare(Stat *a,Stat *b); 
void best_response(Stat *a, int n, int ch);
Stat* alloca_stat(int dim);
void dealloca_stat(Stat *c);
int http_ping( int a, char** b);
 