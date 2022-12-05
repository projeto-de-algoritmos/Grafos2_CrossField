#include <Solution.h>
#include <unistd.h>
#include <iostream>

const int WIDTH=800;
const int HEIGHT=480;

int main (){

    Solution *sol = new Solution();

    std::cout << sol->getSolution() << std::endl;

    /* RenderWindow window(VideoMode(WIDTH, HEIGHT), "CrossField");
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

    window.display();
    
    sleep(5); */
    return 0;
}