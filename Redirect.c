#include "Main.h"

void execRedir1(char **parsed)
{
	//printf("-1\n");
    char *args[10];

    int i; 
  
    for (i = 0; i < 10; i++) { 
        args[i] = strsep(&parsed[0], " ");
  
        if (args[i] == NULL) 
            break; 
        if (strlen(args[i]) == 0) 
            i--; 
    } 
   
    int in, output;

    output = open(parsed[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);

    pid_t pid = fork(); 
 
    if (pid == -1) {
        return;
    } else if (pid == 0) {
    	/*int orig_stdout = dup2(1,stdout);
    	int ret_dup = dup2(output, STDOUT_FILENO);
    	int restore_stdin = dup2(stdout,1);
    	close(stdout);
    	close(output);*/
    	dup2(output, 1);
    	close(output);	

        if (execvp(args[0], args) < 0) {
            perror("exec");
        }
        exit(0);
    } else {
          wait(NULL); 
    }
  
}

void execRedir2(char **parsed)
{
	printf("-2\n");
    char *args[10];

    int i; 
  
    for (i = 0; i < 10; i++) { 
        args[i] = strsep(&parsed[0], " ");
  
        if (args[i] == NULL) 
            break; 
        if (strlen(args[i]) == 0) 
            i--; 
    } 
   
    int input, output;
    //printf("1%s23%s4\n", parsed[1],args[0]);
   	input = open(parsed[1], O_RDONLY);

    pid_t pid = fork(); 
 
    if (pid == -1) {
        return;
    } else if (pid == 0) {
    	
    	dup2(input, 0);
    	close(input);	

        if (execvp(args[0], args) < 0) {
            perror("exec");
        }
        exit(0);
    } else {
          wait(NULL); 
    }
  
}

void execRedir3(char **parsedArgs,char *parsed[])
{
	printf("-3\n");
    char *args[10];

    int i; 
  
    for (i = 0; i < 10; i++) { 
        args[i] = strsep(&parsed[0], " ");
  
        if (args[i] == NULL) 
            break; 
        if (strlen(args[i]) == 0) 
            i--; 
    } 
   
    int input, output;
    //printf("1%s2s\n", parsed[1]);
   	input = open(parsed[1], O_RDONLY);
   	output = open(parsedArgs[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);

    pid_t pid = fork(); 
 
    if (pid == -1) {
        return;
    } else if (pid == 0) {
    	
    	dup2(input, 0);
    	dup2(output, 1);
    	close(output);
    	close(input);	

        if (execvp(args[0], args) < 0) {
            perror("exec");
        }
        exit(0);
    } else {
          wait(NULL); 
    }
  
}