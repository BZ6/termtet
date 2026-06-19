#include <string.h>
#include <stdlib.h>

#include "grid.h"

/* Функция создания сетки
 * Размер сетки (n * m)
 */
Grid create_grid(int n, int m)
{
	int size = n * m;
	int *grid;

	grid = (int *)calloc(size, sizeof(int) * size);
	if (!grid) return (Grid)
		{
			.grid = NULL,
			.n = n,
			.m = m,
			.is_success = 0
		};

	return (Grid)
		{
			.grid = grid,
			.n = n,
			.m = m,
			.is_success = 1
		};
}

/* Функция удаления сетки
 * Размер сетки (n * m)
 */
void delete_grid(Grid *grid)
{
	grid->is_success = 0;
	if (grid && grid->grid)
	{
		free(grid->grid);
		grid->grid = NULL;
	}
}

/* Функция приведения ячеек сетки к одной строке
 * Размер сетки (n * m)
 */
char * str_grid(Grid grid)
{
	char func_name[] = "str_grid";

	int n = grid.n, m = grid.m;
	int i, j, index;
	char *result, *str;

	print_debug(func_name, "allocation memory start");

	str = (char *)malloc(sizeof(char) * (m + 1));
	if (!str) return NULL;
	result = (char *)malloc(sizeof(char) * (n * (m + 1) + 1));
	if (!result) return NULL;

	print_debug(func_name, "allocation memory finished");
	print_debug(func_name, "grid convertation start");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			index = get_element_index(i, j, n, m);

			if (index != -1)
				str[j] = grid.grid[index] <= 0 ? '0' : 'X';
		}
		str[m] = '\n';

		memmove(result + (i * (m + 1)), str, m + 1);
	}

	print_debug(func_name, "grid convertation finished");

	result[n * (m + 1)] = '\0';
	free(str);

	return result;
}

/* Функция получения индекс ячейки из сетки
 * Размер сетки (n * m)
 */
int get_element_index(int i, int j, int n, int m)
{
	if (0 <= i && i < n && 0 <= j && j < m)
		return i * m + j;
	return -1;
}

/* Функция получения значения ячейки из сетки
 * Размер сетки (n * m)
 * При неудачи вернется -1
 */
int get_element(int i, int j, Grid grid)
{
	int index = get_element_index(i, j, grid.n, grid.m);

	if (index == -1) return -1;
	return grid.grid[index];
}

/* Функция установки значения ячейки в сетке
 * Размер сетки (n * m)
 * При неудачи вернется 0, при удаче 1
 */
int set_element(int value, int i, int j, Grid *grid)
{
	int index = get_element_index(i, j, grid->n, grid->m);

	if (value < 0) return 0;
	if (index == -1) return 0;

	grid->grid[index] = value;

	return 1;
}

