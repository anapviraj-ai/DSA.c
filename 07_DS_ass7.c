
#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

/* Add Order - Enqueue */
void enqueue()
{
    int order;

    if(rear == MAX - 1)
    {
        printf("\nQueue Overflow! Cannot accept more orders.\n");
        return;
    }

    printf("\nEnter Order Number: ");
    scanf("%d", &order);

    if(front == -1)
        front = 0;

    rear++;
    queue[rear] = order;

    printf("Order %d added to the queue successfully.\n", order);
}

/* Serve Order - Dequeue */
void dequeue()
{
    if(front == -1 || front > rear)
    {
        printf("\nQueue Underflow! No orders to serve.\n");
        return;
    }

    printf("\nOrder %d has been served.\n", queue[front]);

    front++;

    if(front > rear)
    {
        front = -1;
        rear = -1;
    }
}

/* Display Queue */
void display()
{
    int i;

    if(front == -1)
    {
        printf("\nQueue is empty. No pending orders.\n");
        return;
    }

    printf("\nCurrent Orders in Queue:\n");

    for(i = front; i <= rear; i++)
    {
        printf("Order %d", queue[i]);

        if(i == front)
            printf(" <- FRONT");

        if(i == rear)
            printf(" <- REAR");

        printf("\n");
    }
}

/* Main Function */
int main()
{
    int choice;

    printf("\nPIZZA PARLOR JOB QUEUE SIMULATION\n");

    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Add Order (Enqueue)\n");
        printf("2. Serve Order (Dequeue)\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 4);

    return 0;
}
