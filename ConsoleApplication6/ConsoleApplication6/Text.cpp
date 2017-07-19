#include "stdafx.h"
#include "Text.h"

ALLEGRO_FONT* Text::_default_font = nullptr;

Text::Text(coordType X, coordType Y, string Text, ALLEGRO_COLOR Color, TextFlags Flags, fontDescriptor Font)
{
    _rect.X = X;
    _rect.Y = Y;
    text = Text;
    _color = Color;
    flags = Flags;
    _font = Font::GetFont(Font);
    if (_default_font == nullptr)
        _default_font = al_create_builtin_font();
}

Text::Text(coordPoint Point, string Text, ALLEGRO_COLOR Color, TextFlags Flags, fontDescriptor Font)
{
    _rect.X = Point.X;
    _rect.Y = Point.Y;
    text = Text;
    _color = Color;
    flags = Flags;
    _font = Font::GetFont(Font);
    if (_default_font == nullptr)
        _default_font = al_create_builtin_font();
}

void Text::_draw()
{
    al_draw_text(_font ? _font->GetNative() : _default_font, _color, _rect.X, _rect.Y, flags, text.c_str());
}
