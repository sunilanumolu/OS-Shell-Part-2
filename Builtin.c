#include "Main.h"

// Help command builtin
void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Sunil"
        "\n-Use the shell at your own risk..."
        "\n>general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");
 
    return;
}

// Function to execute builtin commands
int ownCmdHandler(char** parsed,int f)
{
    int NoOfOwnCmds = 8, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* ListOflsCmds[3];
    char* username;
    char cwd[1024];
    struct dirent *dir;
    DIR *d;
 
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "pwd";
    ListOfOwnCmds[5] = "echo";
    ListOfOwnCmds[6] = "ls";
    ListOfOwnCmds[7] = "pinfo";

    ListOflsCmds[0] = "-a";
    ListOflsCmds[1] = "-l";
    ListOflsCmds[2] = "-la";

    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
 
    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is not a place to play around."
            "\nUse help to know more..\n", username);
        return 1;
    case 5:
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return 1;
    case 6:
        for(i=1; i < MAXLIST && parsed[i] != NULL; i++)
            printf("%s ", parsed[i]);
        printf("\n");
        return 1;
    case 7:
        if (f>0) return 0;  
        if (parsed[1]==NULL){
        d=opendir(".");
        if(d!=NULL){
        while((dir=readdir(d))!=NULL){
          if(dir->d_name[0]!='.'){
            printf("%s\n",dir->d_name);
            }
        }
        }
        else{
            printf("cannot access the contents of the present directory\n");
         }
        }
        else if (strcmp(parsed[1], ListOflsCmds[0] ) == 0){
        d=opendir(".");
        if(d!=NULL){
        while((dir=readdir(d))!=NULL){
            printf("%s\n",dir->d_name);
        }
        }
        else{
            printf("cannot access the contents of the present directory\n");
         }
        }
        else if (strcmp(parsed[1], ListOflsCmds[1] ) == 0){
            d=opendir(".");
            if(d!=NULL){
            while((dir =readdir(d))!=NULL){
            if(dir->d_name[0]!='.'){
            printlist(".",dir->d_name,1,0);
            }
           }
          }
          else{
            printf("cannot access the contents of the present directory\n");
         }
        }
        else if (strcmp(parsed[1], ListOflsCmds[2] ) == 0){
            d=opendir(".");
            if(d!=NULL){
            while((dir =readdir(d))!=NULL){
            printlist(".",dir->d_name,1,0);
           }
          }
          else{
            printf("cannot access the contents of the present directory\n");
         }
        }
        return 1;
        case 8:
             if(parsed[1] == NULL){
            char *temp = (char *)malloc(100 * sizeof(char));
            sprintf(temp, "%d", getpid());
            pinfo(temp);
        }
        else {
            pinfo(parsed[1]);
        }
        return 1;
    default:
        break;
    }
 
    return 0;
}
