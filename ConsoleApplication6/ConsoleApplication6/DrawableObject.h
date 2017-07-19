#pragma once

class DrawableObject
{
public:
    coordType GetX() const { return _rect.X; }
    coordType GetY() const { return _rect.Y; }
    coordType GetW() const { return _rect.W; }
    coordType GetH() const { return _rect.H; }
    coordRect GetRect() const { return _rect; }
    void SetX(coordType X) { _rect.X = X; _afterChangeCoords(); }
    void SetY(coordType Y) { _rect.Y = Y; _afterChangeCoords(); }
    void SetW(coordType W) { _rect.W = W; _afterChangeCoords(); }
    void SetH(coordType H) { _rect.H = H; _afterChangeCoords(); }
    void SetRect(coordRect R) { _rect = R; _afterChangeCoords(); }

    ALLEGRO_COLOR GetColor() const { return _color; }
    virtual void SetColor(ALLEGRO_COLOR Color) { _color = Color; }

    bool GetVisible() const { return visible; }
    void SetVisible(bool V) { visible = V; }

    void Draw()
    {
        if (visible)
            _draw();
    }


protected:
    virtual void _afterChangeCoords() {}
    ALLEGRO_COLOR _color;
    coordRect _rect;
    bool visible;
    virtual void _draw() = 0;
};
