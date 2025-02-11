#include <stdio.h>

int main() {
    int capacity, n, faults = 0; // Variables: 'capacity' for frames, 'n' for reference string length, 'faults' for page fault count
    
    // Taking input for number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Declaring necessary arrays
    int frames[capacity];       // Stores the pages in memory
    int reference[100];         // Stores the reference string
    int used[capacity];         // Stores the index of the next use of a page (for optimal page replacement)

    // Initializing frame slots to -1 (indicating empty frames)
    for (int i = 0; i < capacity; i++) 
        frames[i] = -1;

    // Taking input for the reference string
    printf("Enter the number of reference string elements: ");
    scanf("%d", &n);
    
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &reference[i]);

    // Printing table header for output
    printf("\nString | Frames            Fault\n");
    printf("-------------------------------\n");

    // Implementing Optimal Page Replacement Algorithm
    for (int i = 0; i < n; i++) {
        int found = 0; // Flag to check if the page is already in memory

        // Checking if the page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == reference[i]) { 
                found = 1;  // Page is already present, so no replacement needed
                break;
            }
        }

        // If the page is not found in frames, a page fault occurs
        if (!found) {
            if (i < capacity) {
                // If there is still space in memory, insert the page into the next available frame
                frames[i] = reference[i];
            } else {
                // Otherwise, find the page that will be used farthest in the future (Optimal Page Replacement)
                
                // Initialize 'used' array to -1, meaning we don't know the next use yet
                for (int j = 0; j < capacity; j++) 
                    used[j] = -1;

                // Check future references to determine the next usage of each page in frames
                for (int j = 0; j < capacity; j++) {
                    for (int k = i + 1; k < n; k++) {
                        if (frames[j] == reference[k]) {
                            used[j] = k; // Store the next occurrence index
                            break;
                        }
                    }
                }

                // Find the page that will be used farthest in the future
                int maxIndex = -1, farthest = -1;
                for (int j = 0; j < capacity; j++) {
                    if (used[j] == -1) {  // If a page is never used again, it should be replaced immediately
                        maxIndex = j;
                        break;
                    } else if (used[j] > farthest) {  // Otherwise, find the page used farthest in the future
                        farthest = used[j];
                        maxIndex = j;
                    }
                }

                // Replace the selected page with the new page
                frames[maxIndex] = reference[i];
            }
            faults++; // Increment the page fault count
        }

        // Printing the current state of memory frames
        printf("   %d  | ", reference[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) 
                printf("%d ", frames[j]); // Print stored pages
            else 
                printf("  ");  // Print empty spaces
        }
        printf("\t\t%s\n", found ? "No" : "Yes"); // Display whether a fault occurred
    }

    // Calculating and displaying the page fault rate
    float faultRate = ((float)faults / n) * 100;
    printf("\nTotal Requests: %d\n", n);
    printf("Total Page Faults: %d\n", faults);
    printf("Fault Rate: %.2f%%\n", faultRate);

    return 0;
}
