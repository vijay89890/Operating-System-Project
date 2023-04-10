#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int front, rear;
    int items[MAX_QUEUE_SIZE];
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

int isQueueFull(Queue *q) {
    return q->rear == MAX_QUEUE_SIZE - 1;
}

void enqueue(Queue *q, int item) {
    if (isQueueFull(q)) {
        printf("Queue is full\n");
        exit(1);
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = item;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        exit(1);
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

int main() {
    Queue studentQueue, teacherQueue;
    initQueue(&studentQueue);
    initQueue(&teacherQueue);

    int cpuFree = 1;
    int currentPerson = -1;

    while (1) {
        int choice;
        printf("Enter 1 for student, 2 for teacher, 3 to exit: ");
        scanf("%d", &choice);

        if (choice == 3) {
            break;
        }

        if (choice == 1) {
            enqueue(&studentQueue, choice);
        } else if (choice == 2) {
            if (cpuFree) {
                currentPerson = dequeue(&teacherQueue);
                cpuFree = 0;
            } else {
                enqueue(&teacherQueue, choice);
            }
        } else {
            printf("Invalid choice\n");
        }

        if (!cpuFree && currentPerson == 2 && !isQueueEmpty(&teacherQueue)) {
            // Another teacher has arrived, add them to the front of the teacher's queue
            int nextPerson = dequeue(&teacherQueue);
            enqueue(&teacherQueue, currentPerson);
            currentPerson = nextPerson;
        }

        if (!cpuFree) {
            printf("CPU is processing %s\n", currentPerson == 1 ? "student" : "teacher");
            printf("Enter 1 to release CPU: ");
            scanf("%d", &choice);
            if (choice == 1) {
                cpuFree = 1;
                currentPerson = -1;
            }
        }
    }

    return 0;
}

