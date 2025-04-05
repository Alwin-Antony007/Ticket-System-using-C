#include <stdio.h>
#include <stdlib.h>

typedef struct SeatNode {
    int seatNumber;
    int isBooked; // 0 = available, 1 = booked
    struct SeatNode *left;
    struct SeatNode *right;
} SeatNode;

// Function to create a new seat node
SeatNode* createSeat(int seatNumber) {
    SeatNode* newSeat = (SeatNode*)malloc(sizeof(SeatNode));
    newSeat->seatNumber = seatNumber;
    newSeat->isBooked = 0; // Initially, the seat is available
    newSeat->left = newSeat->right = NULL;
    return newSeat;
}

// Insert seats in a binary tree fashion
SeatNode* insertSeat(SeatNode* root, int seatNumber) {
    if (root == NULL)
        return createSeat(seatNumber);

    if (seatNumber < root->seatNumber)
        root->left = insertSeat(root->left, seatNumber);
    else if (seatNumber > root->seatNumber)
        root->right = insertSeat(root->right, seatNumber);

    return root;
}

// Book a seat
void bookSeat(SeatNode* root, int seatNumber) {
    if (root == NULL) {
        printf("Seat %d does not exist.\n", seatNumber);
        return;
    }

    if (root->seatNumber == seatNumber) {
        if (root->isBooked) {
            printf("Seat %d is already booked.\n", seatNumber);
        } else {
            root->isBooked = 1;
            printf("Seat %d booked successfully.\n", seatNumber);
        }
    } else if (seatNumber < root->seatNumber) {
        bookSeat(root->left, seatNumber);
    } else {
        bookSeat(root->right, seatNumber);
    }
}

// Cancel a booking
void cancelBooking(SeatNode* root, int seatNumber) {
    if (root == NULL) {
        printf("Seat %d does not exist.\n", seatNumber);
        return;
    }

    if (root->seatNumber == seatNumber) {
        if (!root->isBooked) {
            printf("Seat %d is already available.\n", seatNumber);
        } else {
            root->isBooked = 0;
            printf("Booking for seat %d canceled successfully.\n", seatNumber);
        }
    } else if (seatNumber < root->seatNumber) {
        cancelBooking(root->left, seatNumber);
    } else {
        cancelBooking(root->right, seatNumber);
    }
}

// Check availability of seats
void checkAvailability(SeatNode* root) {
    if (root != NULL) {
        checkAvailability(root->left);
        printf("Seat %d is %s.\n", root->seatNumber, root->isBooked ? "booked" : "available");
        checkAvailability(root->right);
    }
}

int main() {
    SeatNode* root = NULL;
    int choice, seatNumber, numberOfSeats, i;

    printf("Welcome to the Cinema Ticket Booking System!!!!!!!!\n");
    int arr[]={6,3,9,2,5,8,10,1,4,7};

    for (i = 1; i < 10; i++) {

        root = insertSeat(root,arr[i]);
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Book a Seat\n");
        printf("2. Cancel a Booking\n");
        printf("3. Check Seat Availability\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter seat number to book: ");
                scanf("%d", &seatNumber);
                bookSeat(root, seatNumber);
                break;

            case 2:
                printf("Enter seat number to cancel booking: ");
                scanf("%d", &seatNumber);
                cancelBooking(root, seatNumber);
                break;

            case 3:
                printf("Checking seat availability...\n");
                checkAvailability(root);
                break;

            case 4:
                printf("Exiting the system. Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
