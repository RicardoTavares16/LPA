#include <iostream>
#include <cstdlib>

int nBlocks, blockHeight, maxHeight;

void solve(){
    

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
        std::cin >> nBlocks;
        std::cin >> blockHeight;
        std::cin >> maxHeight;
        //std::cout << nBlocks << " " << blockHeight << " " << maxHeight << std::endl;





    }

    
}
