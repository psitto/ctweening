#include "Tween.h"

struct twn_Player
{
	float* target;
	twn_Motion* motion;
	time_t duration, elapsed_time;
	bool running;
};

twn_Player* twn_make_player(float* target, twn_Motion* motion, time_t duration)
{
	twn_Player* player = malloc(sizeof(twn_Player));
	if (!player)
	{
		return NULL;
	}
	player->target = target;
	player->motion = motion;
	player->duration = duration;
	player->elapsed_time = 0;
	player->running = false;
	return player;
}

void twn_play(twn_Player* player)
{
	*player->target = player->motion->from;
	player->elapsed_time = 0;
	player->running = true;
}

void twn_pause(twn_Player* player)
{
	player->running = false;
}

void twn_resume(twn_Player* player)
{
	player->running = true;
}

void twn_end(twn_Player* player)
{
	*player->target = player->motion->to;
	player->elapsed_time = player->duration;
	player->running = false;
}
void twn_update(twn_Player* player, time_t dt)
{
	twn_Motion* motion = player->motion;
	if (!player->running)
	{
		return;
	}
	player->elapsed_time += dt;
	if (player->elapsed_time >= player->duration)
	{
		player->elapsed_time = player->duration;
		*player->target = motion->to;
		player->running = false;
		return;
	}
	*player->target = motion->from + (motion->to - motion->from) * motion->easing((float)player->elapsed_time / player->duration);
}

bool twn_is_active(twn_Player* player)
{
	return player->running;
}