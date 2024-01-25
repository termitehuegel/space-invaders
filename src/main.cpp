#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Close);
    window.setFramerateLimit(144);

    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/background.png");
    background.setTexture(backgroundTexture);


    while (window.isOpen()) {
        for (sf::Event event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }
}