#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void type_prompt(){
	static int first=1;
	if(first){
		//clear screen for the first time
		// \e is escape codes or sequences to control the formatting color and other 
		//output, interpret as commands, not character codes
		const char* CLEAR_SCREEN_ANSI = "e\[1:1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI,12);
		first=0; //variable set 0 so it wont do it again
	}
	printf("#"); //display prompt
}

void read_command(char command[], char *param[]){
	char line[1024];
	int count=0;
	int i=0;
	int j=0;
	char *array[120], *pch;
	
	//Read one line
	for(;;){
		int c=fgetc(stdin);	//get what has been entered by the user
		line[count++]=(char) c;
		//when returned is entered, exit loop
		if(c=='\n'){
			//a line of characters has been entered
			break;
		}
	}
	
	if(count==1){
		return;
	}
	
	//break the line into tokens (words)
	pch=strtok(line, "\n");
	
	//parse the line into words
	while(pch!=NULL){
		//put the words in a variable array
		array[i++]=strdup(pch);
		pch=strtok(NULL,"\n");
	}
	
	//first word is the command
	strcpy(command, array[0]);
	
	//other parameters 
	for(; j<i; j++){
		param[j]=array[j];
	}
	param[i] = NULL; //NULL terminate the parameter list
}

int main(){
	//2 arrays for the commands and an array of pointers to hold the parameters list
	char cmd[120], command[120], *par[50];
	//array that defines environment variables
	char *envp[]={(char *) "PATH=/bin", 0};	//assume all commands are in directory bin
	while(1){	//loop
		type_prompt();	//display prompt in the screen
		read_command(command, par);	//read commands and parameters from the terminal
		
		if(fork() != 0){
			wait(NULL);
		}
		//create a child
		else{
		//execute the child
			strcpy(cmd, "/bin/");	//copy the bin directory in cmp
			strcat(cmd, command);	//concatenate the command entered to cmd
			execve(cmd, par, envp);	//execute command with parameters
		}
		if(strcmp(command,"exit") == 0){
			//if command exit, then break loop
			break;
		}
	}
	
	return 0;
}
