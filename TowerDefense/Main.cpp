#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "MainMenu.h"
int main()
{
    Utils::get().window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML works!");
    Utils::get().init();

    Utils::get().currentGame = new MainMenu();


    while (Utils::get().window->isOpen())
    {
        Utils::get().tickClock();
        sf::Event event;
        while (Utils::get().window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                Utils::get().window->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                Utils::get().currentGame->onMouseDown(event);
            }
            else if (event.type == Event::KeyPressed) {
                Utils::get().currentGame->onKeyDown(event);
            }
        }
        Utils::get().window->clear({ 66,66,66 });

        //printf("d: %f\n", Utils::get().deltaTime);

        Utils::get().currentGame->update();
        Utils::get().currentGame->draw();

        Utils::get().window->display();
    }

    return 0;
}