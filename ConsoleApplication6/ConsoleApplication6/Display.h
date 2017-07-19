#pragma once
#include "stdafx.h"
#include "DrawableObject.h"

class Display
{
public:
    Display() {};
    Display(int x, int y);

    int GetX() const { return _x; }
    int GetY() const { return _y; }

    void* Display::Draw();

    std::vector<std::shared_ptr<DrawableObject>> itemsToDraw;

private:
    int _x, _y;
    ALLEGRO_DISPLAY *_int_display;

};
