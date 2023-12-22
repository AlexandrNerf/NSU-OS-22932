#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/syscall.h> 
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int filedesc[2];
    if (pipe(filedesc) == -1) { return 1; }

    pid_t pid = fork();
    if (pid == -1) { return 1; }
    // child
    else if (pid == 0) {
        close(filedesc[1]);

        char c;
        while (read(filedesc[0], &c, 1)) {
            printf("%c", toupper(c));
        }

        close(filedesc[0]);
    }
    // parent
    else {
        close(filedesc[0]);

        char* text = "Example text EXAMPLE TExt and etc.";
        for (char* ptr = text; *ptr != 0; ptr++) {
            write(filedesc[1], ptr, 1);
        }

        close(filedesc[1]);
    }

    return 0;
}