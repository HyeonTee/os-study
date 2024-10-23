#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 5

typedef struct Process {
    int id;
    int tickets;
    int burst_time;
    int remaining_time;
} Process;

Process processes[MAX_PROCESSES];
int total_tickets = 0;

int draw_ticket() {
    return rand() % total_tickets;
}

Process* select_process(int ticket) {
    int cumulative_tickets = 0;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        cumulative_tickets += processes[i].tickets;
        if (ticket < cumulative_tickets) {
            return &processes[i];
        }
    }
    return NULL;
}

void create_process(int id, int tickets, int burst_time) {
    processes[id].id = id;
    processes[id].tickets = tickets;
    processes[id].burst_time = burst_time;
    processes[id].remaining_time = burst_time;
    total_tickets += tickets;
}

void lottery_schedule() {
    while (1) {
        int remaining_processes = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (processes[i].remaining_time > 0) {
                remaining_processes++;
            }
        }

        if (remaining_processes == 0) {
            printf("All processes have finished execution.\n");
            break;
        }

        int winning_ticket = draw_ticket();
        Process* selected_process = select_process(winning_ticket);
        if (selected_process->remaining_time > 0) {
            printf("Running process %d (Tickets: %d, Remaining Time: %d)\n", 
                   selected_process->id, selected_process->tickets, selected_process->remaining_time);
            selected_process->remaining_time--;

            if (selected_process->remaining_time == 0) {
                printf("Process %d finished execution.\n", selected_process->id);
            }
        }
    }
}

int main() {
    srand(time(NULL));

    create_process(0, 5, 3);
    create_process(1, 1, 5);
    create_process(2, 2, 4);
    create_process(3, 10, 2);
    create_process(4, 7, 1);

    lottery_schedule();

    return 0;
}
