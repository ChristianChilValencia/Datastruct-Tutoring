#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char symbol);
bool checkDraw(char board[SIZE][SIZE]);
void updateScore(char winner, int *player1Score, int *player2Score);
void displayScores(char *player1, int player1Score, char *player2, int player2Score);

int main() {
    char board[SIZE][SIZE];
    char player1[20], player2[20];
    int rounds, round = 0;
    int player1Score = 0, player2Score = 0;
    
    printf("Welcome to Tic-Tac-Toe!\n\n");
    printf("Enter Player 1's name: ");
    scanf("%s", player1);
    printf("Enter Player 2's name: ");
    scanf("%s", player2);
    
    printf("\nEnter number of rounds: ");
    scanf("%d", &rounds);
    
    while (round < rounds) {
        round++;
        printf("\nRound %d\n", round);
        char currentPlayer = 'X'; // Player 1 starts with 'X'
        int moves = 0;
        bool gameover = false;
        
        initializeBoard(board);
        displayBoard(board);
        
        while (!gameover && moves < SIZE*SIZE) {
            int row, col;
            printf("\n%s's turn (%c): Enter row (1-3) and column (1-3) separated by space: ", 
                   (currentPlayer == 'X' ? player1 : player2), currentPlayer);
            scanf("%d %d", &row, &col);
            
            // Adjusting to 0-based index
            row--;
            col--;
            
            if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                moves++;
                displayBoard(board);
                
                if (checkWin(board, currentPlayer)) {
                    printf("\n%s wins!\n", (currentPlayer == 'X' ? player1 : player2));
                    updateScore(currentPlayer, &player1Score, &player2Score);
                    gameover = true;
                } else if (checkDraw(board)) {
                    printf("\nIt's a draw!\n");
                    gameover = true;
                } else {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            } else {
                printf("Invalid move. Try again.\n");
            }
        }
    }
    
    printf("\nGame Over!\n");
    displayScores(player1, player1Score, player2, player2Score);
    
    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(char board[SIZE][SIZE]) {
    printf("\n  1 2 3\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("  -----\n");
    }
}

bool checkWin(char board[SIZE][SIZE], char symbol) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
    return false;
}

bool checkDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void updateScore(char winner, int *player1Score, int *player2Score) {
    if (winner == 'X') {
        (*player1Score)++;
    } else {
        (*player2Score)++;
    }
}

void displayScores(char *player1, int player1Score, char *player2, int player2Score) {
    printf("\nScores:\n");
    printf("%s: %d\n", player1, player1Score);
    printf("%s: %d\n", player2, player2Score);
}

