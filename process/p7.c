#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        printf("Child process: About to close STDOUT\n");
        close(STDOUT_FILENO);
        printf("Child process: This message will not be printed\n");
    } else {
        printf("Parent process: Waiting for child to finish\n");
        sleep(1);
        printf("Parent process: Finished\n");
    }
    return 0;
}
