#include "unistd.h"
#include "Eat.h"

sf::RenderWindow* Window = nullptr;
void Start();

int main()
{

    sf::RenderWindow window(sf::VideoMode(1100, 650), __FILE__, sf::Style::Default & ~sf::Style::Resize);
    window.setVerticalSyncEnabled (true);
    window.setFramerateLimit (25);
    Window = &window;

    Start();

    return 0;
}

void Start()
{
    sf::Texture background;
    background.loadFromFile("/home/max/CLionProjects/Game/texture/Water.png");
    background.setSmooth(true);

    sf::Texture food;
    food.loadFromFile("/home/max/CLionProjects/Game/texture/Eat.png");
    food.setSmooth(true);

    sf::Sprite sprite (food);
    sprite.setPosition (100, 100);

    Eat first_food(100, 100, 1, 1, 55, 57, 0, 0, 0, food);

    long long curr_dt = 0;
    sf::Clock clock;

    for (int i = 0; i < 5; i++)
    {
        curr_dt = clock.restart().asMicroseconds();
        first_food.d_t = 5;

        sf::RenderTexture tex;
        tex.create (1100, 650);
        tex.clear();

        sf::Sprite texSprite (tex.getTexture());
        texSprite.setOrigin (0, (float) 650);
        texSprite.setScale (1, -1);

        first_food.draw(&tex);

        Window->clear();
        Window->draw(texSprite);
        Window->draw(sprite);
        Window->display();

        //sleep(1);
    }
    sleep(1);
    Window->close();
}