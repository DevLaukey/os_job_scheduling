#include <stdio.h>

#define MAX 200

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int w_time;
    int t_time;
} Process;

void print_gantt_chart(Process p[], int n);

int main()
{
    Process p[MAX];
    int i, j;
    int n = 7;
    int sum_w_time = 0, sum_t_time;

    // Input data from the provided table
    int arrival_times[] = {0, 1, 3, 4, 6, 7, 8};
    int burst_times[] = {10, 8, 14, 7, 5, 4, 6};

    // Initialize processes
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        p[i].arrival_time = arrival_times[i];
        p[i].burst_time = burst_times[i];
        p[i].w_time = p[i].t_time = 0;
    }

    // Sort processes based on burst time (Shortest Job First)
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].burst_time > p[j].burst_time)
            {
                // Swap processes
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    p[0].start_time = p[0].arrival_time;
    for (i = 1; i < n; i++)
    {
        p[i].start_time = p[i - 1].start_time + p[i - 1].burst_time;
        p[i].w_time = p[i].start_time - p[i].arrival_time;
        p[i].t_time = p[i].w_time + p[i].burst_time;
    }

    // Calculate total waiting time and total turnaround time
    for (i = 0; i < n; i++)
    {
        sum_w_time += p[i].w_time;
        sum_t_time += p[i].t_time;
    }

    // Print results
    puts(""); // Empty Line
    printf("Total Waiting Time      : %-2d\n", sum_w_time);
    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_w_time / (double)n);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_t_time / (double)n);

    // Print Gantt chart
    puts(""); // Empty line
    puts("          GANTT CHART          ");
    puts("          ***********          ");
    print_gantt_chart(p, n);
    return 0;
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
        if (p[i].t_time > 9)
            printf("\b");
        printf("%d", p[i].t_time);
    }
    printf("\n");
    getchar();
}
