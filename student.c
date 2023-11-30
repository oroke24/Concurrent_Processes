/*
Jamie O'Roke, 10/30/2023
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string.h>


int main(int argc, char **argv){

    while (1){

        //seed your random number generator
	srand(time(NULL));

        //sleep for a random amount between 5 and 15 seconds to simulate studying
	sleep((rand() % (15-5+1)) + 5);
	//sleep(1);

        //randomize a single digit question number: 1,2,3 or 4
	int digit = (rand() % 4) + 1;
	char question[10];
	sprintf(question, "%d", digit);
	
        //write the random question number to standard output
	write(1, question, 1);

        //wait for a response from standard input
	char response[100];
	bzero(response, 100); 
	read(0, response, 99);
	write(2, response, 99);

        //print the response to stderr
	//write(2, "error!", 6); 

    }
}

