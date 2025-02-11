#include <stdio.h>

int main() {
    int capacity, n, faults = 0, front = 0;
    
    // Taking input for the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    for (int i = 0; i < capacity; i++) 
        frames[i] = -1;  // Initializing frames with -1 (empty)

    // Taking input for the reference string
    printf("Enter the number of reference string elements: ");
    scanf("%d", &n);
    
    printf("Enter the reference string: ");
    int reference[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &reference[i]);

    // Printing the table header
    printf("\nString | Frames            Fault\n");
    printf("-------------------------------\n");

    // Implementing FIFO Page Replacement
    for (int i = 0; i < n; i++) {
        int found = 0;

        // Checking if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == reference[i]) {
                found = 1;
                break;
            }
        }

        // If the page is not found, replace the oldest page (FIFO logic)
        if (!found) {
            frames[front] = reference[i];  // Replace page at the front index
            front = (front + 1) % capacity; // Move front to next position circularly
            faults++;  // Increase page fault count
        }

        // Printing the reference string, frames, and fault status
        printf("   %d  | ", reference[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) 
                printf("%d ", frames[j]);
            else 
                printf("  ");  // Print spaces for empty frames
        }
        printf("\t\t%s\n", found ? "No" : "Yes");
    }

    // Calculating and displaying the fault rate
    float faultRate = ((float)faults / n) * 100;
    printf("\nTotal Requests: %d\n", n);
    printf("Total Page Faults: %d\n", faults);
    printf("Fault Rate: %.2f%%\n", faultRate);

    return 0;
}
