#include <stdio.h>
#include <stdlib.h>

int visit_cell(int **board, int x, int y, int number_moves) {
	int distinct_cells_visited = 0;

	--number_moves;

	if ( (x > 400) | (y > 400) | (x < 0) | (y < 0) ) {
		return 0;
	}
	if (board[x][y] == 0) {
		board[x][y] = 1;
		++distinct_cells_visited;
	}
	if (number_moves >= 0) {
		distinct_cells_visited += visit_cell(board, x-2, y+1, number_moves);
		distinct_cells_visited += visit_cell(board, x-2, y-1, number_moves);
		distinct_cells_visited += visit_cell(board, x-1, y+2, number_moves);
		distinct_cells_visited += visit_cell(board, x-1, y-2, number_moves);
		distinct_cells_visited += visit_cell(board, x+1, y+2, number_moves);
		distinct_cells_visited += visit_cell(board, x+1, y-2, number_moves);
		distinct_cells_visited += visit_cell(board, x+2, y+1, number_moves);
		distinct_cells_visited += visit_cell(board, x+2, y-1, number_moves);
	}
	return distinct_cells_visited;
}

int main() {
	int i, numberKnights, x, y, number_moves, distinct_cells_visited = 0, board_max_size = 401, **board;

	board = (int**) malloc(board_max_size * sizeof(int));

	for (i = 0; i < board_max_size; ++i) {
		board[i] = (int*) calloc((size_t) board_max_size, sizeof(int));
	}

	scanf("%d", &numberKnights);

	for (i = 0; i < numberKnights; ++i)	{
		scanf("%d %d %d", &x, &y, &number_moves);
		x += 200;
		y += 200;
		distinct_cells_visited += visit_cell(board, x, y, number_moves);
	}

	printf("%d\n", distinct_cells_visited);
	return 0;
}