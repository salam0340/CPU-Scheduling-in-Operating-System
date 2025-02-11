#include <stdio.h>
#include <malloc.h>

void main() {
    int n, i, j, pos, temp, *bt, *wt, *tat, *p, *pt; 
    float avgwt = 0, avgtat = 0; // Variables to store average waiting time and turnaround time

    // Taking input for the number of processes
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);

    // Dynamically allocating memory for process attributes
    p = (int*)malloc(n * sizeof(int));    // Process IDs
    bt = (int*)malloc(n * sizeof(int));   // Burst times
    wt = (int*)malloc(n * sizeof(int));   // Waiting times
    tat = (int*)malloc(n * sizeof(int));  // Turnaround times
    pt = (int*)malloc(n * sizeof(int));   // Priorities

    // Taking input for burst times and priority levels of each process
    printf("\n Enter the burst time and priority for each process ");
    for (i = 0; i < n; i++) {
        printf("\n Burst time of P%d : ", i);
        scanf("%d", &bt[i]);
        printf(" Priority of P%d : ", i);
        scanf("%d", &pt[i]);
        p[i] = i;  // Assign process ID
    }

    // Sorting processes based on priority using Selection Sort (Lower value = Higher priority)
    for (i = 0; i < n; i++) {
        pos = i; // Assume current process has the highest priority
        for (j = i + 1; j < n; j++) {
            if (pt[j] < pt[pos]) { // Find process with highest priority (smallest number)
                pos = j;
            }
        }
        
        // Swap priority values
        temp = pt[i];
        pt[i] = pt[pos];
        pt[pos] = temp;

        // Swap burst time values accordingly
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process IDs accordingly
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculating Waiting Time and Turnaround Time
    wt[0] = 0;        // First process has no waiting time
    tat[0] = bt[0];   // Turnaround time for the first process is equal to its burst time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting time of current process = waiting time of previous process + burst time of previous process
        tat[i] = wt[i] + bt[i];         // Turnaround time = Waiting time + Burst time
    }

    // Calculating average waiting time and turnaround time
    for (i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt / n;
    avgtat = avgtat / n;

    // Displaying the results
    printf("\n PROCESS \t PRIORITY \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(" P%d \t\t %d \t\t %d \t\t %d \t\t %d \n", p[i], pt[i], bt[i], wt[i], tat[i]);
    }

    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);

    // Displaying the Gantt Chart
    printf("\n GAANT CHART \n");
    printf("---------------\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], p[i], tat[i]);
    }
}
