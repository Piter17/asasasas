#pragma once
#include "stdafx.h"
#include "DrawableObject.h"
#include "Font.h"

enum TextFlags;

class Text : public DrawableObject
{
public:
    Text(Text&& t) = default;
    Text(coordType X, coordType Y, string Text, ALLEGRO_COLOR Color, TextFlags Flags, fontDescriptor Font);
    Text(coordPoint Point, string Text, ALLEGRO_COLOR Color, TextFlags Flags, fontDescriptor Font);

private:
    
    // defined in allegro_font.h
    TextFlags flags;
    string text;
    void _draw() override;
    shared_ptr<Font> _font;
    static ALLEGRO_FONT* _default_font;
};


enum TextFlags
{
    NoKerning = -1,
    AlignLeft = 0,
    AlignCenter = 1,
    AlignRight = 2,
    AlignInteger = 4,
};