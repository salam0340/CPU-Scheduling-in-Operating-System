#include <stdio.h>
#include <malloc.h>

void main() {
    int n, i, tempn, count, terminaltime = 0, initialtime, qt, flag = 0;
    int *bt, *wt, *tat, *tempbt;
    float avgwt = 0, avgtat = 0;

    // Taking input for number of processes
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);
    tempn = n; // Temporary variable to track remaining processes

    // Dynamically allocating memory for arrays
    tempbt = (int*)malloc(n * sizeof(int));  // Temporary burst times for processing
    bt = (int*)malloc(n * sizeof(int));      // Burst times
    wt = (int*)malloc(n * sizeof(int));      // Waiting times
    tat = (int*)malloc(n * sizeof(int));     // Turnaround times

    // Taking input for Quantum Time (Time Slice)
    printf("\n Enter the Quantum Time : ");
    scanf("%d", &qt);

    // Taking input for Burst Time of each process
    printf("\n Enter the burst time for each process \n\n");
    for (i = 0; i < n; i++) {
        printf(" Burst time of P%d : ", i);
        scanf("%d", &bt[i]);
        tempbt[i] = bt[i];  // Copy burst times to temp array for manipulation
        terminaltime += bt[i]; // Total burst time (for reference)
    }

    wt[0] = 0;  // First process has 0 waiting time initially

    // Printing Gantt Chart Header
    printf("\n GAANT CHART \n");
    printf("\n-------------\n");

    // Implementing Round Robin Scheduling Algorithm
    for (terminaltime = 0, count = 0; tempn != 0;) {
        initialtime = terminaltime; // Store the current time before execution

        // If remaining burst time is less than or equal to quantum and process is still in execution
        if (tempbt[count] <= qt && tempbt[count] > 0) {
            terminaltime += tempbt[count]; // Process completes in this cycle
            tempbt[count] = 0; // Mark process as completed
            wt[count] = terminaltime - bt[count]; // Waiting time = Completion time - Original burst time
            tat[count] = wt[count] + bt[count]; // Turnaround time = Waiting time + Burst time
            flag = 1; // Mark process as completed
        }
        // If remaining burst time is greater than quantum
        else if (tempbt[count] > qt) {
            tempbt[count] -= qt; // Reduce remaining burst time by quantum
            terminaltime += qt; // Move forward in time
        }

        // If process has completely executed
        if (tempbt[count] == 0 && flag == 1) {
            tempn--; // Reduce the number of remaining processes
            flag = 0;
        }

        // Print Gantt Chart only if there is execution
        if (initialtime != terminaltime) {
            printf(" %d\t|| P%d ||\t%d\n", initialtime, count, terminaltime);
        }

        // Move to next process in a circular manner
        if (count == n - 1)
            count = 0;
        else
            ++count;
    }

    // Printing the Process Table
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", i, bt[i], wt[i], tat[i]);
    }

    // Calculating Average Waiting Time and Turnaround Time
    for (i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt / n;
    avgtat = avgtat / n;

    // Printing Average Waiting Time and Turnaround Time
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
}
