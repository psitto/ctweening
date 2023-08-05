#ifndef __TWEEN_H__
#define __TWEEN_H__

#include <stdlib.h>
#include <stdbool.h>

typedef float (*easing_fp)(float);
typedef struct twn_Player twn_Player;
typedef struct twn_Motion
{
	float from, to;
	easing_fp easing;
} twn_Motion;

twn_Player* twn_make_player(float* target, twn_Motion* motion, time_t duration);
void twn_play(twn_Player* player);
void twn_pause(twn_Player* player);
void twn_resume(twn_Player* player);
void twn_end(twn_Player* player);
void twn_update(twn_Player* player, time_t dt);
bool twn_is_active(twn_Player* player);

#endif