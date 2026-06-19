#ifndef __GRID_H__
#define __GRID_H__


#include "debug.h"

typedef struct {
	int *grid; // неотрицательные значения
	int n;
	int m;
	int is_success;
} Grid;

/* Функция создания сетки
 * Размер сетки (n * m)
 */
Grid create_grid(int n, int m);

/* Функция удаления сетки
 * Размер сетки (n * m)
 */
void delete_grid(Grid *grid);

/* Функция приведения ячеек сетки к одной строке
 * Размер сетки (n * m)
 */
char * str_grid(Grid grid);

/* Функция получения индекс ячейки из сетки
 * Размер сетки (n * m)
 */
int get_element_index(int i, int j, int n, int m);

/* Функция получения значения ячейки из сетки
 * Размер сетки (n * m)
 */
int get_element(int i, int j, Grid grid);


/* Функция установки значения ячейки в сетке
 * Размер сетки (n * m)
 * При неудачи вернется 0, при удаче 1
 */
int set_element(int value, int i, int j, Grid *grid);

#endif // __GRID_H__
