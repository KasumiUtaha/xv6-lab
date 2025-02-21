#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char **argv) {
    int pipefd1[2];
    int pipefd2[2];
    char buf[2];

    if (pipe(pipefd1) == -1) {
        fprintf(2, "Pipe Error!\n");
        exit(1);
    }
    
    if (pipe(pipefd2) == -1) {
        fprintf(2, "Pipe Error!\n");
        exit(1);
    }

    int pid = fork();

    if (pid == 0) {
        close(pipefd1[1]);
        close(pipefd2[0]);
        read(pipefd1[0], buf, sizeof(char));
        if (buf[0] == '0') {
            fprintf(1, "%d: received ping\n", getpid());
        }
        write(pipefd2[1], "0", sizeof(char));
        close(pipefd1[0]);
        close(pipefd2[1]);
    } else {
        close(pipefd1[0]);
        close(pipefd2[1]);
        write(pipefd1[1], "0", sizeof(char));
        read(pipefd2[0], buf, sizeof(char));
        if (buf[0] == '0') {
            fprintf(1, "%d: received pong\n", getpid());
        }
        close(pipefd1[1]);
        close(pipefd2[0]);
    }
    exit(0);
}

