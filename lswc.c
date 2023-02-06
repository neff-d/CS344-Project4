#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){


     int pfd[2];
     pipe(pfd);

     pid_t pid = fork();

     if(pid == -1){
	  perror("fork");   
     }
     else if(pid == 0){
          dup2(pfd[0], 0);    
 	  close(pfd[1]);
	
	  execlp("wc","wc", "-l", NULL);
	  perror("execlp");

	  exit(1);	
     }
     else{
	  dup2(pfd[1], 1);
	  close(pfd[0]);
	
	  if(argc > 1){
	       execlp("ls", "ls", "-1a",argv[1], NULL);
	       perror("execlp");	   	
   	  }
	  else{
	       execlp("ls", "ls", "-1a", NULL);
	       perror("execlp");
	  }     
     }

     wait(NULL);
     	   
} // main
