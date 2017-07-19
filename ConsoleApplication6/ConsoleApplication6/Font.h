#pragma once
#include "stdafx.h"
#include <allegro5/allegro_ttf.h>

//First: filename, second: font size
typedef std::pair<std::string, int> fontDescriptor;

class Font
{
public:
    ~Font();
    static shared_ptr<Font> GetFont(fontDescriptor);
    ALLEGRO_FONT* GetNative() const { return _nativeFontPtr; }

private:
    Font(ALLEGRO_FONT* native) { _nativeFontPtr = native; }
    static shared_ptr<Font> _construct(ALLEGRO_FONT* native);

    static std::map<fontDescriptor, weak_ptr<Font>> _fonts;
    ALLEGRO_FONT* _nativeFontPtr;
};
