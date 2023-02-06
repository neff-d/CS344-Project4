#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


void validateInput(int);
int openFile(char *);

int main(int argc, char *argv[]){

     validateInput(argc);
     
     int fd = openFile(argv[1]);
   
     int pfd[2];
     pipe(pfd);

     pid_t pid = fork();

     if(pid == -1){
          perror("fork");
     }
     else if(pid == 0){
          dup2(pfd[1], 1);
	  close(pfd[0]);

	  execvp(argv[2], argv + 2);
	  perror("execvp");
	  exit(1);
     }
     else{
          close(pfd[1]);
	  
	  char buffer[1024];
 	  int count;
	  
	  count = read(pfd[0], buffer, sizeof buffer);
	  write(fd, buffer, count);
	 
	  close(pfd[0]);
	  close(fd); 	  
     }
     wait(NULL);

} // main


void validateInput(int args){
     if(args < 3){
          printf("Not enough arguments entered. Run the program again with at least 1 command after the file name.\n");
	  exit(0);
     }
}

int openFile(char *fileName){

     int fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
     if(fd == -1){
          perror("open");
     }
     return fd;
}
