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

matrix *gameBoard;

void printMatrix(matrix *board)
{
    int row, col;
    // int boardSizeCheck = sizeof(board[0])/sizeof(board[0][0]);
    // std::cout << "Size " << boardSizeCheck << "\n";
    for (row = 0; row < boardSize; row++)
    {

        fprintf(stdout, "\t     |");
        for (col = 0; col < boardSize; col++)
        {
            printf("%4d    |", board->tiles[row][col]);
        }
        fprintf(stdout, "\n\n");
    }
};

int is_solved(matrix *board)
{
    int count = 0;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board->tiles[i][j] > 0)
                count++;
            if (count > 1)
                return 0;
        }
    }
    return 1;
}

matrix *copy_board(matrix *board)
{
    matrix *copy = new matrix();
    memcpy(copy->tiles, board, sizeof(copy->tiles));
    return copy;
}

matrix *down(matrix *originalBoard)
{
    matrix *board = copy_board(originalBoard);
    int i, j, k, temp;
    bool didNothing = true;

    for (i = boardSize - 1; i >= 0; i--)
    {
        for (j = boardSize - 1; j >= 0; j--)
        {
            if (board->tiles[j][i])
            {
                temp = board->tiles[j][i];
                k = j - 1;
                while (k >= 0)
                {
                    if (board->tiles[k][i])
                    {
                        if (board->tiles[k][i] == board->tiles[j][i])
                        {
                            didNothing = false;
                            board->tiles[j][i] *= 2;
                            board->tiles[k][i] = 0;
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
            if (board->tiles[j][i] == 0 && board->tiles[k][i] != 0)
            {
                didNothing = false;
                temp = board->tiles[k][i];
                board->tiles[k][i] = board->tiles[j][i];
                board->tiles[j][i] = temp;
                j--;
            }
            else if (board->tiles[j][i])
            {
                j--;
            }
            k--;
        }
    }

    if (didNothing)
    {
        return NULL;
    }

    return board;
}

matrix *up(matrix *originalBoard)
{
    matrix *board = copy_board(originalBoard);
    int i, j, k, temp;
    bool didNothing = true;

    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board->tiles[j][i])
            {
                temp = board->tiles[j][i];
                k = j + 1;
                while (k < boardSize)
                {
                    if (board->tiles[k][i])
                    {
                        if (board->tiles[k][i] == board->tiles[j][i])
                        {
                            didNothing = false;
                            board->tiles[j][i] *= 2;
                            board->tiles[k][i] = 0;
                        }
                        break;
                    }
                    k++;
                }
            }
        }
    }

    for (i = 0; i < boardSize; ++i)
    {
        j = 0;
        k = 1;
        while (k < boardSize)
        {
            if (board->tiles[j][i] == 0 && board->tiles[k][i] != 0)
            {
                didNothing = false;
                temp = board->tiles[k][i];
                board->tiles[k][i] = board->tiles[j][i];
                board->tiles[j][i] = temp;
                j++;
            }
            else if (board->tiles[j][i])
            {
                j++;
            }
            k++;
        }
    }

    if (didNothing)
    {
        return NULL;
    }

    return board;
}

matrix *left(matrix *originalBoard)
{
    matrix *board = copy_board(originalBoard);
    int i, j, k, temp;
    bool didNothing = true;

    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board->tiles[i][j])
            {
                temp = board->tiles[i][j];
                k = j + 1;
                while (k < boardSize)
                {
                    if (board->tiles[i][k])
                    {
                        if (board->tiles[i][k] == board->tiles[i][j])
                        {
                            didNothing = false;
                            board->tiles[i][j] *= 2;
                            board->tiles[i][k] = 0;
                        }
                        break;
                    }
                    k++;
                }
            }
        }
    }

    for (i = 0; i < boardSize; ++i)
    {
        j = 0;
        k = 1;
        while (k < boardSize)
        {
            if (board->tiles[i][j] == 0 && board->tiles[i][k] != 0)
            {
                didNothing = false;
                temp = board->tiles[i][k];
                board->tiles[i][k] = board->tiles[i][j];
                board->tiles[i][j] = temp;
                j++;
            }
            else if (board->tiles[i][j])
            {
                j++;
            }
            k++;
        }
    }

    if (didNothing)
    {
        return NULL;
    }

    return board;
}

matrix *right(matrix *originalBoard)
{
    matrix *board = copy_board(originalBoard);
    int i, j, k, temp;
    bool didNothing = true;

    for (i = boardSize - 1; i >= 0; i--)
    {
        for (j = boardSize - 1; j >= 0; j--)
        {
            if (board->tiles[i][j])
            {
                temp = board->tiles[i][j];
                k = j - 1;
                while (k >= 0)
                {
                    if (board->tiles[i][k])
                    {
                        if (board->tiles[i][k] == board->tiles[i][j])
                        {
                            didNothing = false;
                            board->tiles[i][j] *= 2;
                            board->tiles[i][k] = 0;
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
            if (board->tiles[i][j] == 0 && board->tiles[i][k] != 0)
            {
                didNothing = false;
                temp = board->tiles[i][k];
                board->tiles[i][k] = board->tiles[i][j];
                board->tiles[i][j] = temp;
                j--;
            }
            else if (board->tiles[i][j])
            {
                j--;
            }
            k--;
        }
    }

    if (didNothing)
    {
        return NULL;
    }

    return board;
}

void solve2048(matrix *board, int play)
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
        matrix *leftMatrix = left(board);
        matrix *rightMatrix = right(board);
        matrix *upMatrix = up(board);
        matrix *downMatrix = down(board);
        //std::cout << "Calling on " << play << " move\n";
        if (leftMatrix != NULL)
        {
            solve2048(leftMatrix, play + 1);
        }
        if (rightMatrix != NULL)
        {
            solve2048(rightMatrix, play + 1);
        }
        if (upMatrix != NULL)
        {
            solve2048(upMatrix, play + 1);
        }
        if (downMatrix != NULL)
        {
            solve2048(downMatrix, play + 1);
        }
        free(board);
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
        gameBoard = new matrix();
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
                    gameBoard->tiles[j][a] = inputNumber;
                    //std::cout << inputNumber;
                }
            }
            //std::cout << "\n";
        }

        // printMatrix(gameBoard);
        // gameBoard = right(gameBoard);
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