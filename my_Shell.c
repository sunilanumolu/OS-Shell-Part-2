// C Program to design a shell in Linux

#include "Main.h"
 
// Greeting shell during startup
void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: %s", username);
    printf("\n");
    sleep(1);
    clear();
}
 
// Function to take input
int takeInput(char* str)
{
    char* buf;
 
    buf = readline("$ ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
 
// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    char* username = getenv("USER");
    printf("\n%s@Ubuntu:%s", username, cwd);
}

 
int main() 
{ 
    char inputString[MAXCOM], *parsedArgs[MAXLIST], * parsedArgsPiped1[MAXLIST], * parsedArgsPiped2[MAXLIST];
    char *args[10];
    int execFlag = 0; 
    init_shell(); 
  
    while (1) { 
        // print shell line 
        printDir(); 
        // take input 
        if (takeInput(inputString)) 
            continue; 
        // process 
        execFlag = processString(inputString, parsedArgs, parsedArgsPiped1, parsedArgsPiped2, args); 
        // execflag returns zero if there is no command 
        // or it is a builtin command, 
        // 1 if it is a simple command 
        // 2 if it is including a pipe. 
  
        // execute 
        if (execFlag == -1)
            execRedir1(parsedArgs);

        if (execFlag == -2)
            execRedir2(parsedArgs);

        if (execFlag == -3)
            execRedir3(parsedArgs,args);

        if (execFlag == 1) 
            execArgs(parsedArgs); 
  
        if (execFlag == 2) 
            execArgsPiped1(parsedArgs, parsedArgsPiped1);

        if (execFlag == 3)
            execArgsPiped2(parsedArgs, parsedArgsPiped1, parsedArgsPiped2); 
    } 
    return 0; 
} 