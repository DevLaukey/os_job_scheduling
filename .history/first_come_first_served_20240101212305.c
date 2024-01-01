#include <stdio.h>

#define MAX 200

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
} Process;

void print_table(Process p[], int n);
void print_gantt_chart(Process p[], int n);

int main() {
    Process p[MAX];
    int i, j, n;
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
        p[i].waiting_time = p[i].turnaround_time = 0;
    }

    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    p[0].turnaround_time = p[0].burst_time;

    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].turnaround_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }

    for (i = 0; i < n; i++) {
        sum_w_time += p[i].waiting_time;
        sum_t_time += p[i].turnaround_time;
    }

    // print table
    puts(""); // Empty line
    print_table(p, n);
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

void print_table(Process p[], int n) {
    printf("| Process | Arrival Time | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("|---------|---------------|------------|--------------|-----------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|   P%-4d |       %-8d |     %-6d |       %-8d |        %-9d |\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

void print_gantt_chart(Process p[], int n)
{
    int i, j;
    printf(" ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst_time; j++)
            printf("  ");
        if (p[i].turnaround_time > 9)
            printf("\b");
        printf("%d", p[i].turnaround_time);
    }
    printf("\n");
    getchar();
}
