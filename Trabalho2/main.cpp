#include <iostream>
#include <cstdlib>

int nBlocks, blockHeight, maxHeight;
int totalComb = 0;
int x[501];

int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
  return mod_add(a, -b, mod);
}

void solve()
{
    for (int i = 3; i < nBlocks; i++)
    {

        if (i == 3)
        {
            x[3] = blockHeight - 1;
        }
        else
        {
            // int minHeight = 1;
            // for (int j = 1; j < i / 2; j++)
            // {
            //     for(int k = 0; blockHeight - 1; k++){
            //         if((minHeight + k + blockHeight) <= maxHeight){
            //             totalComb++;
            //         }
            //     }
            //     minHeight++;
            // }
        }
    }
}

int main()
{
    // An arc consists of 3 ≤ k ≤ n blocks placed consecutively, such that the index i = 1 denotes the first block, i = 2 the second block, and so on until the last block i = k;
    // The first and last blocks must be placed on the floor, that is h1 = 0 and hk = 0, where hi denotes the height from the floor to the base of the block;
    // The ith block must share at least 1 height with its neighbors, formally hi + 1 − h < hi < hi + 1 + h for i > 1;
    // The values of hi should be monotonically increasing, up to a certain block, and then monotonically decreasing. Formally, there exists a block l such that h1 < ⋯ < hl > ⋯ > hk. Note that two consecutive blocks cannot have the same value of hi.

    int testCases;

    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        totalComb = 0;
        std::cin >> nBlocks;
        std::cin >> blockHeight;
        std::cin >> maxHeight;
        //std::cout << nBlocks << " " << blockHeight << " " << maxHeight << std::endl;

        solve();

        std::cout << totalComb << "\n";
    }
}
