#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_INTS 100000

int main() {
    int arr[NUM_INTS];
    FILE *file;
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM_INTS; i++) {
        arr[i] = rand() % 1000000;
    }

    // Open the file for writing
    file = fopen("random_ints.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the integers to the file
    for (i = 0; i < NUM_INTS; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    // Close the file
    fclose(file);

    printf("Random integers saved to random_ints.txt\n");

    return 0;
}
