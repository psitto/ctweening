#ifndef __EASING_H__
#define __EASING_H__

#define _USE_MATH_DEFINES
#include <math.h>

// thank you https://easings.net/

float ease_linear(float x);
float ease_out_sine(float x);
float ease_in_sine(float x);
float ease_out_back(float x);

#endif