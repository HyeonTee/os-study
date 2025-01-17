#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define QUEUE_LEVELS 3

typedef struct Process {
    int id;
    int burst_time;
    int remaining_time;
} Process;

typedef struct Queue {
    Process* processes[MAX_PROCESSES];
    int front;
    int rear;
    int time_quantum;
} Queue;

Queue queues[QUEUE_LEVELS];

void initialize_queue(Queue* queue, int time_quantum) {
    queue->front = 0;
    queue->rear = 0;
    queue->time_quantum = time_quantum;
}

void enqueue(Queue* queue, Process* process) {
    if (queue->rear < MAX_PROCESSES) {
        queue->processes[queue->rear] = process;
        queue->rear++;
    }
}

Process* dequeue(Queue* queue) {
    if (queue->front < queue->rear) {
        return queue->processes[queue->front++];
    }
    return NULL;
}

bool is_empty(Queue* queue) {
    return queue->front == queue->rear;
}

Process* create_process(int id, int burst_time) {
    Process* process = (Process*)malloc(sizeof(Process));
    process->id = id;
    process->burst_time = burst_time;
    process->remaining_time = burst_time;
    return process;
}

void mlfq_schedule() {
    while (true) {
        bool all_queues_empty = true;

        for (int i = 0; i < QUEUE_LEVELS; i++) {
            Queue* queue = &queues[i];

            if (!is_empty(queue)) {
                all_queues_empty = false;
                Process* process = dequeue(queue);

                int time_slice = (process->remaining_time < queue->time_quantum) ? process->remaining_time : queue->time_quantum;
                printf("Running process %d from queue %d for %d time units\n", process->id, i, time_slice);
                process->remaining_time -= time_slice;

                // 시간이 남아있으면 다음 큐로 이동
                if (process->remaining_time > 0) {
                    if (i + 1 < QUEUE_LEVELS) {
                        enqueue(&queues[i + 1], process);  // 다음 낮은 우선순위 큐로 이동
                    } else {
                        enqueue(&queues[i], process);  // 마지막 큐에 그대로 둠
                    }
                } else {
                    printf("Process %d finished execution\n", process->id);
                    free(process);  // 작업이 완료되었으면 메모리 해제
                }
            }
        }

        if (all_queues_empty) {
            printf("All processes finished execution\n");
            break;
        }
    }
}

int main() {
    initialize_queue(&queues[0], 2);
    initialize_queue(&queues[1], 4);
    initialize_queue(&queues[2], 8);

    enqueue(&queues[0], create_process(1, 10));
    enqueue(&queues[0], create_process(2, 5));
    enqueue(&queues[0], create_process(3, 8));

    mlfq_schedule();

    return 0;
}
