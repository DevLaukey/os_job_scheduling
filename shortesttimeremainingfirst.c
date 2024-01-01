#include <stdio.h>

#define MAX 200
#define INF 9999

typedef struct
{
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
} Process;

void print_table(Process p[], int n);
void print_gantt_chart(Process p[], int n);

int find_shortest_job(Process p[], int n, int time)
{
    int shortest = -1;
    int shortest_time = INF;

    for (int i = 0; i < n; i++)
    {
        if (p[i].remaining_time > 0 && p[i].arrival_time <= time && p[i].remaining_time < shortest_time)
        {
            shortest = i;
            shortest_time = p[i].remaining_time;
        }
    }

    return shortest;
}

int main()
{
    Process p[MAX];
    int i, j;
    int n = 7;
    int sum_w_time = 0, sum_t_time, time = 0;

    // Define the number of processes and initialize process values
    int burst_times[] = {10, 8, 14, 7, 5, 4, 6};
    int arrival_times[] = {0, 1, 3, 4, 6, 7, 8};

    // Initialize processes
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        p[i].burst_time = burst_times[i];
        p[i].arrival_time = arrival_times[i];
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = p[i].turnaround_time = 0;
    }

    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    while (1)
    {
        int shortest_job = find_shortest_job(p, n, time);
        if (shortest_job == -1)
        {
            break;
        }

        p[shortest_job].remaining_time--;

        if (p[shortest_job].remaining_time == 0)
        {
            p[shortest_job].turnaround_time = time + 1 - p[shortest_job].arrival_time;
            p[shortest_job].waiting_time = p[shortest_job].turnaround_time - p[shortest_job].burst_time;
        }

        time++;
    }

    for (i = 0; i < n; i++)
    {
        sum_w_time += p[i].waiting_time;
        sum_t_time += p[i].turnaround_time;
    }

    // print table
    puts(""); // Empty line

    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_w_time / (double)n);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_t_time / (double)n);

    // print Gantt chart
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
        if (p[i].turnaround_time > 9)
            printf("\b");
        printf("%d", p[i].turnaround_time);
    }
    printf("\n");
    getchar();
}
