#include "Main.h"

void handler(int sig)
{
    int status;
    pid_t wpid = waitpid(-1, &status, WNOHANG);
    if (wpid > 0 && WIFEXITED(status) == 0)
    {
        fprintf(stderr, "\nProcess with pid: %d exited normally\n", wpid);
    }
    else if (wpid > 0 && WIFSIGNALED(status) == 0) {
        fprintf(stderr, "\nProcess with pid: %d interrupted by signal %d\n", wpid, sig);
    }
}