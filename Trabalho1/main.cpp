#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

int boardSize, maxMoves;
int best;
bool found = false;
bool didNothing = true;
int calls = 0;
const clock_t begin_time = clock();

typedef struct
{
    int tiles[20][20];
    int countTiles;
} matrix;

matrix gameBoard;

void printMatrix(matrix board)
{
    // int boardSizeCheck = sizeof(board[0])/sizeof(board[0][0]);
    // std::cout << "Size " << boardSizeCheck << "\n";
    int row, col;
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

matrix down(matrix board)
{
    int i, j, k, temp;
    didNothing = true;
    board.countTiles = 0;

    for (i = boardSize - 1; i >= 0; i--)
    {
        for (j = boardSize - 1; j >= 0; j--)
        {
            if (board.tiles[j][i])
            {
                board.countTiles++;
                temp = board.tiles[j][i];
                k = j - 1;
                while (k >= 0)
                {
                    if (board.tiles[k][i])
                    {
                        if (board.tiles[k][i] == board.tiles[j][i])
                        {
                            board.countTiles--;
                            didNothing = false;
                            board.tiles[j][i] *= 2;
                            board.tiles[k][i] = 0;
                            j = k;
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
                board.countTiles++;
                didNothing = false;
                temp = board.tiles[k][i];
                board.tiles[k][i] = board.tiles[j][i];
                board.tiles[j][i] = temp;
                j--;
            }
            else if (board.tiles[j][i])
            {
                board.countTiles++;
                j--;
            }
            k--;
        }
    }

    return board;
}

matrix up(matrix board)
{
    int i, j, k, temp;
    didNothing = true;
    board.countTiles = 0;

    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board.tiles[j][i])
            {
                board.countTiles++;
                temp = board.tiles[j][i];
                k = j + 1;
                while (k < boardSize)
                {
                    if (board.tiles[k][i])
                    {
                        if (board.tiles[k][i] == board.tiles[j][i])
                        {
                            board.countTiles--;
                            didNothing = false;
                            board.tiles[j][i] *= 2;
                            board.tiles[k][i] = 0;
                            j = k;
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
            if (board.tiles[j][i] == 0 && board.tiles[k][i] != 0)
            {
                board.countTiles++;
                didNothing = false;
                temp = board.tiles[k][i];
                board.tiles[k][i] = board.tiles[j][i];
                board.tiles[j][i] = temp;
                j++;
            }
            else if (board.tiles[j][i])
            {
                board.countTiles++;
                j++;
            }
            k++;
        }
    }

    return board;
}

matrix left(matrix board)
{
    int i, j, k, temp;
    didNothing = true;
    board.countTiles = 0;

    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board.tiles[i][j])
            {
                board.countTiles++;
                temp = board.tiles[i][j];
                k = j + 1;
                while (k < boardSize)
                {
                    if (board.tiles[i][k])
                    {
                        if (board.tiles[i][k] == board.tiles[i][j])
                        {
                            board.countTiles--;
                            didNothing = false;
                            board.tiles[i][j] *= 2;
                            board.tiles[i][k] = 0;
                            j = k;
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
            if (board.tiles[i][j] == 0 && board.tiles[i][k] != 0)
            {
                board.countTiles++;
                didNothing = false;
                temp = board.tiles[i][k];
                board.tiles[i][k] = board.tiles[i][j];
                board.tiles[i][j] = temp;
                j++;
            }
            else if (board.tiles[i][j])
            {
                board.countTiles++;
                j++;
            }
            k++;
        }
    }

    return board;
}

matrix right(matrix board)
{
    int i, j, k, temp;
    didNothing = true;
    board.countTiles = 0;
    for (i = boardSize - 1; i >= 0; i--)
    {
        for (j = boardSize - 1; j >= 0; j--)
        {
            if (board.tiles[i][j])
            {
                temp = board.tiles[i][j];
                k = j - 1;
                while (k >= 0)
                {
                    if (board.tiles[i][k])
                    {
                        if (board.tiles[i][k] == board.tiles[i][j])
                        {
                            didNothing = false;
                            board.tiles[i][j] *= 2;
                            board.tiles[i][k] = 0;
                            j = k;
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
            if (board.tiles[i][j] == 0 && board.tiles[i][k] != 0)
            {
                board.countTiles++;
                didNothing = false;
                temp = board.tiles[i][k];
                board.tiles[i][k] = board.tiles[i][j];
                board.tiles[i][j] = temp;
                j--;
            }
            else if (board.tiles[i][j])
            {
                board.countTiles++;
                j--;
            }
            k--;
        }
    }

    return board;
}

//check if sum of all tiles is power of 2
bool isPossible(matrix board)
{
    int sum = 0;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board.tiles[i][j] > 0)
            {
                sum += board.tiles[i][j];
            }
        }
    }

    if ((sum & (sum - 1)) == 0)
    {
        return true;
    }
    else
    {
        //printf("impossivel\n");
        return false;
    }
}

void solve2048(matrix board, int play)
{
    //calls++;
    //std::vector<matrix> movesVector;
    //std::cout << "Calling on " << play << " move\n";

    if (play < best)
    {
        matrix downMatrix = down(board);
        //if (is_solved(downMatrix))
        if (downMatrix.countTiles == 1)
        {
            // std::cout << "Count tiles: " << downMatrix.countTiles << "\n";
            if (play < best)
            {
                best = play;
            }
            found = true;
            return;
        }
        if (!didNothing && isPossible(downMatrix))
        {
            solve2048(downMatrix, play + 1);
            //movesVector.push_back(downMatrix);
        }
    }

    if (play < best)
    {
        matrix leftMatrix = left(board);
        //if (is_solved(leftMatrix))
        if (leftMatrix.countTiles == 1)
        {
            // std::cout << "Count tiles: " << leftMatrix.countTiles << "\n";
            if (play < best)
            {
                best = play;
            }
            found = true;
            return;
        }
        if (!didNothing && isPossible(leftMatrix))
        {
            solve2048(leftMatrix, play + 1);
            //movesVector.push_back(leftMatrix);
        }
    }

    if (play < best)
    {
        matrix upMatrix = up(board);
        //if (is_solved(upMatrix))
        if (upMatrix.countTiles == 1)
        {
            // std::cout << "Count tiles: " << upMatrix.countTiles << "\n";
            if (play < best)
            {
                best = play;
            }
            found = true;
            return;
        }
        if (!didNothing && isPossible(upMatrix))
        {
            solve2048(upMatrix, play + 1);
            //movesVector.push_back(upMatrix);
        }
    }

    if (play < best)
    {
        matrix rightMatrix = right(board);
        //if (is_solved(rightMatrix))
        if (rightMatrix.countTiles == 1)
        {
            // std::cout << "Count tiles: " << rightMatrix.countTiles << "\n";
            if (play < best)
            {
                best = play;
            }
            found = true;
            return;
        }
        if (!didNothing && isPossible(rightMatrix))
        {
            solve2048(rightMatrix, play + 1);
            //movesVector.push_back(rightMatrix);
        }
    }

    // if (play < best)
    // {
    //    std::sort(movesVector.begin(), movesVector.end(), compareByLength);
    //     for (std::vector<matrix>::iterator it = movesVector.begin(); it != movesVector.end(); ++it)
    //     {
    //         if (play < best)
    //         {
    //             solve2048(*it, play + 1);
    //         }
    //     }
    // }
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
                    if (inputNumber != 0)
                    {
                        gameBoard.countTiles++;
                    }
                }
            }
            //std::cout << "\n";
        }

        // printMatrix(gameBoard);
        // gameBoard = right(gameBoard);
        // std::cout << "After move\n";
        // printMatrix(gameBoard);
        // calls = 0;

        if (gameBoard.countTiles != 1)
        {
            //check if game can be solved with 1 move
            best = maxMoves;
            found = false;

            matrix downMatrix = down(gameBoard);
            matrix leftMatrix = left(gameBoard);
            matrix upMatrix = up(gameBoard);
            matrix rightMatrix = right(gameBoard);

            int min = std::min(downMatrix.countTiles, std::min(leftMatrix.countTiles, std::min(upMatrix.countTiles, rightMatrix.countTiles)));

            if (min == 1)
            {
                found = true;
                best = 1;
            }
            else
            {
                if (isPossible(gameBoard))
                {
                    solve2048(gameBoard, 1);
                }
            }
        }
        else
        {
            //Already solved
            best = 0;
            found = true;
        }

        if (found == false)
        {
            std::cout << "no solution\n";
        }
        else
        {
            std::cout << best << "\n";
        }

        // std::cout << "CALLS: " << calls << "\n";
    }
    //std::cout << "Total time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "\n";
}
