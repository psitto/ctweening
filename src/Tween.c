#include "Tween.h"

struct twn_Player
{
	float* target;
	twn_Motion* motion;
	time_t duration, elapsed_time;
	callback_fp callback;
	int id;
	bool running;
};

twn_Player* twn_make_player()
{
	twn_Player* p = calloc(1, sizeof(twn_Player));
	if (!p)
	{
		return NULL;
	}
	p->id = get_unique_player_id();
	return p;
}

twn_Player* twn_make_player_ex(float* target, twn_Motion* motion, time_t duration)
{
	twn_Player* p = malloc(sizeof(twn_Player));
	if (!p)
	{
		return NULL;
	}
	p->target = target;
	p->motion = motion;
	twn_set_duration(p, duration);
	p->elapsed_time = 0;
	p->running = false;
	p->callback = NULL;
	p->id = get_unique_player_id();
	return p;
}

void twn_play(twn_Player* p)
{
	*p->target = p->motion->from;
	p->elapsed_time = 0;
	p->running = true;
}

void twn_pause(twn_Player* p)
{
	p->running = false;
}

void twn_resume(twn_Player* p)
{
	p->running = true;
}

void twn_end(twn_Player* p)
{
	twn_end_no_callback(p);
	if (p->callback)
	{
		p->callback(p);
	}
}

void twn_end_no_callback(twn_Player* p)
{
	*p->target = p->motion->to;
	p->elapsed_time = p->duration;
	p->running = false;
}

void twn_reset(twn_Player* p)
{
	if (p->motion)
	{
		*p->target = p->motion->from;
	}
	p->elapsed_time = 0;
	p->running = false;
}

void twn_update(twn_Player* p, time_t dt)
{
	twn_Motion* motion = p->motion;
	if (!p->running)
	{
		return;
	}
	p->elapsed_time += dt;
	if (p->elapsed_time >= p->duration)
	{
		twn_end(p);
		return;
	}
	if (p->elapsed_time < 0)
	{
		p->elapsed_time += p->duration;
	}
	*p->target = motion->from + (motion->to - motion->from) * motion->easing((float)p->elapsed_time / p->duration);
}

float* twn_get_target(twn_Player* p)
{
	return p->target;
}

void twn_set_target(twn_Player* p, float* target)
{
	p->target = target;
	twn_reset(p);
}

twn_Motion* twn_get_motion(twn_Player* p)
{
	return p->motion;
}

void twn_set_motion(twn_Player* p, twn_Motion* motion)
{
	twn_reset(p);
	p->motion = motion;
}

time_t twn_get_elapsed_time(twn_Player* p)
{
	return p->elapsed_time;
}

void twn_jump(twn_Player* p, time_t point)
{
	p->elapsed_time = point;
}

time_t twn_get_duration(twn_Player* p)
{
	return p->duration;
}

void twn_set_duration(twn_Player* p, time_t duration)
{
	p->duration = duration > 0 ? duration : 0;
}

callback_fp twn_get_callback(twn_Player* p)
{
	return p->callback;
}

void twn_set_callback(twn_Player* p, callback_fp cb_f)
{
	p->callback = cb_f;
}

int twn_get_player_id(twn_Player* p)
{
	return p->id;
}

bool twn_is_active(twn_Player* p)
{
	return p->running;
}

static int get_unique_player_id()
{
	static int p_id = 0;
	return p_id++;
}