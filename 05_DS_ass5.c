
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define SEATS 7

// Structure of a Doubly Linked List node
struct Node {
    int seat_num;
    int status;
    struct Node *prev;
    struct Node *next;
};

// Create linked list for each row
struct Node* create_row() {
    struct Node *head = NULL;
    struct Node *temp = NULL;

    for (int i = 1; i <= SEATS; i++) {
        struct Node *newNode =
            (struct Node*)malloc(sizeof(struct Node));

        newNode->seat_num = i;
        newNode->status = -1;  // -1 means empty
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            temp = newNode;
        } else {
            temp->next = newNode;
            newNode->prev = temp;
            temp = newNode;
        }
    }

    return head;
}

// Find a particular seat
struct Node* find_seat(struct Node *head, int seat) {
    struct Node *temp = head;

    while (temp != NULL) {
        if (temp->seat_num == seat) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

// Randomly book some seats initially
void randomly_book_seats(struct Node *head) {
    int count = (rand() % 3) + 1;
    int booked = 0;

    while (booked < count) {
        int seat = (rand() % SEATS) + 1;
        struct Node *temp = find_seat(head, seat);

        if (temp->status == -1) {
            temp->status = 1;
            booked++;
        }
    }
}

// Display all seats and available seats
void display_seats(struct Node *heads[]) {
    printf("\n========== CINEMAX THEATER ==========\n");

    for (int i = 0; i < ROWS; i++) {
        struct Node *temp = heads[i];

        printf("\nRow %d: ", i + 1);

        while (temp != NULL) {
            if (temp->status == 1)
                printf(" B ");
            else
                printf(" - ");

            temp = temp->next;
        }

        printf("\nAvailable seats: ");

        temp = heads[i];

        while (temp != NULL) {
            if (temp->status == -1)
                printf("%d ", temp->seat_num);

            temp = temp->next;
        }
    }

    printf("\n\nB = Booked | - = Empty\n");
}

// Book a specific seat
void book_seat(struct Node *heads[]) {
    int row, seat;

    printf("\nEnter row number (1-10): ");
    scanf("%d", &row);

    printf("Enter seat number (1-7): ");
    scanf("%d", &seat);

    if (row < 1 || row > ROWS ||
        seat < 1 || seat > SEATS) {
        printf("\nInvalid row or seat number!\n");
        return;
    }

    struct Node *temp = find_seat(heads[row - 1], seat);

    if (temp->status == -1) {
        temp->status = 1;
        printf("\nSeat booked successfully!\n");
    } else {
        printf("\nSorry! This seat is already booked.\n");
    }
}

// Cancel an existing booking
void cancel_booking(struct Node *heads[]) {
    int row, seat;

    printf("\nEnter row number (1-10): ");
    scanf("%d", &row);

    printf("Enter seat number (1-7): ");
    scanf("%d", &seat);

    if (row < 1 || row > ROWS ||
        seat < 1 || seat > SEATS) {
        printf("\nInvalid row or seat number!\n");
        return;
    }

    struct Node *temp = find_seat(heads[row - 1], seat);

    if (temp->status == 1) {
        temp->status = -1;
        printf("\nBooking cancelled successfully!\n");
    } else {
        printf("\nThis seat is already empty.\n");
    }
}

// Free allocated memory
void free_memory(struct Node *heads[]) {
    for (int i = 0; i < ROWS; i++) {
        struct Node *temp = heads[i];

        while (temp != NULL) {
            struct Node *nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        heads[i] = NULL;
    }
}

// Main function
int main() {
    struct Node *heads[ROWS];

    int choice;

    srand(time(NULL));

    // Initialize linked lists for all rows
    for (int i = 0; i < ROWS; i++) {
        heads[i] = create_row();
        randomly_book_seats(heads[i]);
    }

    printf("\nInitial Seat Layout:\n");
    display_seats(heads);

    // Main menu
    do {
        printf("\n========== CINEMAX MENU ==========\n");
        printf("1. Display Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Booking\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_seats(heads);
                break;

            case 2:
                book_seat(heads);
                break;

            case 3:
                cancel_booking(heads);
                break;

            case 4:
                free_memory(heads);
                printf("\nMemory freed successfully.\n");
                printf("Thank you for using Cinemax!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
