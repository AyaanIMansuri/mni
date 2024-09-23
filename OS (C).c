#include<stdio.h>
#include<stdlib.h>

#define MAX 100

// Structure to represent a process
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function prototypes
void findWaitingTime(Process proc[], int n, int waiting_time[]);
void findTurnAroundTime(Process proc[], int n, int waiting_time[], int turnaround_time[]);
void findavgTime(Process proc[], int n);

int main() {
    int n; // Number of processes

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[MAX];
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
    }

    findavgTime(proc, n);

    return 0;
}

// Function to find waiting time of all processes
void findWaitingTime(Process proc[], int n, int waiting_time[]) {
    int remaining_processes = n;
    int current_time = 0;
    int min_remaining_time;
    int shortest = 0;
    int completion_time;

    while (remaining_processes > 0) {
        min_remaining_time = 99999;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time < min_remaining_time && proc[i].remaining_time > 0) {
                min_remaining_time = proc[i].remaining_time;
                shortest = i;
            }
        }

        if (min_remaining_time == 99999) {
            current_time++;
            continue;
        }

        proc[shortest].remaining_time--;
        min_remaining_time = proc[shortest].remaining_time;

        if (proc[shortest].remaining_time == 0) {
            remaining_processes--;
            completion_time = current_time + 1;
            waiting_time[shortest] = completion_time - proc[shortest].burst_time - proc[shortest].arrival_time;
            proc[shortest].turnaround_time = completion_time - proc[shortest].arrival_time;
        }

        current_time++;
    }
}

// Function to find turn around time
void findTurnAroundTime(Process proc[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = proc[i].burst_time + waiting_time[i];
    }
}

// Function to calculate average time
void findavgTime(Process proc[], int n) {
    int waiting_time[MAX], turnaround_time[MAX];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, waiting_time);
    findTurnAroundTime(proc, n, waiting_time, turnaround_time);

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_tat / n);
}