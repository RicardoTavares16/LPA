#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

int** board;
int boardSize, maxMoves;

void printMatrix(int** board) {
        int row, col;
        // int boardSizeCheck = sizeof(board[0])/sizeof(board[0][0]);
        // std::cout << "Size " << boardSizeCheck << "\n";
        for(row = 0; row < boardSize; row++){

            fprintf(stdout, "\t     |");
            for(col = 0; col < boardSize; col++)
            {
                printf("%4d    |", board[row][col]);
            }
            fprintf(stdout, "\n\n");
        }
};

void alloc() {
    board = (int**) malloc((boardSize) * sizeof(int*));
    for(int i = 0; i < boardSize; i++) {
        board[i] = (int*) malloc((boardSize) * sizeof(int));
    }
}

void clear() {
      for(int i = 0; i < boardSize; i++) {
            free(board[i]);
        }
	    free(board);
}

int solve2048(int moves) {
    moves--;
    if(moves >= 0) {
        return solve2048(moves);
    }
    else {
        return -1;
    }
}

void fall() {
    int i, j, k, temp;

    // migrate zeros to backward
    for (i = 0; i < boardSize; ++i) {
        j = boardSize - 1;
        k = boardSize - 2;
        while (k > -1) {
            if (board[j][i] == 0 && board[k][i] != 0) {
                temp = board[k][i];
                board[k][i] = board[j][i];
                board[j][i] = temp;
                j--;
            }
            else if (board[j][i]) {
                j--;
            }
            k--;
        }
    }

    // resolve
    for (i = boardSize - 2; i >= 0; --i) {
        for (j = 0; j < boardSize; ++j) {
            if (board[i][j] == board[i+1][j]) {
                board[i+1][j] = board[i][j] * 2;
                board[i][j] = 0;
            }
            else if (board[i+1][j] == 0) {
                board[i+1][j] = board[i][j];
                board[i][j] = 0;
            } else {
                board[i][j] = board[i][j];
            }
        }
    }
}

int main()
{

    int testCases;
    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        std::cin >> boardSize >> maxMoves;
        std::cout << "Board: " << boardSize << " Moves: " << maxMoves << "\n";
        alloc();

        for (int j = 0; j < boardSize; j++)
        {
            std::string line;
            for (int a = 0; a < boardSize; a++)
            {
                int inputNumber;
                getline(std::cin, line, ' ');
                std::istringstream iss(line);
                while (iss >> inputNumber)
                {
                    board[j][a] = inputNumber;
                    std::cout << inputNumber;
                }
            }
            std::cout << "\n";
        }
        printMatrix(board);
        std::cout << "Fall\n";
        fall();
        printMatrix(board);
        // int best = solve2048(maxMoves);
        // if(best == -1){
        //     std::cout << "no solution\n";
        // }
        // else{
        //     std::cout << best << "\n";
        // }

        clear();
    }
}