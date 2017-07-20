#include "stdafx.h"
#include "Font.h"

std::map<fontDescriptor, weak_ptr<Font>> Font::_fonts;

Font::~Font()
{
    al_destroy_font(_nativeFontPtr);
}

shared_ptr<Font> Font::GetFont(fontDescriptor FontDesc)
{
    static std::mutex addMutex;
    std::lock_guard<std::mutex> lock(addMutex);

    auto searchIt = _fonts.find(FontDesc);
    if (searchIt != _fonts.end())
    {
        if (auto fontFromMap = searchIt->second.lock())
        {
            std::cout << "Font " << FontDesc.first.c_str() << " with size: " << FontDesc.second << " is already loaded" << std::endl;
            return fontFromMap;
        }
        _fonts.erase(searchIt);
    }
    
    auto native = al_load_ttf_font(FontDesc.first.c_str(), FontDesc.second, 0);
    if(!native)
    {
        std::cerr << "Failed to read font: " << FontDesc.first << endl;
        return shared_ptr<Font>(nullptr);
    }
    std::cout << "Font " << FontDesc.first.c_str() << " with size: " << FontDesc.second << " loaded on address: " << native << std::endl;
    auto font = _construct(native);
    _fonts[FontDesc] = font;
    return font;
}

shared_ptr<Font> Font::_construct(ALLEGRO_FONT* native)
{
    Font font(native);
    return std::make_shared<Font>(font);
}
