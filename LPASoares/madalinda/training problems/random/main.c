#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20

int DP[number_rows][number_rows];

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

void DP_bottom_up(int number_rows) {

	for (int i=0; i<number_rows; i++) {
		for (int j=0; j<i; j++) {
			DP[i, j] = P[i, j] + max (DP[i-1, j], DP[i-1, j-1]);
		}
	}
}

int main(int argc, char * argv[]) {
	//reads input

	//the first row indicates the number of test cases
	char* buffer;
	char stdin_buffer[MAX];
	int number_inputs, number_rows;
	int matrix[MAX][MAX];
	fgets(stdin_buffer, MAX, stdin);
	
	buffer = stdin_buffer;
	number_inputs = (int) strtol(buffer, &buffer, 10);
	printf("number_inputs = %d\n", number_inputs);

	for (int i=0; i<number_inputs; i++) {
		//the next row indicates the number of rows of the matrix

		fgets(stdin_buffer, MAX, stdin);
		buffer = stdin_buffer;

		number_rows = (int) strtol(buffer, &buffer, 10);
		printf("number_rows = %d\n", number_rows);

		for (int j=0; j<number_rows; j++) {
			fgets(stdin_buffer, MAX, stdin);
			buffer = stdin_buffer;

			for (int k=0; k<number_rows; k++) {
				matrix[j][k] = (int) strtol(buffer, &buffer, 10);
				printf("matrix[%d][%d] = %d\n", j, k, matrix[j][k]);
			}
		}
	}

	//building the matrix
	DP_bottom_up(number_rows);

	printf("DP[1][1] = %d\n", DP[0][0]);


}