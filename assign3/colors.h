/* 
 * colors.h - Starter code from lecture notes.
 * Defines a struct for rgb values, and a relevant namespace
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef _COLORS_H_
#define _COLORS_H_

#include <iostream>

struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

namespace colors {
	constexpr color BLACK	{   0,   	0,		0 	};
	constexpr color WHITE	{	255, 	255,	255 };
	constexpr color RED		{   255,	0,		0 	};
	constexpr color GREEN	{   0, 		255,	0 	};
	constexpr color BLUE	{   0,   	0, 		255 };
	constexpr color ORANGE	{	255,	165,	0	};
}

#endif