#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];  // 파이프용 파일 디스크립터 배열
    pipe(pipe_fd);   // 파이프 생성

    int rc = fork(); // fork 호출하여 자식 프로세스 생성

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        close(pipe_fd[0]);  // 파이프의 읽기 끝 닫기
        printf("hello\n");
        write(pipe_fd[1], "done", 4);  // 부모에게 완료 신호를 보냄
        close(pipe_fd[1]);  // 파이프의 쓰기 끝 닫기
    } else {
        char buffer[4];
        close(pipe_fd[1]);  // 파이프의 쓰기 끝 닫기
        read(pipe_fd[0], buffer, 4);  // 자식이 완료되기를 기다림
        printf("goodbye\n");
        close(pipe_fd[0]);  // 파이프의 읽기 끝 닫기
    }

    return 0;
}
