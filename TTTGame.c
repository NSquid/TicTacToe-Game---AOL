#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Define the Node structure
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to display the game board
void displayBoard(Node* head) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", head->data);
            head = head->next;
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---+---+---\n");
    }
    printf("\n");
}

// Function to check if there is a win
int checkWin(Node* head) {
    char board[3][3];
    int k = 0;
    Node* current = head;
    
    // Convert linked list to 2D array for easy checking
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = current->data;
            current = current->next;
        }
    }

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return 1;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return 1;

    return 0;
}

// Function to check if the board is full
int isBoardFull(Node* head) {
    while (head != NULL) {
        if (head->data == ' ') return 0;
        head = head->next;
    }
    return 1;
}

void game() {
    Node* head = NULL;
    Node* current = NULL;

    // Initialize the linked list representing the game board
    for (int i = 0; i < 9; i++) {
        if (head == NULL) {
            head = createNode(' ');
            current = head;
        } else {
            current->next = createNode(' ');
            current = current->next;
        }
    }

    srand(time(NULL)); // Seed the random number generator

    int currentPlayer = 1;
    int gameOver = 0;
    int move;
    char mark;

    while (!gameOver) {
        displayBoard(head);

        if (currentPlayer == 1) {
            printf("Player 1, enter a number (1-9) to place X: ");
            scanf("%d", &move);
        } else {
            do {
                move = rand() % 9 + 1; // Bot chooses a random move
                current = head;
                for (int i = 1; i < move; i++) {
                    current = current->next;
                }
            } while (current->data != ' ');
            printf("Bot chooses position %d\n", move);
        }

        mark = (currentPlayer == 1) ? 'X' : 'O';

        current = head;
        for (int i = 1; i < move; i++) {
            current = current->next;
        }
        if (current->data == ' ') {
            current->data = mark;
            if (checkWin(head)) {
                displayBoard(head);
                if (currentPlayer == 1) {
                    printf("Player 1 wins!\n");
                } else {
                    printf("Bot wins!\n");
                }
                gameOver = 1;
            } else if (isBoardFull(head)) {
                displayBoard(head);
                printf("The game is a draw.\n");
                gameOver = 1;
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            printf("Invalid move. Please try again.\n");
        }
    }

    current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void menu(){
    printf("  _______         \n"
           " /_  ___/_____    \n"
           "  / / / / ___/    \n"
           " / / / / /__      \n"
           "/_/ /_/____/      \n"
           "  ______           \n"
           " /_  __/___  _____\n"
           "  / / / __ \\/ ___/\n"
           " / / / /_/ / /__ \n"
           "/_/ /_/\\__/____/  \n"
           "  ______           \n"
           " /_  __/___  ___  \n"
           "  / / / __ \\/ _ \\ \n"
           " / / / /_/ /  __/ \n"
           "/_/  \\____/\\___/\n");

    printf("\n1. Play Game\n");
    printf("2. View Score\n");
    printf("3. Exit\n\n\n\n");
    printf("Please pick a choice");
}

int main() {
    int choice;
    menu();
    while(choice > 3 || choice <= 0){
        printf("\t>>");
        scanf("%d", &choice);
    }
    switch(choice){
        case 1:
        break;
        case 2:
        break;
        case 3:

        printf( "  ______________  ___  ________  ________   ___  __             ___    ___ ________  ___  ___          ________ ________  ________          ________  ___       ________      ___    ___ ___  ________   ________     \n"
                " |\\___   __\\ \\  \\|\\  \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\          |\\  \\  /  /|\\   __  \\|\\  \\|\\  \\        |\\  _____\\\\   __  \\|\\   __  \\        |\\   __  \\|\\  \\     |\\   __  \\    |\\  \\  /  /|\\  \\|\\   ___  \\|\\   ____\\    \n"
                " \\|___ \\  \\ \\ \\  \\_\\  \\ \\  \\_\\  \\ \\  \\\\ \\  \\ \\  \\/  /__        \\ \\  \\/  / | \\  \\ \\  \\ \\  \\ \\  \\       \\ \\  \\___\\ \\  \\ \\  \\ \\  \\_\\  \\       \\ \\  \\_\\  \\ \\  \\    \\ \\  \\_\\  \\   \\ \\  \\/  / | \\  \\ \\  \\\\ \\  \\ \\  \\___|    \n"
                "      \\ \\  \\ \\ \\   __  \\ \\   __  \\ \\  \\\\ \\  \\ \\   ___  \\        \\ \\    / / \\ \\  \\ \\  \\ \\  \\ \\  \\       \\ \\   __\\\\ \\  \\ \\  \\ \\   _  _\\       \\ \\   ____\\ \\  \\    \\ \\   __  \\   \\ \\    / / \\ \\  \\ \\  \\\\ \\  \\ \\  \\  ___  \n"
                "       \\ \\  \\ \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\        \\/  /  /   \\ \\  \\_\\  \\ \\  \\_\\  \\       \\ \\  \\_| \\ \\  \\_\\  \\ \\  \\\\  \\        \\ \\  \\___|\\ \\  \\____\\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\ \\  \\\\ \\  \\ \\  \\_\\  \\ \n"
                "        \\ \\__\\ \\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\     __/  / /      \\ \\_______\\ \\_______\\       \\ \\__\\   \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\__/  / /      \\ \\__\\ \\__\\\\ \\__\\ \\_______\\\n"
                "         \\|__|  \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|__| \\|__|    |\\___/ /        \\|_______|\\|_______|        \\|__|    \\|_______|\\|__|\\|__|        \\|__|     \\|_______|\\|__|\\|__|\\___/ /        \\|__|\\|__| \\|__|\\|_______|\n"
                "                                                              \\|___|/                                                                                                       \\|___|/\n");
        sleep(2);
        return 0;
        break;
    }
    game();
    return 0;
}