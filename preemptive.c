#include <stdio.h>

#define MAX 200
#define AGE_THRESHOLD 5

typedef struct
{
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
    int priority;
    int age;
} Process;

void print_table(Process p[], int n);
void print_gantt_chart(Process p[], int n);

int main()
{
    Process p[MAX];
    int i, j, n, time = 0;
    int sum_w_time = 0, sum_t_time;

    // Define the number of processes and initialize process values
    n = 7; // Number of processes
    int burst_times[] = {10, 8, 14, 7, 5, 4, 6};
    int arrival_times[] = {0, 1, 3, 4, 6, 7, 8};
    int priorities[] = {2, 4, 6, 8, 3, 6, 9};

    // Initialize processes
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        p[i].burst_time = burst_times[i];
        p[i].arrival_time = arrival_times[i];
        p[i].priority = priorities[i];
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = p[i].turnaround_time = 0;
        p[i].age = 0;
    }

    int remaining_processes = n;
    while (remaining_processes > 0)
    {
        int highest_priority = -1;
        int selected_process = -1;

        for (i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].priority > highest_priority)
            {
                highest_priority = p[i].priority;
                selected_process = i;
            }
        }

        if (selected_process != -1)
        {
            int execute_time = 1; // Execute one time unit
            p[selected_process].remaining_time -= execute_time;
            time += execute_time;

            if (p[selected_process].remaining_time == 0)
            {
                remaining_processes--;
                p[selected_process].turnaround_time = time - p[selected_process].arrival_time;
                p[selected_process].waiting_time = p[selected_process].turnaround_time - p[selected_process].burst_time;
            }

            // Aging - decrement priority if the process remains in the ready queue for 5 time units
            if (p[selected_process].age >= AGE_THRESHOLD)
            {
                p[selected_process].priority--;
                p[selected_process].age = 0;
            }
            else
            {
                p[selected_process].age++;
            }
        }
        else
        {
            // No process is ready, just increment time
            time++;
        }
    }

    for (i = 0; i < n; i++)
    {
        sum_w_time += p[i].waiting_time;
        sum_t_time += p[i].turnaround_time;
    }

    // print table
    
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

