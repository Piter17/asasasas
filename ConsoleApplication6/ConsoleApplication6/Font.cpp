#include "stdafx.h"
#include "Font.h"

std::map<fontDescriptor, weak_ptr<Font>> Font::_fonts;

Font::~Font()
{
    al_destroy_font(_nativeFontPtr);
}

shared_ptr<Font> Font::GetFont(fontDescriptor Font)
{
    static std::mutex addMutex;
    std::lock_guard<std::mutex> lock(addMutex);

    auto searchIt = _fonts.find(Font);
    if (searchIt != _fonts.end())
    {
        if (auto fontFromMap = searchIt->second.lock())
            return fontFromMap;
        _fonts.erase(searchIt);
    }
    
    auto native = al_load_ttf_font(Font.first.c_str(), Font.second, 0);
    if(!native)
    {
        std::cerr << "Failed to read font: " << Font.first << endl;
        return shared_ptr<Font>(nullptr);
    }
    auto font = _construct(native);
    _fonts[Font] = font;
    return font;
}

shared_ptr<Font> Font::_construct(ALLEGRO_FONT* native)
{
    Font font(native);
    return std::make_shared<Font>(font);
}
