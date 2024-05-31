#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Define struct
typedef struct Node {
    char data;
    struct Node* next;
} Node;

int playerOneScore = 0, playerTwoScore = 0, botScore = 0;

// New node function
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

// Function to check if there is a win condition (Horizontal, Vertical, or Diagonal)
int checkWin(Node* head) {
    char board[3][3];
    int k = 0;
    Node* current = head;
    
    // Convert linked list to 2D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = current->data;
            current = current->next;
        }
    }

    // Check for Horizontal and Vertical (Row and Columns)
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return 1;
    }

    // Check Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return 1;

    return 0;
}

// Function to check if the board is full
int checkBoardFull(Node* head) {
    while (head != NULL) {
        if (head->data == ' ') return 0;
        head = head->next;
    }
    return 1;
}

// Function for file processing (Score history)
void scoreFile(int score1, int score2, int mode){
    time_t t = time(NULL); // Gets the current callendar time. NULL because we are not giving a variable to restore the result
    struct tm tm = *localtime(&t); // Converts the time_t val into a better format (yyyy/mm/dd)
    FILE *file = fopen("Scores.txt", "a"); // Open Scores.txt and set to append
    if(file == NULL){
        printf("Unable to access score file!\n");
        return;
    }
    if(mode == 1){
        fprintf(file, "%04d-%02d-%02d - Player 1 VS Bot = %d : %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, score1, score2); // Scores format (Date - Player 1 VS Bot = Score 1 : Score 2)
    } else{
        fprintf(file, "%04d-%02d-%02d - Player 1 VS Player 2 = %d : %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, score1, score2); // Scores format (Date - Player 1 VS Player 2 = Score 1 : Score 2)
    }
    fclose(file);
}

// Function to play the game
void TicTacToe(int gameMode) {
    Node* head = NULL;
    Node* current = NULL;

    // Initialize the linked list to represent the game board
    for (int i = 0; i < 9; i++) {
        if (head == NULL) {
            head = createNode(' ');
            current = head;
        } else {
            current->next = createNode(' ');
            current = current->next;
        }
    }

    srand(time(NULL)); // Seed the RNG for bot

    int currentPlayer = 1;
    int gameOver = 0;
    int playAgain = 0;
    int move;
    char mark;

    while (!gameOver) {
        displayBoard(head);

        if (currentPlayer == 1) {
            printf("Player 1, enter a number (1-9) to place X: ");
            scanf("%d", &move);
        } else {
            if (gameMode == 1) {
                do {
                    move = rand() % 9 + 1; // Bot RNG Move
                    current = head;
                    for (int i = 1; i < move; i++) {
                        current = current->next;
                    }
                } while (current->data != ' ');
                printf("Bot chooses position %d\n", move);
            } else {
                printf("Player 2, enter a number (1-9) to place O: ");
                scanf("%d", &move);
            }
        }

        mark = (currentPlayer == 1) ? 'X' : 'O'; // Check if the currentPlayer is 1, if yes it will mark 'X', if not it will mark 'O'

        current = head;
        for (int i = 1; i < move; i++) {
            current = current->next;
        }
        if (current->data == ' ') {
            current->data = mark;
            if (checkWin(head)) { // If someone wins the game
                displayBoard(head);
                if (currentPlayer == 1) {
                    printf("Player 1 wins!\n");
                    playerOneScore++;
                } else {
                    if(gameMode == 1){
                        printf("Bot wins!\n");
                        botScore++;
                    } else{
                        printf("Player 2 Wins!\n");
                        playerTwoScore++;
                    }
                }
                gameOver = 1;
            } else if (checkBoardFull(head)) {
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

    printf("Do you want to play again?(1 for Yes | 0 for No)\n");
    scanf("%d", &playAgain);
    if (playAgain == 1) {
        TicTacToe(gameMode);
    } else {
        if(gameMode == 1){
            scoreFile(playerOneScore, botScore, gameMode);
        }else{
            scoreFile(playerOneScore, playerTwoScore, gameMode);
        }
        return;
    }
}
 // Menu function
void menu(){
    system("CLS");
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
           "/_/  \\____/\\___/\n"); // The game title in ASCII art

    printf("\n1. Play Game\n");
    printf("2. View Score\n");
    printf("0. Exit\n\n\n\n");
    printf("Please pick a choice\n");
}

// Main function
int main() {
    int choice, gameChoice;
    start:
    menu();
    do{
        printf("\t>>");
        scanf("%d", &choice);
    }while(choice > 3);

    switch(choice){
        case 1:
            system("CLS"); // To make the screen clear
            printf("Please pick a gamemode!\n\n");
            printf("1. Single Player (VS Bot)\n");
            printf("2. Multi Plater (PVP)\n");
            printf("0. Back\n");
            do{
                printf("\t>>");
                scanf("%d", &gameChoice);
            }while(gameChoice < 0 || gameChoice > 2);
            switch(gameChoice){
                case 1:
                    TicTacToe(1);
                    goto start;
                break;
                case 2:
                    TicTacToe(2);
                    goto start;
                break;
                case 0:
                    goto start;
                break;
            }
        break;
        case 2:
            system("CLS");
            FILE *file = fopen("Scores.txt", "r");
            if (file == NULL) {
                printf("Unable to open scores file.\n");
                break;
            }

            char line[256];
            while (fgets(line, sizeof(line), file)) { // Write all 'line' in Scores.txt
                printf("%s", line);
            }
            fclose(file);

            printf("\nPress any key to go back.\n");
            getch();
            goto start;
        break;
        case 0:
            system("CLS");
            // vvv basically just 'THANK YOU FOR PLAYING' in ASCII art and 3D vvv
            printf( "  ______________  ___  ________  ________   ___  __             ___    ___ ________  ___  ___          ________ ________  ________          ________  ___       ________      ___    ___ ___  ________   ________     \n"
                    " |\\___   __\\ \\  \\|\\  \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\          |\\  \\  /  /|\\   __  \\|\\  \\|\\  \\        |\\  _____\\\\   __  \\|\\   __  \\        |\\   __  \\|\\  \\     |\\   __  \\    |\\  \\  /  /|\\  \\|\\   ___  \\|\\   ____\\    \n"
                    " \\|___ \\  \\ \\ \\  \\_\\  \\ \\  \\_\\  \\ \\  \\\\ \\  \\ \\  \\/  /__        \\ \\  \\/  / | \\  \\ \\  \\ \\  \\ \\  \\       \\ \\  \\___\\ \\  \\ \\  \\ \\  \\_\\  \\       \\ \\  \\_\\  \\ \\  \\    \\ \\  \\_\\  \\   \\ \\  \\/  / | \\  \\ \\  \\\\ \\  \\ \\  \\___|    \n"
                    "      \\ \\  \\ \\ \\   __  \\ \\   __  \\ \\  \\\\ \\  \\ \\   ___  \\        \\ \\    / / \\ \\  \\ \\  \\ \\  \\ \\  \\       \\ \\   __\\\\ \\  \\ \\  \\ \\   _  _\\       \\ \\   ____\\ \\  \\    \\ \\   __  \\   \\ \\    / / \\ \\  \\ \\  \\\\ \\  \\ \\  \\  ___  \n"
                    "       \\ \\  \\ \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\        \\/  /  /   \\ \\  \\_\\  \\ \\  \\_\\  \\       \\ \\  \\_| \\ \\  \\_\\  \\ \\  \\\\  \\        \\ \\  \\___|\\ \\  \\____\\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\ \\  \\\\ \\  \\ \\  \\_\\  \\ \n"
                    "        \\ \\__\\ \\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\     __/  / /      \\ \\_______\\ \\_______\\       \\ \\__\\   \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\__/  / /      \\ \\__\\ \\__\\\\ \\__\\ \\_______\\\n"
                    "         \\|__|  \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|__| \\|__|    |\\___/ /        \\|_______|\\|_______|        \\|__|    \\|_______|\\|__|\\|__|        \\|__|     \\|_______|\\|__|\\|__|\\___/ /        \\|__|\\|__| \\|__|\\|_______|\n"
                    "                                                              \\|___|/                                                                                                       \\|___|/\n");
            printf("Press anything to quit...");
            getch();
            return 0;
        break;
    }
    return 0;
}