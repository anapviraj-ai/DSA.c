#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create();
void display();
void insert();
void deleteNode();
void search();

struct node
{
    int prn;
    char design[50];
    char name[50];
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
struct node *temp = NULL;

struct node *createNode(int prn, const char *name, const char *designation)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    strcpy(newNode->design, designation);
    newNode->next = NULL;
    return newNode;
}

int main()
{
    int ch;
    create();

    while (1)
    {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            insert();
            break;
        case 2:
            search();
            break;
        case 3:
            deleteNode();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("\nExiting...");
            exit(0);
        default:
            printf("\nInvalid choice!");
        }
    }

    return 0;
}

void create()
{
    int value;
    char name[50], choice;

    head = NULL;
    tail = NULL;

    printf("Enter PRN for the President: ");
    scanf("%d", &value);
    printf("Enter name for President: ");
    scanf("%s", name);

    head = createNode(value, name, "President");
    tail = head;

    printf("Enter PRN for the Secretary: ");
    scanf("%d", &value);
    printf("Enter name for Secretary: ");
    scanf("%s", name);

    temp = createNode(value, name, "Secretary");
    tail->next = temp;
    tail = temp;

    printf("\nWant to add members (y/n): ");
    scanf(" %c", &choice);

    while (choice == 'y' || choice == 'Y')
    {
        printf("\nEnter PRN for the member: ");
        scanf("%d", &value);
        printf("Enter name for member: ");
        scanf("%s", name);

        struct node *member = createNode(value, name, "Member");
        struct node *curr = head;
        while (curr->next != tail)
        {
            curr = curr->next;
        }

        member->next = tail;
        curr->next = member;

        printf("\nWant to add another member (y/n): ");
        scanf(" %c", &choice);
    }

    printf("\nInitial committee created successfully!\n");
    display();
}

void display()
{
    int i = 1;
    temp = head;

    printf("\nSr.No.\tPRN\tName\t\tDesignation");
    while (temp != NULL)
    {
        printf("\n%d\t%d\t%s\t\t%s", i, temp->prn, temp->name, temp->design);
        temp = temp->next;
        i++;
    }
    printf("\n");
}

void insert()
{
    int choice, value, pos;
    char name[50];
    struct node *newnode, *curr, *prev;

    printf("\n1. Beginning (New President)\n2. End (New Secretary)\n3. Position (New Member)");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nEnter PRN for new President: ");
        scanf("%d", &value);
        printf("Enter name for new President: ");
        scanf("%s", name);

        newnode = createNode(value, name, "President");

        if (head == NULL)
        {
            head = tail = newnode;
        }
        else
        {
            strcpy(head->design, "Member");
            newnode->next = head;
            head = newnode;
        }

        display();
    }
    else if (choice == 2)
    {
        printf("\nEnter PRN for new Secretary: ");
        scanf("%d", &value);
        printf("Enter name for new Secretary: ");
        scanf("%s", name);

        newnode = createNode(value, name, "Secretary");

        if (head == NULL)
        {
            head = tail = newnode;
        }
        else
        {
            if (tail != NULL)
            {
                strcpy(tail->design, "Member");
            }
            tail->next = newnode;
            tail = newnode;
        }

        display();
    }
    else if (choice == 3)
    {
        printf("\nEnter position to insert member: ");
        scanf("%d", &pos);

        if (pos <= 1 || head == NULL)
        {
            printf("\nInvalid position.");
            return;
        }

        printf("\nEnter PRN for member: ");
        scanf("%d", &value);
        printf("Enter name for member: ");
        scanf("%s", name);

        newnode = createNode(value, name, "Member");

        prev = NULL;
        curr = head;
        for (int i = 1; curr != NULL && i < pos; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL)
        {
            printf("\nInvalid position.");
            free(newnode);
            return;
        }

        if (prev == NULL)
        {
            newnode->next = head;
            head = newnode;
        }
        else
        {
            newnode->next = curr;
            prev->next = newnode;
        }

        display();
    }
    else
    {
        printf("\nInvalid choice!");
    }
}

void deleteNode()
{
    int choice, prn;
    struct node *prev, *curr;

    if (head == NULL)
    {
        printf("\nNo committee exists.");
        return;
    }

    printf("\n1. President\n2. Secretary\n3. Member\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        curr = head;
        head = head->next;
        free(curr);

        if (head == NULL)
        {
            tail = NULL;
            printf("\nCommittee empty.\n");
            return;
        }

        strcpy(head->design, "President");
        if (head->next == NULL)
        {
            tail = head;
        }
        display();
    }
    else if (choice == 2)
    {
        if (head == tail)
        {
            free(head);
            head = NULL;
            tail = NULL;
            printf("\nCommittee empty.\n");
            return;
        }

        prev = head;
        while (prev->next != tail)
        {
            prev = prev->next;
        }

        curr = tail;
        prev->next = NULL;
        tail = prev;
        strcpy(tail->design, "Secretary");
        free(curr);
        display();
    }
    else if (choice == 3)
    {
        printf("\nEnter PRN to delete: ");
        scanf("%d", &prn);

        prev = NULL;
        curr = head;

        while (curr != NULL && curr->prn != prn)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL)
        {
            printf("\nMember not found.");
            return;
        }

        if (prev == NULL)
        {
            head = curr->next;
            if (head == NULL)
            {
                tail = NULL;
            }
            free(curr);
        }
        else
        {
            prev->next = curr->next;
            if (curr == tail)
            {
                tail = prev;
                strcpy(tail->design, "Secretary");
            }
            free(curr);
        }

        display();
    }
    else
    {
        printf("\nInvalid choice!");
    }
}

void search()
{
    int prn;
    int found = 0;

    printf("\nEnter PRN to search: ");
    scanf("%d", &prn);

    temp = head;
    while (temp != NULL)
    {
        if (temp->prn == prn)
        {
            printf("\nRecord found:");
            printf("\nPRN: %d\nName: %s\nDesignation: %s\n", temp->prn, temp->name, temp->design);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        printf("\nRecord not found.");
    }
}
