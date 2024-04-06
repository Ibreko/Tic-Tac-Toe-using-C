#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to hold player statistics
typedef struct {
    int wins;
    int losses;
    int draws;
} PlayerStats;

// Function to display the Tic Tac Toe board
void display_board(char board[], int size) {
    for (int i = 0; i < size; ++i) {
        printf(" %c ", board[i]);
        if ((i + 1) % (int)sqrt(size) == 0 && i != size - 1) {
            printf("\n---|---|---\n");
        } else if (i != size - 1) {
            printf("|");
        }
    }
    printf("\n");
}

// Function to check if a player has won
bool check_win(char board[], char mark, int size) {
    // Check rows
    for (int i = 0; i < size; i += (int)sqrt(size)) {
        if (board[i] == mark && board[i] == board[i + 1] && board[i] == board[i + 2]) {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < (int)sqrt(size); ++i) {
        if (board[i] == mark && board[i] == board[i + (int)sqrt(size)] && board[i] == board[i + 2 * (int)sqrt(size)]) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0] == mark && board[0] == board[4] && board[0] == board[8]) ||
        (board[2] == mark && board[2] == board[4] && board[2] == board[6])) {
        return true;
    }
    return false;
}

// Function to check if the board is full
bool check_full(char board[], int size) {
    for (int i = 0; i < size; ++i) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

// Function to check if the chosen position is valid
bool is_valid_move(char board[], int position, int size) {
    if (position < 1 || position > size || board[position - 1] != ' ') {
        return false;
    }
    return true;
}

// Function to get the player's move
int get_player_move(char board[], int size) {
    int position;
    printf("Enter your move (1-%d): ", size);
    scanf("%d", &position);
    return position;
}

// Function to alternate players
char alternate_player(char current_player) {
    return (current_player == 'X') ? 'O' : 'X';
}

// Function to update player statistics
void update_statistics(PlayerStats *stats, char winner) {
    if (winner == 'X') {
        stats->wins++;
    } else if (winner == 'O') {
        stats->losses++;
    } else {
        stats->draws++;
    }
}

// Function to display player statistics
void display_statistics(PlayerStats stats) {
    printf("Wins: %d\nLosses: %d\nDraws: %d\n", stats.wins, stats.losses, stats.draws);
}

// Function to play a single game
char play_game(int size) {
    int position;
    char current_player = 'X';
    char *board = (char *)malloc(size * size * sizeof(char));
    for (int i = 0; i < size * size; ++i) {
        board[i] = ' ';
    }
    while (true) {
        display_board(board, size * size);
        printf("Player %c's turn\n", current_player);
        position = get_player_move(board, size * size);
        if (!is_valid_move(board, position, size * size)) {
            printf("Invalid move! Try again.\n");
            continue;
        }
        board[position - 1] = current_player;
        if (check_win(board, current_player, size * size)) {
            display_board(board, size * size);
            printf("Player %c wins!\n", current_player);
            free(board);
            return current_player;
        } else if (check_full(board, size * size)) {
            display_board(board, size * size);
            printf("It's a draw!\n");
            free(board);
            return ' ';
        }
        current_player = alternate_player(current_player);
    }
}

// Main function
int main() {
    int size;
    char winner;
    PlayerStats player1_stats = {0, 0, 0};
    PlayerStats player2_stats = {0, 0, 0};
    printf("Welcome to Tic Tac Toe!\n");
    while (true) {
        printf("Enter the size of the board (e.g., 3 for 3x3, 4 for 4x4, etc.): ");
        scanf("%d", &size);
        winner = play_game(size);
        if (winner == 'X') {
            update_statistics(&player1_stats, winner);
        } else if (winner == 'O') {
            update_statistics(&player2_stats, winner);
        } else {
            update_statistics(&player1_stats, winner);
            update_statistics(&player2_stats, winner);
            printf("No winner.\n");
        }
        printf("Player 1 Statistics:\n");
        display_statistics(player1_stats);
        printf("Player 2 Statistics:\n");
        display_statistics(player2_stats);
        char choice;
        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &choice);
        if (choice != 'Y' && choice != 'y') {
            break;
        }
    }
    return 0;
}
