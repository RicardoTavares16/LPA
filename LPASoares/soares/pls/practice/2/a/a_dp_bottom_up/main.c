#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 300

#define MAX_SIZE 101

int matix[MAX_SIZE][MAX_SIZE];

int cache[MAX_SIZE][MAX_SIZE];

int max(int a, int b) {
	return a > b ? a : b;
}

int bottom_up(int size){
	int i, j, best = 0;

	for(i = 0; i < size; i++) {
		for(j = 0; j <= i; j++) {
			if (i == 0) cache[i][j] = matix[i][j];
			else if (j == 0)  cache[i][j] = matix[i][j] + cache[i-1][j];
			else cache[i][j] = matix[i][j] + max(cache[i-1][j],cache[i - 1][j - 1]);
		}
	}
	for (i = 0; i < size; i++) {
		best = max(best, cache[size-1][i]);
	}

	return best;
}

int main() {
	char stdin_buffer[BUFFER_SIZE], *buffer;
	int i, j, k;
	int number_test_cases = 0, test_case_depth = 0;

	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_test_cases = (int) strtol(buffer, &buffer, 10);

	for (i = 0; i < number_test_cases; i++) {

		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		test_case_depth = (int) strtol(buffer, &buffer, 10);

		for (j = 0; j < test_case_depth; j++) {

			fgets(stdin_buffer, BUFFER_SIZE, stdin);
			buffer = stdin_buffer;

			for (k = 0; k <= j; k++) {

				matix[j][k] = (int) strtol(buffer, &buffer, 10);

			}
		}

		printf("%d\n", bottom_up(test_case_depth));
	}

	return 0;
}
