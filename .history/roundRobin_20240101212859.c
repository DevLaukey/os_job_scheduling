#include <stdio.h>

#define MAX 200

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
} Process;

void print_gantt_chart(Process p[], int n);

int main() {
    Process p[MAX];
    int i, j, n, time = 0, q = 5;
    int sum_w_time = 0, sum_t_time;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time and arrival time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P[%d] - Burst Time: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("       Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = p[i].turnaround_time = 0;
    }


    int remaining_processes = n;
    while (remaining_processes > 0) {
        for (i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                int execute_time = (p[i].remaining_time < q) ? p[i].remaining_time : q;
                p[i].remaining_time -= execute_time;
                time += execute_time;


                if (p[i].remaining_time == 0) {
                    remaining_processes--;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                } else {
                }
            }
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
    getch();
}
