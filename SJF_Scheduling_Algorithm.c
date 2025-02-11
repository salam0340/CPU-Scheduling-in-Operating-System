#include <stdio.h>
#include <malloc.h>

void main() {
    int n, i, j, pos, temp, *bt, *wt, *tat, *p;
    float avgwt = 0, avgtat = 0;

    // Taking input for the number of processes
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);

    // Dynamically allocate memory for arrays
    p = (int*)malloc(n * sizeof(int));   // Process IDs
    bt = (int*)malloc(n * sizeof(int));  // Burst Time
    wt = (int*)malloc(n * sizeof(int));  // Waiting Time
    tat = (int*)malloc(n * sizeof(int)); // Turnaround Time

    // Taking input for Burst Time of each process
    printf("\n Enter the burst time for each process \n");
    for (i = 0; i < n; i++) {
        printf(" Burst time for P%d : ", i);
        scanf("%d", &bt[i]);
        p[i] = i; // Assigning process number
    }

    // Sorting processes based on Burst Time using Selection Sort
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) { // Select the process with the shortest burst time
                pos = j;
            }
        }
        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process numbers accordingly
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculating Waiting Time and Turnaround Time
    wt[0] = 0;          // First process has 0 waiting time
    tat[0] = bt[0];     // First process turnaround time = burst time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting Time = Sum of previous burst times
        tat[i] = wt[i] + bt[i];        // Turnaround Time = Waiting Time + Burst Time
    }

    // Calculate Total Waiting Time and Turnaround Time for Average Calculation
    for (i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt / n;
    avgtat = avgtat / n;

    // Printing the Process Table
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", p[i], bt[i], wt[i], tat[i]);
    }

    // Printing Average Waiting Time and Turnaround Time
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);

    // Printing the Gantt Chart
    printf("\n GAANT CHART \n");
    printf("---------------\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], p[i], tat[i]);
    }
}
