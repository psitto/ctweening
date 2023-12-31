#ifndef __TWEEN_H__
#define __TWEEN_H__

#include <stdlib.h>
#include <stdbool.h>

#define TWN_MOTION_NAME_LENGTH 32

typedef struct twn_Player twn_Player;
typedef float (*easing_fp)(float);
typedef void (*callback_fp)(twn_Player*);
typedef struct twn_Motion
{
	float from, to;
	easing_fp easing;
	char name[TWN_MOTION_NAME_LENGTH];
} twn_Motion;

twn_Player* twn_make_player();
twn_Player* twn_make_player_ex(float* target, twn_Motion* motion, time_t duration);
void twn_play(twn_Player* p);
void twn_pause(twn_Player* p);
void twn_resume(twn_Player* p);
void twn_end(twn_Player* p);
void twn_end_no_callback(twn_Player* p);
void twn_reset(twn_Player* p);
void twn_update(twn_Player* p, time_t dt);
float* twn_get_target(twn_Player* p);
void twn_set_target(twn_Player* p, float* target);
twn_Motion* twn_get_motion(twn_Player* p);
void twn_set_motion(twn_Player* p, twn_Motion* motion);
time_t twn_get_elapsed_time(twn_Player* p);
void twn_jump(twn_Player* p, time_t point);
time_t twn_get_duration(twn_Player* p);
void twn_set_duration(twn_Player* p, time_t duration);
callback_fp twn_get_callback(twn_Player* p);
void twn_set_callback(twn_Player* p, callback_fp cb_f);
int twn_get_player_id(twn_Player* p);
bool twn_is_active(twn_Player* p);
static int get_unique_player_id();

#endif