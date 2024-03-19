#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <pthread.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct {
    struct Node** bucket;
    int bucketIndex;
} BucketSortArgs;

void* insertionSortThread(void* args) {
    BucketSortArgs* bsArgs = (BucketSortArgs*)args;
    insertionSort(bsArgs->bucket);
    return NULL;
}

void insertionSort(struct Node** head) {
    struct Node* sorted = NULL;
    struct Node* current = *head;
    *head = NULL;

    while (current != NULL) {
        struct Node* next = current->next;
        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

void bucketSort(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    struct Node* buckets[BUCKET_SIZE];
    for (int i = 0; i < BUCKET_SIZE; i++) {
        buckets[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] * BUCKET_SIZE) / (maxVal + 1);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = buckets[bucketIndex];
        buckets[bucketIndex] = newNode;
    }

    int k = 0;

    pthread_t threads[BUCKET_SIZE];
    BucketSortArgs args[BUCKET_SIZE];

    for (int i = 0; i < BUCKET_SIZE; i++) {
        args[i].bucket = &buckets[i];
        args[i].bucketIndex = i;
        pthread_create(&threads[i], NULL, insertionSortThread, &args[i]);
    }

    for (int i = 0; i < BUCKET_SIZE; i++) {
        pthread_join(threads[i], NULL);
        struct Node* node = buckets[i];
        while (node != NULL) {
            arr[k++] = node->data;
            struct Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main() {
    int arr[NUM_INTS];
    load_random_ints(arr);
    int n = sizeof(arr) / sizeof(arr[0]);

    clock_t start = clock();
    bucketSort(arr, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by bucketSort(): %.6f seconds\n", time_taken);

    // printf("Sorted array: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    return 0;
}