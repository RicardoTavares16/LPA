#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>

int number_of_problems, number_of_coins;
int total_sum = 0;

int coins[100];

bool *value_matrix[100];

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void fill_value_matrix() {

	for(int t = 0; t <= total_sum; t++) value_matrix[0][t] = false;

	for(int t = 0; t <= number_of_coins; t++) value_matrix[t][0] = true;

	for(int i = 1; i <= number_of_coins; i++) {

		for(int t = 0; t <= static_cast<int>((floor(total_sum)/2)); t++) {

			if (coins[i] > t) value_matrix[i][t] = value_matrix[i - 1][t];

			else value_matrix[i][t] = (value_matrix[i - 1][t] || value_matrix[i - 1][t - coins[i]]);

		}
	}
}

int main() {

	std::cin >> number_of_problems;

	for (int i = 0; i < number_of_problems; i++) {

		std::cin >> number_of_coins;
		total_sum = 0;

		for(int j = 0 ; j < number_of_coins; j++) {
			std::cin >> coins[j];
			total_sum += coins[j];
		}

		for(int j = 0 ; j <= number_of_coins; j++) {
			value_matrix[j] = (bool*) std::malloc(static_cast<int>(floor(total_sum/2) + 1) * sizeof(int) );
		}

		fill_value_matrix();

		for(int j = static_cast<int>((floor(total_sum)/2)); j >= 0; j-- ) {

			if(value_matrix[number_of_coins][j]) {
				std::cout << total_sum - (2*j)  << std::endl;
				break;
			}
		}

		for(int j = 0 ; j <= number_of_coins; j++) {
			free(value_matrix[j]);
		}
	}

	return 0;
}
