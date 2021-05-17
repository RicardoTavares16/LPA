#include <iostream>
#include <cstdlib>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> adjMatrix;

void printAnswers(int questions)
{
    switch (questions)
    {
    case 1:
        std::cout << 0 << "\n";
        break;
    case 2:
        std::cout << 0 << 0 << "\n";
        break;
    case 3:
        std::cout << 0 << 0 << 0 << "\n";
        break;
    case 4:
        std::cout << 0 << 0 << 0 << 0 << "\n";
        break;
    default:
        std::cout << "Fudge\n";
        break;
    }
}
void resetMatrix(int vCount)
{
    adjMatrix.clear();
    adjMatrix.resize(vCount + 1);
}

int main()
{
    int testCases;
    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int poiCount, numberOfConnections, questions;
        std::cin >> poiCount >> numberOfConnections >> questions;

        resetMatrix(poiCount);

        for (int j = 0; j < numberOfConnections; j++)
        {
            int A, B, weight;
            std::cin >> A >> B >> weight;
            adjMatrix[A].push_back(std::make_pair(B, weight));
        }

        printf("Test Case: %d POIs: %d Conn: %d Questions: %d\n", i + 1, poiCount, numberOfConnections, questions);

        printAnswers(questions);
    }
}
