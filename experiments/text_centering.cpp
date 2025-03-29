#include <iostream>
#include <stdexcept>
#include <random>
#include <SFML/Graphics.hpp>

constexpr sf::Vector2u screenSize{1280, 720};

sf::Color randomColor() {
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<std::uint8_t> distribution(0, 255);
    return {distribution(generator), distribution(generator), distribution(generator)};
}

void initCircle(sf::CircleShape& circle) {
    circle.setRadius(50);
    circle.setPointCount(32);
    circle.setOrigin({circle.getRadius(), circle.getRadius()}); // Центр круга
    circle.setPosition({screenSize.x/2.f, screenSize.y/2.f});  // Центр экрана
    circle.setFillColor(randomColor());

    // Дебаг информация
    std::cout << "\n=== CIRCLE ===";
}

void initShapeText(sf::Text& text) {
    text.setString("Circle");
    text.setCharacterSize(24);


    // Центрирование текста
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({textBounds.position.x /2.f, textBounds.position.y /2.f});
}

int main() {
    sf::RenderWindow window(sf::VideoMode({screenSize}), "Text Centering", sf::Style::Close);
    window.setFramerateLimit(60);

    // Загрузка шрифта
    sf::Font font("..\\Comp4300\\stuff\\font.ttf");


    // Инициализация объектов
    sf::CircleShape circle;
    initCircle(circle);

    sf::Text shapeText(font);
    initShapeText(shapeText);
    shapeText.setPosition(circle.getPosition()); // Начальная позиция

    // Главный цикл
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            /*if (event->is<sf::Event::Closed>())
                window.close();*/
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }

        }


        // Обновление позиции
        //circle.move({1.5f, 1.5f});
        shapeText.setPosition(circle.getPosition());

        // Отрисовка
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(shapeText);
        window.display();
    }

    return EXIT_SUCCESS;
}