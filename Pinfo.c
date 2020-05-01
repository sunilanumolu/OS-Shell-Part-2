#include "Main.h"

void pinfo(char *temp){
    FILE *fd;
    char add[100] = "/proc/", text[10000],exe[100],state,size[10],extra_arr[100] = "a";
    printf("Pid -- %d\n",getpid());
    strcat(add,temp);
    strcpy(exe,add);
    strcat(exe,"/exe");
    strcat(add,"/status");
    fd = fopen(add, "r");
    while(fgets(text,100,fd)){
        if(text[0] == *"S" && text[1] == *"t" && text[2] == *"a" && text[3] == *"t" && text[4] == *"e")printf("Process Status -- %c\n",text[7]);
        if(text[0] == *"V" && text[1] == *"m" && text[2] == *"S" && text[3] == *"i" && text[4] == *"z" && text[5] == *"e")
        {
            for(int i=0;i<10;i++)size[i] = text[11+i];
            printf("Memory -- %s",size);
        }
    }
    printf("Executable -- ");
    int ret = readlink(exe,extra_arr,100);
    printf("%s\n",extra_arr);
}
