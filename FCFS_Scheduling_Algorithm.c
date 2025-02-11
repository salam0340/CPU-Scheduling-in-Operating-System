#include<stdio.h>  // Standard input-output library
#include<malloc.h> // Library for dynamic memory allocation

void main()
{
    int i, n, *bt, *wt, *tat; // Variables and pointers for burst time, waiting time, and turnaround time
    float avgtat = 0, avgwt = 0; // Variables to store average turnaround and waiting times

    // Taking input for the number of processes
    printf("\n Enter the number of processes : ");
    scanf("%d", &n);

    // Dynamically allocating memory for burst time, waiting time, and turnaround time arrays
    bt = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    tat = (int*)malloc(n * sizeof(int));

    // Taking input for burst times of each process
    printf("\n Enter the burst time for each process \n");
    for(i = 0; i < n; i++)
    {
        printf(" Burst time for P%d : ", i);
        scanf("%d", &bt[i]); // Storing burst time for each process
    }

    // First process has 0 waiting time, turnaround time equals its burst time
    wt[0] = 0;
    tat[0] = bt[0];

    // Calculating waiting time and turnaround time for each process
    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting Time of current process = Waiting Time of previous process + Burst Time of previous process
        tat[i] = wt[i] + bt[i];         // Turnaround Time = Waiting Time + Burst Time
    }

    // Calculating total waiting time and turnaround time
    for(i = 0; i < n; i++)
    {
        avgwt += wt[i];  // Summing up all waiting times
        avgtat += tat[i]; // Summing up all turnaround times
    }

    // Calculating average waiting time and average turnaround time
    avgwt = avgwt / n;
    avgtat = avgtat / n;

    // Printing the process details in tabular format
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for(i = 0; i < n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", i, bt[i], wt[i], tat[i]);
    }

    // Printing the average waiting time and turnaround time
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);

    // Displaying Gantt Chart
    printf("\n GAANT CHART \n");
    printf("---------------\n");
    for(i = 0; i < n; i++)
    {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], i, tat[i]);  // Showing process execution order with start and end times
    }
}
