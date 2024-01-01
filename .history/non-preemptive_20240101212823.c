#include <stdio.h>

#define MAX 200
#define AGE_THRESHOLD 5
#define SIMULATION_TIME 200

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
    int priority;
    int age;
} Process;

void print_table(Process p[], int n);
void print_gantt_chart(Process p[], int n);

int main() {
    Process p[MAX];
    int i, j, n;
    int sum_w_time = 0, sum_t_time;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time, arrival time, and priority for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P[%d] - Burst Time: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("       Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("       Priority: ");
        scanf("%d", &p[i].priority);
        p[i].waiting_time = p[i].turnaround_time = 0;
        p[i].age = 0;
    }

    // Sort processes based on priority (higher priority comes first)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].priority < p[j + 1].priority) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;
    for (i = 0; i < n; i++) {
        int execute_time = (p[i].burst_time < SIMULATION_TIME - time) ? p[i].burst_time : SIMULATION_TIME - time;
        p[i].waiting_time = time - p[i].arrival_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;

        time += execute_time;

        // Aging - decrement priority if the process remains in the ready queue for 5 time units
        if (p[i].age >= AGE_THRESHOLD) {
            p[i].priority--;
            p[i].age = 0;
        } else {
            p[i].age++;
        }

        // Update simulation time
        if (time >= SIMULATION_TIME) {
            break;
        }
    }

    for (i = 0; i < n; i++) {
        sum_w_time += p[i].waiting_time;
        sum_t_time += p[i].turnaround_time;
    }

    puts(""); // Empty Line
    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_w_time / (double)n);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_t_time / (double)n);

    // print Gantt chart
    puts(""); // Empty line
    puts("          GANTT CHART          ");
    puts("          ***********          ");
    print_gantt_chart(p, n);

    return 0;
}


void print_gantt_chart(Process p[], int n) {
    int i, j;
    printf(" ");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("  ");
        if (p[i].turnaround_time > 9)
            printf("\b");
        printf("%d", p[i].turnaround_time);
    }
    printf("\n");
    getchar();
}

