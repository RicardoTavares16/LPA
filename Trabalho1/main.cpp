#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>

int **board;
int boardSize, maxMoves;

void printMatrix(int **board)
{
    int row, col;
    // int boardSizeCheck = sizeof(board[0])/sizeof(board[0][0]);
    // std::cout << "Size " << boardSizeCheck << "\n";
    for (row = 0; row < boardSize; row++)
    {

        fprintf(stdout, "\t     |");
        for (col = 0; col < boardSize; col++)
        {
            printf("%4d    |", board[row][col]);
        }
        fprintf(stdout, "\n\n");
    }
};

void alloc()
{
    board = new int *[boardSize];
    for (int i = 0; i < boardSize; ++i)
    {
        board[i] = new int[boardSize];
    }
}

void clear()
{
    for (int i = 0; i < boardSize; ++i)
    {
        delete[] board[i];
    }
    delete[] board;
}

int is_solved(int **board)
{
    int count = 0;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] > 0)
                count++;
            if (count > 1)
                return 0;
        }
    }
    return 1;
}

int **fall(int **board)
{
    int i, j, k, temp;

    // migrate zeros to backward
    for (i = 0; i < boardSize; ++i)
    {
        j = boardSize - 1;
        k = boardSize - 2;
        while (k > -1)
        {
            if (board[j][i] == 0 && board[k][i] != 0)
            {
                temp = board[k][i];
                board[k][i] = board[j][i];
                board[j][i] = temp;
                j--;
            }
            else if (board[j][i])
            {
                j--;
            }
            k--;
        }
    }

    // resolve
    for (i = boardSize - 2; i >= 0; --i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == board[i + 1][j])
            {
                board[i + 1][j] = board[i][j] * 2;
                board[i][j] = 0;
            }
            else if (board[i + 1][j] == 0)
            {
                board[i + 1][j] = board[i][j];
                board[i][j] = 0;
            }
            else
            {
                board[i][j] = board[i][j];
            }
        }
    }

    return board;
}

int **upside_down(int **board)
{
    int temp;
    for (int i = 0; i < boardSize / 2; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            temp = board[i][j];
            board[i][j] = board[boardSize - i - 1][j];
            board[boardSize - i - 1][j] = temp;
        }
    }
    return board;
}

int **rotate_right(int **board)
{
    int **g2 = new int *[boardSize];
    for (int i = 0; i < boardSize; i++)
    {
        g2[i] = new int[boardSize];
    }

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            g2[boardSize - 1 - j][i] = board[i][j];
        }
    }

    memcpy(board, g2, sizeof(int) * boardSize * boardSize);

    free(g2);
    return board;
}

int **rotate_left(int **board)
{
    int **g2 = new int *[boardSize];
    for (int i = 0; i < boardSize; i++)
    {
        g2[i] = new int[boardSize];
    }

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            g2[i][j] = board[boardSize - 1 - j][i];
        }
    }

    memcpy(board, g2, sizeof(int) * boardSize * boardSize);

    free(g2);
    return board;
}

int **up(int **board)
{
    board = upside_down(board);
    board = fall(board);
    board = upside_down(board);
    return board;
}

int **down(int **board)
{
    board = fall(board);
    return board;
}

int **left(int **board)
{
    board = rotate_right(board);
    board = fall(board);
    board = rotate_left(board);
    return board;
}

int **right(int **board)
{
    board = rotate_left(board);
    board = fall(board);
    board = rotate_right(board);
    return board;
}

void solve2048(int **board, int moves)
{
    moves--;
    if (is_solved(board))
    {
        std::cout << "SOLVED " << moves << "\n";
        return;
    }
    if (moves >= 0)
    {
        std::cout << "Calling on " << moves << " move\n";
        solve2048(left(board), moves);
        solve2048(right(board), moves);
        solve2048(up(board), moves);
        solve2048(down(board), moves);
    }
    else
    {
        return;
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
        board = left(board);
        std::cout << "After move\n";
        printMatrix(board);

        //solve2048(board, maxMoves);
        // if(best == -1){
        //     std::cout << "no solution\n";
        // }
        // else{
        //     std::cout << best << "\n";
        // }

        clear();
    }
}