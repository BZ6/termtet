#ifndef __BRICK_H__
#define __BRICK_H__


#include "game_struct.h"

typedef enum {
	BRICK_MOVE_DOWN = 0,
	BRICK_MOVE_RIGHT,
	BRICK_MOVE_LEFT,
	BRICK_MOVE_ROTATE
} BrickMove;

typedef enum {
	BRICK_SQUARE = 0,
	BRICK_STICK,
	//BRICK_Z,
} BrickType;

typedef Grid (*BrickMap)(void);

typedef struct {
	int center_x, center_y;
	BrickType type;
	BrickMap func_map;
} Brick;

/* Функция двжения блока
 */
void brick_move(Brick *brick, Game *game, BrickMove move);

/* Функция создания блока
 */
Brick brick_create(BrickType type);

#endif // __BRICK_H__
