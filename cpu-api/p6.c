#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        printf("Hello, I am the child process (pid: %d)\n", (int) getpid());
        sleep(2);
        printf("Child process (pid: %d) exiting\n", (int) getpid());
        exit(0);
    } else {
        int status;
        pid_t child_pid = waitpid(rc, &status, 0);
        printf("Parent process (pid: %d) waited for child (pid: %d)\n", (int) getpid(), child_pid);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit successfully\n");
        }
    }
    return 0;
}
