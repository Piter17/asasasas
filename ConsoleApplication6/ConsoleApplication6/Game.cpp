#include "stdafx.h"
#include "Game.h"
#include "Display.h"
#include "Text.h"
#include "Rectangle.h"

Game::Game()
{
    _allegro_init();
    _display = Display(800, 600);
}

void Game::Logic()
{

}


void Game::_allegro_init()
{
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_OPENGL);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    
}



int Game::Run()
{
    Texture::LoadTexture("asd.jpg", asd);
    _display.itemsToDraw.emplace_back(new Text(400, 300, "Lubie placki", al_map_rgb(255, 0, 0), AlignCenter));
    _display.itemsToDraw.emplace_back(new Text(400, 320, "Lubie placki", al_map_rgb(0, 255, 0), AlignLeft));
    _display.itemsToDraw.emplace_back(new Text(400, 280, "Lubie placki", al_map_rgb(0, 0, 255), AlignRight));
    //_display.itemsToDraw.emplace_back(new Rectangle(300, 300, 150, 150, 0, al_map_rgb(255,0, 0)));
    auto rect = std::make_shared<Rectangle>(300, 300, 150, 150, 0, asd);
    
    _display.itemsToDraw.push_back(std::dynamic_pointer_cast<DrawableObject>(rect));

    
    auto _startTime = std::chrono::system_clock::now();
    _lastTime = std::chrono::system_clock::now();

    for(;;)
    {
        auto timeNow = std::chrono::system_clock::now();
        std::chrono::duration<double> timeDiff = timeNow - _lastTime;

        auto frameDur = std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count();

        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - _startTime).count();

        rect->SetRot((dur / 200.0 / (std::atan(1.0) * 4)));
        rect->SetW(150 + 50.0 * sinf(dur / 1000.0));
        rect->SetH(150 + 50.0 * cosf(dur / 1000.0));
        rect->SetColor(sinf(dur / 700.0) / 2 + 0.5f);
        

        Logic();
        _display.Draw();
        //al_rest(0.0);


        _lastTime = timeNow;
    }
    
    return 0;
}


