#pragma once
#include "stdafx.h"
#include "DrawableObject.h"
#include "Texture.h"

class Rectangle : public DrawableObject
{
public:
    Rectangle(Rectangle&& r) = default;
    Rectangle(coordType X, coordType Y, coordType W, coordType H, rotType Rotation, eTexture TextureId );
    Rectangle(coordRect Rect, rotType Rotation, eTexture TextureId);

    Rectangle(coordType X, coordType Y, coordType W, coordType H, rotType Rotation, ALLEGRO_COLOR color);
    Rectangle(coordRect Rect, rotType Rotation, ALLEGRO_COLOR color);

    void SetRot(rotType r) { _rot = r; _afterChangeCoords(); }
    rotType GetRot() const { return _rot; }

    void SetColor(ALLEGRO_COLOR Color) override;
    void SetColor(float Brightness);
    void SetTexture(eTexture Texture);
    eTexture GetTexture() const { return _textureId; }

protected:
    void _draw() override;
    inline void _afterChangeCoords() override;
private:
    
    void _recalculate_vtxs();
    void _init_vtxs();
    
    ALLEGRO_VERTEX _vtxs[4];
    rotType _rot;
    eTexture _textureId;
    weak_ptr<Texture> _texture;
    float _brightness;
};
