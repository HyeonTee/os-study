#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define NUM_SWITCHES 100000

double get_time_in_microseconds() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1e6 + time.tv_usec;
}

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer = 'x';
    double start_time, end_time;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스
        for (int i = 0; i < NUM_SWITCHES; i++) {
            // 부모로부터 데이터 받기
            read(pipe1[0], &buffer, 1);
            // 부모에게 데이터 보내기
            write(pipe2[1], &buffer, 1);
        }
        exit(0);
    } else {
        // 부모 프로세스
        start_time = get_time_in_microseconds();  // 시간 측정 시작

        for (int i = 0; i < NUM_SWITCHES; i++) {
            // 자식에게 데이터 보내기
            write(pipe1[1], &buffer, 1);
            // 자식으로부터 데이터 받기
            read(pipe2[0], &buffer, 1);
        }

        end_time = get_time_in_microseconds();  // 시간 측정 종료

        // 문맥 교환 시간 계산 및 출력
        double total_time = end_time - start_time;
        double average_time = total_time / (NUM_SWITCHES * 2); // 두 번의 문맥 교환이 한 세트이므로 *2
        printf("Total time for %d context switches: %.2f microseconds\n", NUM_SWITCHES, total_time);
        printf("Average time per context switch: %.5f microseconds\n", average_time);

        // 자식 프로세스가 종료되길 기다림
        wait(NULL);
    }

    return 0;
}
