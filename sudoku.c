#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define UPPER 9
#define LOWER 1


void draw_board();
void title_page();
bool check_if_valid(int user_input, int row, int column, int sudoku_stored_values[9][9]);
bool check_values_horizontal(int user_input, int row, int sudoku_stored_values[9][9]);
bool check_values_vertical(int user_input, int column, int sudoku_stored_values[9][9]);
bool check_values_box(int user_input, int row, int column, int sudoku_stored_values[9][9]);
int user_input();
void sudoku_generator();
void del(int arr[], int *n, int key);
// void print_sudoku_board(int sudoku_stored_values[9][9])
// {
// 	for (int i = 0; i < 9; i++)
// 	{
// 		for(int j = 0; j < 9; j++)
// 		{
// 			printf ("%d ", sudoku_stored_values[i][j]);
// 		}
// 		printf ("\n");
// 	}
// }

// struct sudoku_board
// {
// 	int board_struct[9][9];
// };


// struct sudoku_board ret_sudoku_board()
// {
// 	struct sudoku_board board_places = 
// 		{
// 							 {{0, 2, 3, 7, 5, 1, 4, 9, 8},
// 							  {8, 4, 9, 6, 2, 3, 5, 7, 1},
// 							  {7, 5, 1, 4, 8, 9, 6, 3, 2},
// 							  {3, 7, 2, 8, 4, 5, 1, 6, 9},
// 							  {9, 8, 4, 3, 1, 6, 7, 2, 5},
// 							  {5, 1, 6, 9, 7, 2, 8, 4, 3},
// 							  {1, 3, 8, 2, 6, 7, 9, 5, 4},
// 							  {2, 6, 5, 1, 9, 4, 3, 8, 7},
// 							  {4, 9, 7, 5, 3, 8, 2, 1, 6}}
// 		};

// 	return board_places;	
// }


int main()
{
	// title_page();
	// int sudoku_board[9][9] = {{0, 2, 3, 7, 5, 1, 4, 9, 8},
	// 						  {8, 4, 9, 6, 2, 3, 5, 7, 1},
	// 						  {7, 5, 1, 4, 8, 9, 6, 3, 2},
	// 						  {3, 7, 2, 8, 4, 5, 1, 6, 9},
	// 						  {9, 8, 4, 3, 1, 6, 7, 2, 5},
	// 						  {5, 1, 6, 9, 7, 2, 8, 4, 3},
	// 						  {1, 3, 8, 2, 6, 7, 9, 5, 4},
	// 						  {2, 6, 5, 1, 9, 4, 3, 8, 7},
	// 						  {4, 9, 7, 5, 3, 8, 2, 1, 6}};
	
	// for (int i = 0; i < 9; i++)
	// {
	// 	for(int j = 0; j < 9; j++)
	// 	{
	// 		printf ("%d ", sudoku_board[i][j]);
	// 	}
	// 	printf ("\n");
	// }

	// int input_from_user = user_input();

	// if(true)
	// {
	// 	printf("It is valid\n");
	// }
	// else
	// {
	// 	printf("Not valid\n");
	// }
	sudoku_generator();
	return 0;
}


void sudoku_generator()
{
	int count = 9;
	int array_length = 0;
	
	int matrix[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0, 0}};
	srand(time(NULL));
	int rand_int_index;
	for(int i = 0; i < 9; i++)
	{
		int valid_numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		array_length = sizeof(valid_numbers)/(sizeof(valid_numbers[0]));
		for(int j = 0; j < 9; j++)
		{
			while(true)
			{
				
				rand_int_index = rand() % count;
				if(check_if_valid(valid_numbers[rand_int_index], i, j, matrix))
				{
					matrix[i][j] = valid_numbers[rand_int_index];
					del(valid_numbers, &array_length, valid_numbers[rand_int_index]);
					--count;
					break;
				}
			}
		}
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

}

void del(int arr[], int *n, int key) {
  
  	// Find the element
  	int i = 0;
  	while (arr[i] != key) i++;
  	
    // Shifting the right side elements one
  	// position towards left
    for (int j = i; j < *n - 1; j++) {
        arr[j] = arr[j + 1];
    }
  
  	// Decrease the size
    (*n)--; 
}

bool check_if_valid (int user_input, int row, int column, int sudoku_stored_values[9][9]) //Checks if the given input is valid according to sudoku rules
{
	bool box_check, horizontal_check, vertical_check;
	box_check = horizontal_check = vertical_check = false;

	if (row < 3 && column < 3)
	{
		row = 0;
		column = 0;
	}

	else if (row < 3 && column > 2 && column < 6)
	{
		row = 0;
		column = 3;
	}

	else if (row < 3 && column > 5)
	{
		row = 0;
		column = 6;
	}

	else if (row > 2 && row < 6 && column <3)
	{
		row = 3;
		column = 0;
	}

	else if (row > 2 && row < 6 && column > 2 && column < 6)
	{
		row = 3;
		column = 3;
	}

	else if (row > 2 && row < 6 && column > 5)
	{
		row = 3;
		column = 6;
	}

	else if (row > 5 && column < 3)
	{
		row = 6;
		column = 0;
	}

	else if (row > 5 && column > 2 && column < 6)
	{
		row = 6;
		column = 3;
	}

	else if (row > 5 && column > 5)
	{
		row = 6;
		column = 6;
	}
	
	//Multiple checks for validity of user input

	box_check = check_values_box(user_input, row, column, sudoku_stored_values); 
	horizontal_check = check_values_horizontal(user_input, row, sudoku_stored_values);
	vertical_check = check_values_vertical(user_input, column, sudoku_stored_values);

	if(box_check && horizontal_check && vertical_check)
	{
		return true;
	}
	return false;
}


bool check_values_horizontal(int user_input, int row, int sudoku_stored_values[9][9]) //Checks horizontally if the value is valid or not
{
	for(int a = 0; a < 9; a++)
	{
		if(user_input == sudoku_stored_values[row][a])
		{
			return false;
		}
	}
	return true;
}


bool check_values_vertical(int user_input, int column, int sudoku_stored_values[9][9])
{
	for(int a = 0; a < 9; a++)
	{
		if(user_input == sudoku_stored_values[a][column])
		{
			return false;
		}
	}
	return true;
}


bool check_values_box(int user_input, int row, int column, int sudoku_stored_values[9][9])
{	
	for(int i = row; i < row + 3; i++)
	{
		for(int j = column; j < column + 3; j++)
		{
			if(user_input == sudoku_stored_values[i][j])
			{
				return false;
			}
		}
	}
	return true;
}


int user_input()
{
	int user_input;
	printf("Enter your input\n");
	scanf("%d", &user_input);
	
	return user_input;
}


void draw_board()
{
	for(int i = 0; i < 10; i++)
	{
		for(int i = 0; i < 9; i++)
		{
			printf(":----:");
		}
		
		printf("\n");

		for(int i = 0; i < 9; i++)
		{
			printf(":    :");
		}

		printf("\n");
	}
}


void title_page()
{
	printf("Welcome to sudoku!!!\n");
	printf("You may start\n");
}
