#include "game_threads.h"
#include "game_input.h"
#include "game_logic.h"

#include "game.h"

/* Функция запуска процесса игры
 */
void run_game(void)
{
	thrd_t game_input_thread, game_logic_thread;
	init_message();

	if (mtx_init(&mtx, mtx_plain) != thrd_success) {
		printf("Failed to init mutex.\n");
		return;
	}

	if (thrd_create(&game_input_thread, game_input, NULL) != thrd_success)
	{
		printf("Failed to create thread game_input_thread.\n");
		return;
	}
	if (thrd_create(&game_logic_thread, game_logic, NULL) != thrd_success)
	{
		printf("Failed to create thread game_logic_thread.\n");
		return;
	}

	thrd_join(game_input_thread, NULL);
	thrd_join(game_logic_thread, NULL);

	mtx_destroy(&mtx);
}
