#pragma once
#include "stdafx.h"

typedef float coordType;
typedef float rotType;

struct coordRect
{
    coordType X, Y, W, H;
};

struct coordPoint
{
    coordType X, Y;
};

enum anchor
{
    Center,
    FirstVertex,
};
