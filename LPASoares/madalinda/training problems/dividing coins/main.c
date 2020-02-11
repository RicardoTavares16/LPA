#include <stdio.h>
#include <math.h>

int coins[1000];
int DP[1000][1000];


int fairshare(int number_coins) {

    float total = 0;
    int half, k, i, j;

    for (i = 0; i < number_coins; i++) {
        DP[i][0] = 1;
        total += coins[i];
    }

    half = (int) ceil(total / 2);
    for (j=1; j<=half; j++) {
        DP[0][j] = 0;
    }

    for (i = 1; i < number_coins; i++) {
        for (j = 0; j <= half; j++) {

            if (coins[i] > j) {
                DP[i][j] = DP[i - 1][j];
            } else {
                if (DP[i-1][j] == 1 || DP[i-1][j - coins[i]] == 1) {
                    DP[i][j] = 1;
                }
                else DP[i][j] = 0;
            }
        }
    }

    k = half;
    while (k >= 0) {
        if (DP[number_coins-1][k] == 1) break;
        k--;
    }

    return total - k*2;
}


int main(int argc, char* argv[]) {

    int number_problems, number_coins, coin, res, i, j;

    scanf("%d", &number_problems);

    for (i=0; i<number_problems; i++) {

        scanf("%d", &number_coins);

        for (j=0; j<number_coins; j++) {
            scanf("%d ", &coin);
            coins[j] = coin;
        }

        res = fairshare(number_coins);
        printf("%d\n", res);
    }

    return 0;
}
