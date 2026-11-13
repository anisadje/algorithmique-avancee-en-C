#include <stdio.h>
#include <stdlib.h>

/*
 * Circular FIFO queue (graded lab "TER")
 *
 * A FIFO queue stored as a circular linked list. Enqueue and
 * dequeue both run in constant time O(1).
 *
 * The time complexity of each function is given.
 */

// -------------------- Structures --------------------
typedef struct Block {
    int value;
    struct Block *next;
} Block;

typedef Block *Queue;  // points to the LAST element of the queue

// -------------------- Functions --------------------

/*
 * @brief Adds an element at the end of the queue (enqueue)
 * @param x Value to insert
 * @param Q_ptr Address of the pointer to the last element
 * Complexity: O(1)
 */
void enqueue(int x, Queue *Q_ptr){
    Queue Q = *Q_ptr;
    Block *N = (Block *)malloc(sizeof(Block));

    if (N == NULL){
        perror("Allocation error in enqueue");
        exit(EXIT_FAILURE);
    }
    N->value = x;

    if (Q == NULL){
        // empty queue: N points to itself
        N->next = N;
    } else {
        // non-empty queue: insert after the last cell
        N->next = Q->next; // N points to the head
        Q->next = N;       // the old last cell points to N
    }
    *Q_ptr = N; // N becomes the last element
}

/*
 * @brief Removes the element at the head of the queue (dequeue)
 * @param x Pointer where the removed value is stored
 * @param Q_ptr Address of the pointer to the last element
 * Complexity: O(1)
 */
void dequeue(int *x, Queue *Q_ptr){
    Queue Q = *Q_ptr;

    if (Q == NULL){
        fprintf(stderr, "Error: dequeue on an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    // head of the queue
    Block *H = Q->next;
    *x = H->value;

    if (Q == H){
        // only one element
        *Q_ptr = NULL;
    } else {
        // several elements: the last cell now points to the new head
        Q->next = H->next;
    }
    free(H);
}

/*
 * @brief Prints every element of the queue without changing it
 * @param Q The last element of the queue
 * Complexity: O(n)
 */
void printQueue(Queue Q){
    if (Q == NULL){
        printf("Empty queue\n");
        return;
    }
    Block *current = Q->next; // head
    do {
        printf("%d ", current->value);
        current = current->next;
    } while (current != Q->next);
    printf("\n");
}

// -------------------- Tests --------------------
int main(){
    Queue queue = NULL;
    int out;

    printf("Enqueue 10, 20, 30\n");
    enqueue(10, &queue);
    enqueue(20, &queue);
    enqueue(30, &queue);

    printf("Queue: ");
    printQueue(queue);

    dequeue(&out, &queue);
    printf("Dequeued: %d\n", out);
    dequeue(&out, &queue);
    printf("Dequeued: %d\n", out);

    printf("Final queue: ");
    printQueue(queue);

    // Free what is left
    while (queue != NULL){
        dequeue(&out, &queue);
    }

    return 0;
}
