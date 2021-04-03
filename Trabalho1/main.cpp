#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

int** board;

void printMatrix(int** board, int boardSize) {
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

void alloc(int boardSize) {
    board = (int**) malloc((boardSize) * sizeof(int*));
    for(int i = 0; i < boardSize; i++) {
        board[i] = (int*) malloc((boardSize) * sizeof(int));
    }
}

void clear(int boardSize) {
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

int main()
{

    int testCases;
    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int boardSize, maxMoves;
        std::cin >> boardSize >> maxMoves;
        //std::cout << "Board: " << boardSize << " Moves: " << maxMoves << "\n";
        alloc(boardSize);

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
                    //std::cout << inputNumber;
                }
            }
            //std::cout << "\n";
        }
        //printMatrix(board, boardSize);
        int best = solve2048(maxMoves);
        if(best == -1){
            std::cout << "no solution\n";
        }
        else{
            std::cout << best << "\n";
        }

        clear(boardSize);
    }
}