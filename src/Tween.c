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
	*p->target = p->motion->to;
	p->elapsed_time = p->duration;
	p->running = false;
}

void twn_reset(twn_Player* p)
{
	*p->target = p->motion->from;
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
		p->elapsed_time = p->duration;
		*p->target = motion->to;
		p->running = false;
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

bool twn_is_active(twn_Player* p)
{
	return p->running;
}