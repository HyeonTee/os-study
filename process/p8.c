#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fds[2];  // 파이프의 파일 디스크립터 배열: pipe_fds[0] = 읽기, pipe_fds[1] = 쓰기
    if (pipe(pipe_fds) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // 첫 번째 자식 프로세스 생성 (파이프에 쓰기)
    int rc1 = fork();
    if (rc1 < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc1 == 0) {
        // 자식 1: 파이프의 쓰기 끝에 데이터를 보냄
        close(pipe_fds[0]);  // 읽기 끝을 닫음 (사용하지 않음)
        dup2(pipe_fds[1], STDOUT_FILENO);  // 파이프의 쓰기 끝을 표준 출력으로 연결
        close(pipe_fds[1]);  // 쓰기 끝을 닫음 (dup2로 복사되었으므로 필요 없음)

        // 데이터 출력 (파이프를 통해 다른 자식 프로세스에 전달됨)
        printf("This is message from child 1\n");
        exit(0);
    }

    // 두 번째 자식 프로세스 생성 (파이프로부터 읽기)
    int rc2 = fork();
    if (rc2 < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc2 == 0) {
        // 자식 2: 파이프에서 데이터를 읽음
        close(pipe_fds[1]);  // 쓰기 끝을 닫음 (사용하지 않음)
        dup2(pipe_fds[0], STDIN_FILENO);  // 파이프의 읽기 끝을 표준 입력으로 연결
        close(pipe_fds[0]);  // 읽기 끝을 닫음 (dup2로 복사되었으므로 필요 없음)

        // 표준 입력에서 데이터를 읽어 출력
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Child 2 received: %s", buffer);
        }
        exit(0);
    }

    // 부모 프로세스: 자식 프로세스가 종료될 때까지 기다림
    close(pipe_fds[0]);  // 부모는 파이프를 사용하지 않으므로 닫음
    close(pipe_fds[1]);
    wait(NULL);  // 자식 1 종료 대기
    wait(NULL);  // 자식 2 종료 대기

    return 0;
}
