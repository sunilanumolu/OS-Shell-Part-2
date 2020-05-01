#include "Main.h"

int r=0;
// function for finding pipe 
int parsePipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 3; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[2] == NULL && strpiped[1] != NULL) 
        return 1; 
    else if(strpiped[1] == NULL)
        return 0;
    else { 
        return 2; 
    } 
} 
  
// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
 
void parseRedir1(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, ">");

        if(i==1 && parsed[1] != NULL)
             r=1; 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
    
} 

void parseRedir2(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, "<");

        if(i==1 && parsed[1] != NULL)
             r=2; 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
    
}

int processString(char* str, char** parsed, char** parsedpipe1,char** parsedpipe2,char *args[]) 
{ 
    r=0;
    int i;

    char* strpiped[3]; 
    int piped = 0; 
  
    piped = parsePipe(str, strpiped); 
  
    if (piped > 0) { 
        parseSpace(strpiped[0], parsed); 
        parseSpace(strpiped[1], parsedpipe1);
        if(piped == 2) {
        parseSpace(strpiped[2], parsedpipe2);
        } 

    } else {

        parseRedir1(str, parsed);
        if (r == 1)
        {
            for (i = 0; i < MAXLIST; i++) { 
                args[i] = strsep(&parsed[0], "<");

            if(i==1 && args[1] != NULL)
                r=3; 
  
            if (args[i] == NULL) 
                break; 
            if (strlen(args[i]) == 0) 
                i--; 
        } 
        }
        if( r == 0 )
            parseRedir2(str, parsed);
        if(r == 0) 
             parseSpace(str, parsed); 
    } 
    
    if(r == 0){
    if (ownCmdHandler(parsed, piped)) 
        return 0; 
    else
        return 1 + piped;
    }
    else if(r == 1){
        return -1;
    }else if(r == 2){
        return -2;
    }else if( r == 3){
        return -3;
    }
} 