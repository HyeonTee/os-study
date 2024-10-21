#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        // 자식 프로세스에서 execl 호출
        execl("/bin/ls", "ls", "-l", (char *)NULL);  // 인자들은 개별적으로 전달됨
        perror("execl failed");
    } else {
        // 부모 프로세스
        wait(NULL);
    }
    return 0;
}
