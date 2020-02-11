#include <iostream>
#include <string>

// ( -> 40 | ) -> 41 | [ -> 91 | ] -> 93
int eat_bracket(const std::string &string, int current_position) {

	if (current_position == static_cast<int>(string.length())) return - 1;

	if(string[current_position] == 40 || string[current_position] == 91) {
		char nom = string[current_position];
		int result = eat_bracket(string, current_position + 1);

		while (true) {
			if (result == -1) return -1;
			else if (string[result] == 41 && nom == 40) return result + 1;
			else if (string[result] == 93 && nom == 91) return result + 1;
			else if (string[result] == 40 || string[result] == 91) result = eat_bracket(string, result);
			else return -1;
		}
	}
	else{
		return current_position;
	}
}

int main( ) {
	int current_position;

	std::string input_string;
	std::getline(std::cin, input_string);
	while(std::getline(std::cin, input_string)) {
		current_position = 0;
		do {
			if (input_string[0]=='\0') break;
			current_position = eat_bracket(input_string, current_position);
			if (input_string[current_position] == 41 || input_string[current_position] == 93) current_position = -1;
		} while (current_position < static_cast<int>(input_string.length())  && current_position != -1);
		std::cout << ((current_position == -1) ? "No" : "Yes") << std::endl;
	};

	return 0;
}
