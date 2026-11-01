
#include <stdio.h>
#include <string.h>

#define MAX 100

char queue[MAX][50];
int front = 0, rear = -1, count = 0;

// Function to add an order
void enqueue(int m)
{
    char order[50];

    if (count == m)
    {
        printf("\nQueue is full. Cannot accept more orders.\n");
        return;
    }

    // Shift elements if rear reaches the last position
    if (rear == m - 1)
    {
        for (int i = 0; i < count; i++)
        {
            strcpy(queue[i], queue[front + i]);
        }

        front = 0;
        rear = count - 1;
    }

    printf("Enter pizza order: ");
    scanf(" %49[^\n]", order);

    rear++;
    strcpy(queue[rear], order);
    count++;

    printf("Order added successfully.\n");
}

// Function to serve an order
void dequeue()
{
    if (count == 0)
    {
        printf("\nQueue is empty. No orders to serve.\n");
        return;
    }

    printf("\nOrder served: %s\n", queue[front]);

    front++;
    count--;

    if (count == 0)
    {
        front = 0;
        rear = -1;
    }
}

// Function to display the queue
void display()
{
    if (count == 0)
    {
        printf("\nQueue is empty.\n");
        return;
    }

    printf("\nCurrent Pizza Orders:\n");

    for (int i = front; i <= rear; i++)
    {
        printf("%s\n", queue[i]);
    }

    printf("Total pending orders: %d\n", count);
}

// Main function
int main()
{
    int m, choice;

    printf("Enter maximum number of orders: ");
    scanf("%d", &m);

    if (m <= 0 || m > MAX)
    {
        printf("Invalid queue size.\n");
        return 0;
    }

    do
    {
        printf("\n--- PIZZA PARLOR QUEUE ---\n");
        printf("1. Add Order (Enqueue)\n");
        printf("2. Serve Order (Dequeue)\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enqueue(m);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("\nExiting Pizza Parlor System.\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
