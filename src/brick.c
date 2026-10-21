#include "brick.h"

#define BRICK_WIDTH 4
#define BRICK_HEIGHT 2

/* Функция создания палки
 */
Grid brick_create_stick();

/* Функция создания квадрата
 */
Grid brick_create_square();

/* Функция создания блока
 */
Brick brick_create(BrickType type)
{
	Brick brick = {
		.center_x = 0,
		.center_y = 0,
		.type = type
	};

	switch (type)
	{
		case BRICK_SQUARE:
			brick.func_map = brick_create_square;
		case BRICK_STICK:
			brick.func_map = brick_create_stick;
		default:
			brick.func_map = brick_create_square;
	}

	return brick;
}


/* Функция создания палки
 */
Grid brick_create_stick()
{
	Grid grid = create_grid(BRICK_HEIGHT, BRICK_WIDTH);

	// Все по нулям изначально
	set_element(1, 0, 0, &grid);
	set_element(1, 0, 1, &grid);
	set_element(1, 0, 2, &grid);
	set_element(1, 0, 3, &grid);

	return grid;
}

/* Функция создания квадрата
 */
Grid brick_create_square()
{
	Grid grid = create_grid(BRICK_HEIGHT, BRICK_WIDTH);

	// Все по нулям изначально
	set_element(1, 0, 0, &grid);
	set_element(1, 0, 1, &grid);
	set_element(1, 1, 0, &grid);
	set_element(1, 1, 1, &grid);

	return grid;
}
