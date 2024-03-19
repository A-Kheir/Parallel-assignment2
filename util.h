#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define BUCKET_SIZE 10
#define NUM_INTS 100000
#define NUM_THREADS 8

void load_random_ints(int* arr) {
    FILE* file;
    int i;

    // Open the file for reading
    file = fopen("random_ints.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Read the integers from the file into the array
    for (i = 0; i < NUM_INTS; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    // Close the file
    fclose(file);
}