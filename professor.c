/*
Jamie O'Roke, 10/30/2023
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){

    char *prog = "student";
    char **args = NULL;


    //create two uni-directional pipes
    //one for professor to student, one from student to professor
    int pipefd_fromParent[2];
    int pipefd_fromChild[2];
    int parent_pid, child_pid;


    pipe(pipefd_fromParent);//professor to student pipe
    pipe(pipefd_fromChild);//student to professor pipe
    


    //fork to create a child process
    child_pid = fork();


    //child portion
    //need two calls to dup2, two calls to close, and a call to execv
    if (child_pid == 0) {  


    	dup2(pipefd_fromChild[1], 1);	    
    	dup2(pipefd_fromParent[0], 0);
	
   	close(pipefd_fromParent[1]); // 
    	close(pipefd_fromChild[0]); //  
				    //
        execv(prog, args);
        // NOT REACHED
	perror("execv");
	exit(1);
    } else { 
    

    	//parent portion
    	//need two calls to dup2
    	dup2(pipefd_fromChild[0], 0); //dup std out 2 child out	    
	dup2(pipefd_fromParent[1], 1); //dup std in 2 parent in

    	close(pipefd_fromParent[0]); // close parent write
    	close(pipefd_fromChild[1]); // close child read

 
    	while (1){

       		 fprintf(stderr,"prof: waiting for question\n");
       		 fflush(stderr);

       		 //read a question from child
		char response[100];
		bzero(response, 100);
		read(0, response, sizeof(response));
		fprintf(stderr, "recieved question #%c from student\n", response[0]);		

       		 //choose an answer based on the question
		switch((response[0])){
			case '1':
				write(1, "silly question\n", 16);
				break;
			case '2':
				write(1, "good question\n", 14);
				break;
			case '3':
				write(1, "smart question\n", 15);
				break;
			case '4':
				write(1, "I don't know\n", 13);
				break;
			default:
				write(1, "not recognized\n",15);
				break;
		}//end switch
		printf("\n");
    
        	//write the response to standard output
		//write(1, response, 10);
		//fprintf(stderr, "prof: after switch\n");

    	}//end while
    }//end else
}//end main

