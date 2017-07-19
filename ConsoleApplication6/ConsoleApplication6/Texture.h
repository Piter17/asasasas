#pragma once
#include "stdafx.h"

enum eTexture;

class Texture
{
public:
    ~Texture();

    coordType GetW() const { return _w; }
    coordType GetH() const { return _h; }
    ALLEGRO_BITMAP * GetNative() const { return _bitmap; }

    static bool LoadTexture(string fileName, eTexture TextureId);
    static std::shared_ptr<Texture> GetTexture(eTexture e_texture) { return _textures[e_texture]; }
    explicit Texture(ALLEGRO_BITMAP* Bitmap);

private:
    coordType _w, _h;
    ALLEGRO_BITMAP *_bitmap;
    static std::map<eTexture, std::shared_ptr<Texture>> _textures;
};

enum eTexture
{
    blank,
    placeholder,
    asd,
};