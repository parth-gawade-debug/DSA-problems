#include <stdio.h>
#include <string.h>

void enque(int job_id, char job_title[10]);
void dequeue();
void displayqueue();
int isempty();

struct jobs {
    int job_id;
    char job_title[10];
};

struct jobs queue[15];
int front = -1;
int rear = -1;

int main() {
    int choice;
    int job_id;
    char job_title[10];

    while (1) {
        printf("\n---Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter a number from 1-4: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter your job id and job title  ");
                scanf("%d %s", &job_id, job_title);
                enque(job_id, job_title);
                displayqueue();
                break;
            case 2:
                dequeue();
                displayqueue();
                break;
            case 3:
                displayqueue();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }
}

void enque(int job_id, char job_title[10]) {
    if (rear >= 14) {
        printf("Queue is full!\n");
    } else {
        rear++;
        queue[rear].job_id = job_id;
        strcpy(queue[rear].job_title, job_title);
        printf("Inserted successfully.\n");
    }
}

void dequeue() {
    if (isempty()) {
        printf("Queue is empty!\n");
    } else {
        printf("Dequeued job id: %d, job title: %s\n", queue[front + 1].job_id, queue[front + 1].job_title);
        front++;
    }
}

void displayqueue() {
    if (isempty()) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue contents:\n");
        for (int i = front + 1; i <= rear; i++) {
            printf("Job ID: %d, Job Title: %s\n", queue[i].job_id, queue[i].job_title);
        }
    }
}

int isempty() {
    if (front == rear) {
        return 1;
    } else {
        return 0;
    }
}