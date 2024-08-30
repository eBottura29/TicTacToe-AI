#include <iostream>
#include <ctime>
#include <algorithm>  // Include for std::max and std::min

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
int endgameCheck(char *spaces, char player, char computer);
int minimax(char *spaces, bool isMaximizing, char player, char computer);
int bestMove(char *spaces, char computer, char player);

int main() {
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';
    char computer = 'O';
    bool running = true;

    drawBoard(spaces);
    
    while (running) {
        playerMove(spaces, player);
        drawBoard(spaces);

        int endgameCheckIndex = endgameCheck(spaces, player, computer);
        if (endgameCheckIndex == 1) {
            std::cout << "YOU WON!\n";
            break;
        } else if (endgameCheckIndex == 2) {
            std::cout << "YOU LOST!\n";
            break;
        } else if (endgameCheckIndex == 3) {
            std::cout << "It's a tie!\n";
            break;
        }

        computerMove(spaces, computer);
        drawBoard(spaces);

        endgameCheckIndex = endgameCheck(spaces, player, computer);
        if (endgameCheckIndex == 1) {
            std::cout << "YOU WON!\n";
            break;
        } else if (endgameCheckIndex == 2) {
            std::cout << "YOU LOST!\n";
            break;
        } else if (endgameCheckIndex == 3) {
            std::cout << "It's a tie!\n";
            break;
        }
    }

    std::cout << "Thanks for playing\n";
    return 0;
}

void drawBoard(char *spaces) {
    std::cout << "   |   |   \n";
    std::cout << " " << spaces[0] << " | " << spaces[1] << " | " << spaces[2] << " \n";
    std::cout << "___|___|___\n";
    std::cout << "   |   |   \n";
    std::cout << " " << spaces[3] << " | " << spaces[4] << " | " << spaces[5] << " \n";
    std::cout << "___|___|___\n";
    std::cout << "   |   |   \n";
    std::cout << " " << spaces[6] << " | " << spaces[7] << " | " << spaces[8] << " \n";
    std::cout << "   |   |   \n";
}

void playerMove(char *spaces, char player) {
    int number;
    while (true) {
        std::cout << "Enter your move (1-9): ";
        std::cin >> number;

        // Check if input is a valid number
        if (std::cin.fail() || number < 1 || number > 9) {
            std::cin.clear();  // Clear the input stream
            std::cin.ignore(10000, '\n');  // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
        } else if (spaces[number - 1] != ' ') {
            std::cout << "This space is already taken. Choose another.\n";
        } else {
            spaces[number - 1] = player;
            break;
        }
    }
}

void computerMove(char *spaces, char computer) {
    int move = bestMove(spaces, computer, 'X');
    spaces[move] = computer;
    std::cout << "AI Played " << move + 1 << '\n';
}

int endgameCheck(char *spaces, char player, char computer) {
    int output = 0;

    if ((spaces[0] != ' ') && (spaces[0] == spaces[1]) && (spaces[1] == spaces[2])) {
        return (spaces[0] == player) ? 1 : 2;
    } else if ((spaces[3] != ' ') && (spaces[3] == spaces[4]) && (spaces[4] == spaces[5])) {
        return (spaces[3] == player) ? 1 : 2;
    } else if ((spaces[6] != ' ') && (spaces[6] == spaces[7]) && (spaces[7] == spaces[8])) {
        return (spaces[6] == player) ? 1 : 2;
    } else if ((spaces[0] != ' ') && (spaces[0] == spaces[3]) && (spaces[3] == spaces[6])) {
        return (spaces[0] == player) ? 1 : 2;
    } else if ((spaces[1] != ' ') && (spaces[1] == spaces[4]) && (spaces[4] == spaces[7])) {
        return (spaces[1] == player) ? 1 : 2;
    } else if ((spaces[2] != ' ') && (spaces[2] == spaces[5]) && (spaces[5] == spaces[8])) {
        return (spaces[2] == player) ? 1 : 2;
    } else if ((spaces[0] != ' ') && (spaces[0] == spaces[4]) && (spaces[4] == spaces[8])) {
        return (spaces[0] == player) ? 1 : 2;
    } else if ((spaces[2] != ' ') && (spaces[2] == spaces[4]) && (spaces[4] == spaces[6])) {
        return (spaces[2] == player) ? 1 : 2;
    }

    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return 0;  // Game is still ongoing
        }
    }

    return 3;  // It's a tie
}

int minimax(char *spaces, bool isMaximizing, char player, char computer) {
    int score = endgameCheck(spaces, player, computer);
    if (score == 1) return -10;  // Player wins
    if (score == 2) return 10;   // Computer wins
    if (score == 3) return 0;    // Tie

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                spaces[i] = computer;
                bestScore = std::max(bestScore, minimax(spaces, false, player, computer));
                spaces[i] = ' ';
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                spaces[i] = player;
                bestScore = std::min(bestScore, minimax(spaces, true, player, computer));
                spaces[i] = ' ';
            }
        }
        return bestScore;
    }
}

int bestMove(char *spaces, char computer, char player) {
    int bestScore = -1000;
    int move = 0;
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            spaces[i] = computer;
            int score = minimax(spaces, false, player, computer);
            spaces[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}
