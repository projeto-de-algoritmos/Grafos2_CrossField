#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

class Settings
{
private:

public:
    Settings();
    ~Settings();

    std::string shortest_path, current_value, try_number, best_try, victory;
    int width, height;
    Font font;
};
