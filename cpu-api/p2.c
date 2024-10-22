#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("file.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        perror("fork failed\n");
        close(fd);
        exit(1);
    } else if (rc == 0) {
        const char *child_message = "Hello from child process!\n";
        write(fd, child_message, strlen(child_message));
        printf("Child process (pid: %d) wrote to file.\n", (int) getpid());
    } else {
        const char *parent_message = "Hello from parent process!\n";
        write(fd, parent_message, strlen(parent_message));
        printf("Parent process (pid: %d) wrote to file.\n", (int) getpid());
    }

    close(fd);

    return 0;
}
