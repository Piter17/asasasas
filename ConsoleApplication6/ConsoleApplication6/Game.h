#pragma once
#include "stdafx.h"
#include "Display.h"

class Game
{
public:
    Game();

    void Logic();

    int Run();


private:
    std::chrono::time_point<std::chrono::system_clock> _lastTime;
    Display _display;
    void _allegro_init();
};

