#include <sys/utsname.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include <perror.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
 
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")


void printlist(char tmp[],char name[],int l,int file);

void pinfo(char *temp);

int ownCmdHandler(char** parsed,int f);

int parsePipe(char* str, char** strpiped);

void parseSpace(char* str, char** parsed);

int processString(char* str, char** parsed, char** parsedpipe1,char** parsedpipe2,char *args[]);

void execArgs(char** parsed);

void execArgsPiped1(char** parsed, char** parsedpipe);

void execArgsPiped2(char** parsed, char** parsedpipe1,char** parsedpipe2);

void handler(int sig);

void execRedir1(char **parsed);

void execRedir2(char **parsed);

void execRedir3(char **parsedArgs,char *parsed[]);