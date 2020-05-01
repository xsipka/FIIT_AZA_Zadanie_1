#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC optimize ("O3")

#define TRUE 1
#define FALSE 0

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif


typedef struct map_vertex {
	int inc_length;
	int dec_length;
	int total_length;
	int value;
	short visited;
} MAP_VERTEX;

struct map_vertex **map = NULL;
int longest_path = 0;



int in_area(int row, int col, int curr_row, int curr_col) {

	if (curr_row < 0 || curr_row >= row || curr_col < 0 || curr_col >= col) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}


int find_decreasing_path(int curr_row, int curr_col, int row, int col) {
	int right = INT_MIN,
		left  = INT_MIN,
		up    = INT_MIN,
		down  = INT_MIN;

	if (in_area(row, col, curr_row, curr_col) == FALSE) {
		return 0;
	}

	if (map[curr_row][curr_col].dec_length != NULL || map[curr_row][curr_col].visited == TRUE) {
		return map[curr_row][curr_col].dec_length;
	}
	map[curr_row][curr_col].visited = TRUE;
	

	if (curr_col < col - 1 && (map[curr_row][curr_col].value >= map[curr_row][curr_col + 1].value)) {
		right = 1 + find_decreasing_path(curr_row, curr_col + 1, row, col);
	}

	if (curr_col > 0 && (map[curr_row][curr_col].value >= map[curr_row][curr_col - 1].value)) {
		left = 1 + find_decreasing_path(curr_row, curr_col - 1, row, col);
	}

	if (curr_row > 0 && (map[curr_row][curr_col].value >= map[curr_row - 1][curr_col].value)) {
		up = 1 + find_decreasing_path(curr_row - 1, curr_col, row, col);
	}

	if (curr_row < row - 1 && (map[curr_row][curr_col].value >= map[curr_row + 1][curr_col].value)) {
		down = 1 + find_decreasing_path(curr_row + 1, curr_col, row, col);
	}
	map[curr_row][curr_col].visited = FALSE;

	return map[curr_row][curr_col].dec_length = max(right, max(left, max(up, max(down, 1))));
}


int find_increasing_path(int curr_row, int curr_col, int row, int col, int counter) {
	int right = INT_MIN, 
		left  = INT_MIN, 
		up    = INT_MIN, 
		down  = INT_MIN;

	if (in_area(row, col, curr_row, curr_col) == FALSE) {
		return 0;
	}

	if (map[curr_row][curr_col].inc_length != NULL || map[curr_row][curr_col].visited == TRUE) {
		map[curr_row][curr_col].inc_length;
	}
	counter += 1;

	if (curr_col < col - 1 && (map[curr_row][curr_col].value <= map[curr_row][curr_col + 1].value)) {
		map[curr_row][curr_col].visited = TRUE;
		right = 1 + find_increasing_path(curr_row, curr_col + 1, row, col, counter);
	}

	if (curr_col > 0 && (map[curr_row][curr_col].value <= map[curr_row][curr_col - 1].value)) {
		map[curr_row][curr_col].visited = TRUE;
		left = 1 + find_increasing_path(curr_row, curr_col - 1, row, col, counter);
	}

	if (curr_row > 0 && (map[curr_row][curr_col].value <= map[curr_row - 1][curr_col].value)) {
		map[curr_row][curr_col].visited = TRUE;
		up = 1 + find_increasing_path(curr_row - 1, curr_col, row, col, counter);
	}

	if (curr_row < row - 1 && (map[curr_row][curr_col].value <= map[curr_row + 1][curr_col].value)) {
		map[curr_row][curr_col].visited = TRUE;
		down = 1 + find_increasing_path(curr_row + 1, curr_col, row, col, counter);
	}

	map[curr_row][curr_col].visited = FALSE;
	find_decreasing_path(curr_row, curr_col, row, col);
	
	if (longest_path <= counter + map[curr_row][curr_col].dec_length - 1) {
		longest_path = counter + map[curr_row][curr_col].dec_length - 1;
	}

	max(counter + map[curr_row][curr_col].dec_length - 1, 5);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j].dec_length = NULL;
		}
	}
	
	map[curr_row][curr_col].inc_length = max(right, max(left, max(up, max(down, 1))));
	return longest_path;
}


int find_longest_path(int row, int col) {
	int length = 1;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j].inc_length == NULL) {
				longest_path = find_increasing_path(i, j, row, col, 0);
			}
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					map[i][j].visited = FALSE;
				}
			}
			length = max(length, longest_path);
		}
	}

	return length;
}


void calculate_value(int index, int *value_seq) {

	value_seq[index] = (value_seq[index - 1] * 75) % 65537;
	return;
}


int main() {
	int num_of_maps,
		first_value,
		row, col;
	int *value_seq;


	scanf("%d", &num_of_maps);

	for (int curr_map = 0; curr_map < num_of_maps; curr_map++) {

		scanf("%d %d %d", &first_value, &row, &col);
		value_seq = (int *)malloc((row * col) * sizeof(int));
		value_seq[0] = first_value;

		map = (MAP_VERTEX **)malloc(row * sizeof(MAP_VERTEX *));
		for (int i = 0; i < row; i++) {
			map[i] = (MAP_VERTEX *)malloc(col * sizeof(MAP_VERTEX));
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				calculate_value(i * col + j + 1, value_seq);
				map[i][j].value = value_seq[i * col + j + 1];		
				map[i][j].visited = FALSE;
				map[i][j].inc_length = NULL;
				map[i][j].dec_length = NULL;
				//printf("%d ", map[i][j].value);
			}
			//printf("\n");
		}
		printf("%d\n", find_longest_path(row, col));
		longest_path = 0;
		//free(map);
	}

	

	return 0;
}
