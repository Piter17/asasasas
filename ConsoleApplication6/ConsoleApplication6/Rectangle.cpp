#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(coordType X, coordType Y, coordType W, coordType H, rotType Rotation, eTexture TextureId)
{
    _rect = { X, Y, W, H };
    _rot = Rotation;
    _color = al_map_rgb(255, 255, 255);
    SetTexture(TextureId);
}

Rectangle::Rectangle(coordRect Rect, rotType Rotation, eTexture TextureId)
{
    _rect = Rect;
    _rot = Rotation;
    _color = al_map_rgb(255, 255, 255);
    SetTexture(TextureId);
}

Rectangle::Rectangle(coordType X, coordType Y, coordType W, coordType H, rotType Rotation, ALLEGRO_COLOR color)
{
    _rect = { X, Y, W, H };
    _rot = Rotation;
    Rectangle::SetColor(color);
}

Rectangle::Rectangle(coordRect Rect, rotType Rotation, ALLEGRO_COLOR color)
{
    _rect = Rect;
    _rot = Rotation;
    Rectangle::SetColor(color);
}

void Rectangle::SetColor(ALLEGRO_COLOR color)
{
    _color = color;
    _init_vtxs();
}

void Rectangle::SetColor(float Brightness)
{
    SetColor(al_map_rgb_f(Brightness, Brightness, Brightness));
}

void Rectangle::SetTexture(eTexture Texture)
{
    _textureId = Texture;
    _texture = Texture::GetTexture(Texture);
    _init_vtxs();
}

void Rectangle::_draw()
{
    ALLEGRO_BITMAP* tex = nullptr;
    if (auto texture = _texture.lock())
        tex = texture->GetNative();

    al_draw_prim(_vtxs, nullptr, tex, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

void Rectangle::_afterChangeCoords()
{
    _recalculate_vtxs();
}

void Rectangle::_recalculate_vtxs()
{
    auto halfW = _rect.W / static_cast<coordType>(2.0);
    auto halfH = _rect.H / static_cast<coordType>(2.0);

    _vtxs[0].x = ((-halfW) * std::cos(_rot)) + (-halfH * std::sin(_rot)) + _rect.X;
    _vtxs[0].y = ((halfW)* std::sin(_rot)) + (-halfH * std::cos(_rot)) + _rect.Y;

    _vtxs[1].x = ((halfW)* std::cos(_rot)) + ((-halfH) * std::sin(_rot)) + _rect.X;
    _vtxs[1].y = ((-halfW)* std::sin(_rot)) + ((-halfH) * std::cos(_rot)) + _rect.Y;

    _vtxs[2].x = ((halfW)* std::cos(_rot)) + (halfH * std::sin(_rot)) + _rect.X;
    _vtxs[2].y = ((-halfW)* std::sin(_rot)) + (halfH * std::cos(_rot)) + _rect.Y;

    _vtxs[3].x = ((-halfW) * std::cos(_rot)) + (halfH * std::sin(_rot)) + _rect.X;
    _vtxs[3].y = ((halfW)* std::sin(_rot)) + (halfH * std::cos(_rot)) + _rect.Y;
}

void Rectangle::_init_vtxs()
{
    coordRect rect = {0, 0, 0, 0};
    bool hasTexture = false;
    if (auto texture = _texture.lock())
    {
        rect = { 0, 0, texture->GetW(), texture->GetH() };
        hasTexture = true;
    }
    
    auto halfW = _rect.W / static_cast<coordType>(2.0);
    auto halfH = _rect.H / static_cast<coordType>(2.0);

    _vtxs[0].x = ((-halfW) * std::cos(_rot)) + (-halfH * std::sin(_rot)) + _rect.X;
    _vtxs[0].y = ((halfW)* std::sin(_rot)) + (-halfH * std::cos(_rot)) + _rect.Y;
    _vtxs[0].z = 0;
    _vtxs[0].u = rect.X;
    _vtxs[0].v = rect.Y;
    _vtxs[0].color = _color;

    _vtxs[1].x = ((halfW)* std::cos(_rot)) + ((-halfH) * std::sin(_rot)) + _rect.X;
    _vtxs[1].y = ((-halfW)* std::sin(_rot)) + ((-halfH) * std::cos(_rot)) + _rect.Y;
    _vtxs[1].z = 0;
    _vtxs[1].u = rect.W;
    _vtxs[1].v = rect.Y;
    _vtxs[1].color = _color;


    _vtxs[2].x = ((halfW)* std::cos(_rot)) + (halfH * std::sin(_rot)) + _rect.X;
    _vtxs[2].y = ((-halfW)* std::sin(_rot)) + (halfH * std::cos(_rot)) + _rect.Y;
    _vtxs[2].z = 0;
    _vtxs[2].u = rect.W;
    _vtxs[2].v = rect.H;
    _vtxs[2].color = _color;

    _vtxs[3].x = ((-halfW) * std::cos(_rot)) + (halfH * std::sin(_rot)) + _rect.X;
    _vtxs[3].y = ((halfW)* std::sin(_rot)) + (halfH * std::cos(_rot)) + _rect.Y;
    _vtxs[3].z = 0;
    _vtxs[3].u = rect.X;
    _vtxs[3].v = rect.H;
    _vtxs[3].color = _color;
}
