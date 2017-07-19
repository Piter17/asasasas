#include "stdafx.h"
#include "Texture.h"

std::map<eTexture, std::shared_ptr<Texture>> Texture::_textures;

Texture::~Texture()
{
    if(_bitmap)
        al_destroy_bitmap(_bitmap);
}

bool Texture::LoadTexture(string fileName, eTexture TextureId)
{
    auto bitmap = al_load_bitmap(fileName.c_str());
    if (!bitmap)
    {
        std::cerr << "Failed to read texture: " << fileName << endl;
        return false;
    }
   
    _textures.try_emplace(TextureId, std::make_shared<Texture>(bitmap));
    //_textures.emplace(std::piecewise_construct, std::forward_as_tuple(TextureId), std::forward_as_tuple(bitmap, w, h));
    return true;
}

Texture::Texture(ALLEGRO_BITMAP* Bitmap)
{
    _bitmap = Bitmap;
    _w = al_get_bitmap_width(_bitmap);
    _h = al_get_bitmap_height(_bitmap);
}
