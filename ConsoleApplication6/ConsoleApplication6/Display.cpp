#include "stdafx.h"
#include "Display.h"
#include "Texture.h"

Display::Display(int x, int y)
{
    _x = x;
    _y = y;
    _int_display = al_create_display(x, y);
}

void* Display::Draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    for (auto &i : itemsToDraw)
        i->Draw();

    al_flip_display();
    return nullptr;
}
