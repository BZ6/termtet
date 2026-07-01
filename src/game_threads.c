#include <stdio.h>

#include "game_threads.h"

ThreadMessage message;
mtx_t mtx;

/* Функция инициализации сообщения
 */
void init_message(void)
{
	message = MSG_UNDEFINED;
}

/* Функция для записи сообщения между потоками
 */
void write_message(mtx_t *mtx, ThreadMessage msg)
{
	mtx_lock(mtx);
	message = msg;
	mtx_unlock(mtx);
}

/* Функция для чтения сообщения между потоками
 */
ThreadMessage read_message(mtx_t *mtx)
{
	ThreadMessage msg;

	mtx_lock(mtx);
	msg = message;
	message = MSG_UNDEFINED;
	mtx_unlock(mtx);

	return msg;
}
