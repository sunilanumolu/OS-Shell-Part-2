#include "Main.h"

void printlist(char tmp[],char name[],int l,int file){
  struct stat sfile;
  struct passwd *pw;
  struct group *gr;
  char path[1000];
  char Time[1000];
  strcpy(path,tmp);
  if(!file&&path[l-1]!='/'){
    path[l]='/';
    path[l+1]=0;
    strcat(path,name);
    // printf("path is:%s\n",path);
    // printf("hello in printlist\n");
  }
  if(stat(path,&sfile)==0){
    char t[100];
    char perms[11];
    if(S_ISREG(sfile.st_mode)) perms[0]='-';
        else if(S_ISDIR(sfile.st_mode)) perms[0]='d';
        else if(S_ISFIFO(sfile.st_mode)) perms[0]='|';
        else if(S_ISSOCK(sfile.st_mode)) perms[0]='s';
        else if(S_ISCHR(sfile.st_mode)) perms[0]='c';
        else if(S_ISBLK(sfile.st_mode)) perms[0]='b';
        else perms[0]='l';  // S_ISLNK
    perms[1] = (sfile.st_mode & S_IRUSR) ? 'r':'-';
        perms[2] = (sfile.st_mode & S_IWUSR) ? 'w':'-';
        perms[3] = (sfile.st_mode & S_IXUSR) ? 'x':'-';
        perms[4] = (sfile.st_mode & S_IRGRP) ? 'r':'-';
        perms[5] = (sfile.st_mode & S_IWGRP) ? 'w':'-';
        perms[6] = (sfile.st_mode & S_IXGRP) ? 'x':'-';
        perms[7] = (sfile.st_mode & S_IROTH) ? 'r':'-';
        perms[8] = (sfile.st_mode & S_IWOTH) ? 'w':'-';
        perms[9] = (sfile.st_mode & S_IXOTH) ? 'x':'-';
        perms[10] = '\0';
    printf("%s",perms);
    printf(" ");
    printf("%lu ",sfile.st_nlink);
    pw = getpwuid(sfile.st_uid);
    gr = getgrgid(sfile.st_gid);
    printf("%s %s ",pw->pw_name,gr->gr_name);
    printf("%-5ld ",sfile.st_size);
    strcpy(t,ctime(&sfile.st_mtime));
    t[16]='\0';
    printf("%s ",t);
    printf("%s\n",name);
    // fprintf(stderr,"Failed to access the %s file\n",path);
  }
  else
  {
    fprintf(stderr,"Failed to access the %s file\n",path);
  }
  return;
}