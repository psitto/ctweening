#ifndef __EASING_H__
#define __EASING_H__

#define _USE_MATH_DEFINES
#include <math.h>

// thank you https://easings.net/

float ease_linear(float x)
{
	return x;
}

float ease_out_sine(float x)
{
	return sin(x * M_PI_2);
}

float ease_in_sine(float x)
{
	return 1 - cos(x * M_PI_2);
}

float ease_out_back(float x)
{
	static const float c1 = 1.70158;
	static const float c3 = 2.70158;
	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

#endif