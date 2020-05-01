#include "Main.h"

// Function where the system command is executed
void execArgs(char** parsed)
{
   // printf("1\n");
    int bg = 0;
    if(parsed[0][strlen(parsed[0])-1] == *"&"){
        bg = 1;
        signal(SIGCHLD,handler);
        parsed[0][strlen(parsed[0])-1] = *"\0";
    }
    // Forking a child
    for(int i=0;i<MAXLIST && parsed[i]!=NULL;i++){
        if(!strcmp(parsed[i],"&")){
            signal(SIGCHLD,handler);
            bg = 1;
        }
    }
    pid_t pid = fork(); 
 
    if (pid == -1) {
        //printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        //printf("child_executing\n");
        if (execvp(parsed[0], parsed) < 0) {
            perror("exec");
        }
        exit(0);
    } else {
        //printf("waiting for child to terminate\n");
        if(bg == 0){
           wait(NULL); 
    }
        return; 
    }
}
 
// Function where the piped system commands is executed 
void execArgsPiped1(char** parsed, char** parsedpipe) 
{    
   // printf("2\n");
    // 0 is read end, 1 is write end 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[0]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            perror("exec"); 
            exit(0); 
        } 
    } else { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[1]); 
            
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                perror("exec"); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children
            close(pipefd[0]);
            close(pipefd[1]);

            wait(NULL); 
            wait(NULL);
            return; 
        } 
    } 
} 

void execArgsPiped2(char** parsed, char** parsedpipe1,char** parsedpipe2) 
{   
    //printf("3\n");  
    // 0 is read end, 1 is write end 
    int pipefd1[2];
    int pipefd2[2];  
    pid_t p1, p2 ,p3; 
  
    if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        dup2(pipefd1[1], STDOUT_FILENO); 
        close(pipefd1[0]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            perror("exec"); 
            exit(0); 
        } 
    } else { 
        
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            dup2(pipefd1[0], STDIN_FILENO); 
            close(pipefd1[1]);

            dup2(pipefd2[1], STDOUT_FILENO); 
            close(pipefd2[0]); 
            
            if (execvp(parsedpipe1[0], parsedpipe1) < 0) { 
                perror("exec"); 
                exit(0); 
            } 
        } else { 
            close(pipefd1[0]);
            close(pipefd1[1]);
            
        p3 = fork(); 
  
        if (p3 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 3 executing.. 
        // It only needs to read at the read end 
        if (p3 == 0) { 
            dup2(pipefd2[0], STDIN_FILENO); 
            close(pipefd2[1]);
            
            if (execvp(parsedpipe2[0], parsedpipe2) < 0) { 
                perror("exec"); 
                exit(0); 
            } 
        } else {
            
            close(pipefd2[0]);
            close(pipefd2[1]);

            wait(NULL); 
            wait(NULL);
            wait(NULL);

            return;
        }

        }
    } 
}    