#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>

int boardSize, maxMoves;
int best;
bool found = false;

typedef struct
{
    int tiles[20][20];
} matrix;

matrix gameBoard;

void printMatrix(matrix board)
{
    int row, col;
    // int boardSizeCheck = sizeof(board[0])/sizeof(board[0][0]);
    // std::cout << "Size " << boardSizeCheck << "\n";
    for (row = 0; row < boardSize; row++)
    {

        fprintf(stdout, "\t     |");
        for (col = 0; col < boardSize; col++)
        {
            printf("%4d    |", board.tiles[row][col]);
        }
        fprintf(stdout, "\n\n");
    }
};

int is_solved(matrix board)
{
    int count = 0;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board.tiles[i][j] > 0)
                count++;
            if (count > 1)
                return 0;
        }
    }
    return 1;
}

matrix fall(matrix board)
{
    int i, j, k, temp;
    for (i = boardSize - 1; i >= 0; i--)
    {
        for (j = boardSize - 1; j >= 0; j--)
        {
            if (board.tiles[j][i])
            {
                temp = board.tiles[j][i];
                k = j - 1;
                while (k >= 0)
                {
                    if (board.tiles[k][i])
                    {
                        if (board.tiles[k][i] == board.tiles[j][i])
                        {
                            board.tiles[j][i] *= 2;
                            board.tiles[k][i] = 0;
                        }
                        break;
                    }
                    k--;
                }
            }
        }
    }

    for (i = 0; i < boardSize; ++i)
    {
        j = boardSize - 1;
        k = boardSize - 2;
        while (k > -1)
        {
            if (board.tiles[j][i] == 0 && board.tiles[k][i] != 0)
            {
                temp = board.tiles[k][i];
                board.tiles[k][i] = board.tiles[j][i];
                board.tiles[j][i] = temp;
                j--;
            }
            else if (board.tiles[j][i])
            {
                j--;
            }
            k--;
        }
    }

    return board;
}

matrix upsideDown(matrix board)
{
    int temp;
    for (int i = 0; i < boardSize / 2; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            temp = board.tiles[i][j];
            board.tiles[i][j] = board.tiles[boardSize - i - 1][j];
            board.tiles[boardSize - i - 1][j] = temp;
        }
    }
    return board;
}

matrix rotateRight(matrix board)
{
    matrix g2;
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            g2.tiles[boardSize - 1 - j][i] = board.tiles[i][j];
        }
    }
    memcpy(board.tiles, g2.tiles, sizeof(int) * 20 * 20);
    return board;
}

matrix rotateLeft(matrix board)
{
    matrix g2;
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            g2.tiles[i][j] = board.tiles[boardSize - 1 - j][i];
        }
    }
    memcpy(board.tiles, g2.tiles, sizeof(int) * 20 * 20);
    return board;
}

matrix up(matrix board)
{
    board = upsideDown(board);
    board = fall(board);
    board = upsideDown(board);
    return board;
}

matrix down(matrix board)
{
    board = fall(board);
    return board;
}

matrix left(matrix board)
{
    board = rotateRight(board);
    board = fall(board);
    board = rotateLeft(board);
    return board;
}

matrix right(matrix board)
{
    board = rotateLeft(board);
    board = fall(board);
    board = rotateRight(board);
    return board;
}

void solve2048(matrix board, int play)
{
    if (is_solved(board))
    {
        //std::cout << "SOLVED " << play << " play\n";
        if (play < best)
        {
            best = play;
            //std::cout << "play: " << play << "\n";
        }
        found = true;
        return;
    }
    if (play < best)
    {
        //std::cout << "Calling on " << play << " move\n";
        solve2048(left(board), play + 1);
        solve2048(right(board), play + 1);
        solve2048(up(board), play + 1);
        solve2048(down(board), play + 1);
    }
}

int main()
{
    int testCases;
    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        std::cin >> boardSize >> maxMoves;
        //std::cout << "Board: " << boardSize << " Moves: " << maxMoves << "\n";

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
                    gameBoard.tiles[j][a] = inputNumber;
                    //std::cout << inputNumber;
                }
            }
            //std::cout << "\n";
        }

        // printMatrix(gameBoard);
        // gameBoard = down(gameBoard);
        // std::cout << "After move\n";
        // printMatrix(gameBoard);

        best = maxMoves;
        found = false;
        solve2048(gameBoard, 0);
        if (found == false)
        {
            std::cout << "no solution\n";
        }
        else
        {
            std::cout << best << "\n";
        }
    }
}