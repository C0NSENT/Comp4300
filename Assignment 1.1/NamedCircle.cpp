#include "NamedCircle.h"

#include <iostream>

#include <cmath>
#include <ranges>

namespace nc
{
    template<typename VectorType, typename DivisorType>
    auto NamedCircle::vectorDivider(const sf::Vector2<VectorType>& v, DivisorType divisor) -> sf::Vector2<VectorType> {
        return sf::Vector2<VectorType>{v.x / divisor, v.y / divisor};
    }

    sf::Color NamedCircle::ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor) {
        auto convert = [](const float colorChannel) -> std::uint8_t {
            if (colorChannel <= 1.0f && colorChannel >= 0.0f)
                return static_cast<std::uint8_t>(std::round(colorChannel * 255.f));

            throw std::invalid_argument("Invalid ImGuiColor");
        };

        return sf::Color{
            convert(ImGuiColor[0]),
            convert(ImGuiColor[1]),
            convert(ImGuiColor[2]),
        };
    }

    auto NamedCircle::SFMLColorToImGui(const sf::Color& color) -> std::array<float, 3> {
        return std::array{
            static_cast<float>(color.r) / 255.f,
            static_cast<float>(color.g) / 255.f,
            static_cast<float>(color.b) / 255.f,
        };
    }

    sf::Color NamedCircle::invertColor(const sf::Color& color)
    {

        auto invert = [](const std::uint8_t colorChannel) -> std::uint8_t
        {
            std::uint8_t inverted = 255 - colorChannel;

            //Чуть для большей контрастности
            if (inverted < 122)
                inverted = std::min(inverted+40, 255);
            else
                inverted = std::max(inverted-40, 0);

            return inverted;
        };
        return {invert(color.r), invert(color.g), invert(color.b), color.a};
    }

    int NamedCircle::randomInt(std::mt19937_64& gen, const int min, const int max) {
        std::uniform_int_distribution distribution(min, max);
        return distribution(gen);
    }

    float NamedCircle::randomFloat(std::mt19937_64& gen, const float min, const float max) {
        std::uniform_real_distribution distribution(min, max);
        return distribution(gen);
    }

    void NamedCircle::processAxisCollision(const float centerPos, const float radius, float& velocity, const float axis) {
        if (centerPos - radius <= 0.f || centerPos + radius >= axis)
            velocity *= -1;
    }

    void NamedCircle::centeringText() {
        std::cout << "NamedCircle::centeringText()" << std::endl;
        this->textCenter = circle.getLocalBounds().getCenter() - name.getLocalBounds().getCenter();
    }

    ///////////////////////////////////////////////////
    ////    КОНСТРУКТОРЫ
    ///////////////////////////////////////////////////

    NamedCircle::NamedCircle(
        const sf::Font& font,
        const sf::String& name,
        const float radius,
        const int pointCount,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity
    )
        : circle{radius, static_cast<std::size_t>(pointCount)}
    , name(font, name, 24)
    , velocity(velocity)
    {
        std::cout << "NamedCircle::NamedCircle()" << std::endl;
        centeringText();
        this->setPosition(position);
        isCircleDrawn = isTextDrawn = true;
    }

    NamedCircle::NamedCircle(
        std::mt19937_64& gen,
        const sf::Font& font,
        const sf::String& name,
        const sf::Vector2u& screenSize
    )
        : circle(randomFloat(gen, 30.f, 200.f), randomInt(gen, 32, 64))
        , name(font, name, 24)
    {
        std::cout << "NamedCircle::NamedCircle()" << std::endl;
        centeringText();
        this->setPosition({randomFloat(gen, 0.f, screenSize.x),
            randomFloat(gen, 0.f, screenSize.y)});
        this->setVelocity(sf::Vector2f{randomFloat(gen, -5.f, 5.f),
            randomFloat(gen, -5.f, 5.f)});
        this->setColor(sf::Color{
            static_cast<std::uint8_t>(randomInt(gen, 0, 255)),
            static_cast<std::uint8_t>(randomInt(gen, 0, 255)),
            static_cast<std::uint8_t>(randomInt(gen, 0, 255))
        });
        isCircleDrawn = isTextDrawn = true;
    }

    ///////////////////////////////////////////////////
    ////    СЕТТЕРЫ
    ///////////////////////////////////////////////////

    void NamedCircle::setCircleFillColor(const std::array<float, 3>& ImGuiColor) {
        this->setCircleFillColor(ImGuiColorToSFMLColor(ImGuiColor));
    }

    void NamedCircle::setCircleFillColor(const sf::Color& color) {
        this->circle.setFillColor(color);
    }

    void NamedCircle::setColor(const sf::Color& color) {
        this->setCircleFillColor(color);
        this->name.setFillColor(invertColor(color));
        this->name.setOutlineColor(sf::Color::Black);
    }

    void NamedCircle::setColor(const std::array<float, 3>& ImGuiColor) {
        setColor(ImGuiColorToSFMLColor(ImGuiColor));
    }

    void NamedCircle::setPosition(const sf::Vector2f& position) {
        circle.setPosition(position);
        name.setPosition(position + textCenter);
    }

    void NamedCircle::setRadius(const float radius, const sf::Vector2u& screenSize) {
        circle.setRadius(radius);
        centeringText();
        processScreenCollision(screenSize);
    }

    void NamedCircle::setPointCount(const std::size_t& pointCount) {
        circle.setPointCount(pointCount);
    }

    void NamedCircle::setVelocity(const sf::Vector2f& velocity) {
        this->velocity = velocity;
    }

    void NamedCircle::setVelocity(const std::array<float, 2>& velocity) {
        setVelocity(sf::Vector2f{velocity[0], velocity[1]});
    }

    void NamedCircle::setName(const std::string& name) {
        this->name.setString(name);
        centeringText();
    }

    ///////////////////////////////////////////////////
    ////    ГЕТТЕРЫ
    ///////////////////////////////////////////////////

    float NamedCircle::getRadius() const {
        return circle.getRadius();
    }
    std::size_t NamedCircle::getPointCount() const {
        return circle.getPointCount();
    }
    std::string NamedCircle::getName() const {
        return name.getString();
    }
    sf::Vector2f NamedCircle::getPosition() const {
        return circle.getPosition();
    }
    sf::Vector2f NamedCircle::getVelocity() const {
        return velocity;
    }
    std::array<float, 2> NamedCircle::getImGuiVelocity() const {
        return {velocity.x, velocity.y};
    }
    std::array<float, 3> NamedCircle::getImGuiFillColor() const {
        return SFMLColorToImGui(this->circle.getFillColor());
    }

    ///////////////////////////////////////////////////
    ////    ДРУГИЕ МЕТОДЫ
    ///////////////////////////////////////////////////

    void NamedCircle::move() {
        setPosition(circle.getPosition() + velocity);
    }

    void NamedCircle::draw(sf::RenderWindow& window) const {
        if (isCircleDrawn) window.draw(circle);
        if (isTextDrawn) window.draw(name);
    }

    void NamedCircle::processScreenCollision(const sf::Vector2u& windowSize) {
        processAxisCollision(
            circle.getGlobalBounds().getCenter().x,
            circle.getRadius(),
            velocity.x,
            windowSize.x
        );

        processAxisCollision(
            circle.getGlobalBounds().getCenter().y,
            circle.getRadius(),
            velocity.y,
            windowSize.y
        );
    }

    NamedCircle getElement(const unsigned selectedIndex, const std::list<NamedCircle> &lsCircles)
    {
	    if (selectedIndex < lsCircles.size()) {
		    auto it = lsCircles.begin();
		    std::advance(it, selectedIndex);
		    return *it;
	    }
	    throw std::out_of_range("List out of range: list size = " + std::to_string(lsCircles.size())
	        + ", selectedIndex = " + std::to_string(selectedIndex));
    }

    NamedCircle& getElementRef(const unsigned selectedIndex, std::list<NamedCircle> &lsCircles)
    {
	    auto it = lsCircles.begin();
	    if (selectedIndex < lsCircles.size()) {
		    std::advance(it, selectedIndex);
	    }
	    return *it;
    }

    ///////////////////////////////////////////////////
    ////	ImGuiLoopHandler
    //////////////////////////////////////////////////

    ImGuiLoopHandler::ImGuiLoopHandler(const unsigned selectedIndex, const NamedCircle &circle)
	    : currentIndex(selectedIndex)
	    , radius(circle.getRadius())
	    , pointCount(circle.getPointCount())
	    , velocity(circle.getVelocity())
	    , name(circle.getName())
	    , ImGuiCircleFillColor(circle.getImGuiFillColor())
	    , isCircleDrawn(circle.isCircleDrawn)
	    , isNameDrawn(circle.isTextDrawn)
    {
    }

    ImGuiLoopHandler::ImGuiLoopHandler(const unsigned selectedIndex, const std::list<NamedCircle> &lsCircles)
	    : ImGuiLoopHandler(selectedIndex, getElement(selectedIndex, lsCircles)) {}

    ImGuiLoopHandler & ImGuiLoopHandler::operator=(const NamedCircle &circle)
    {
	    radius = circle.getRadius();
	    pointCount = circle.getPointCount();
	    velocity = circle.getVelocity();
	    name = circle.getName();
	    ImGuiCircleFillColor = circle.getImGuiFillColor();
	    isCircleDrawn = circle.isCircleDrawn;
	    isNameDrawn = circle.isTextDrawn;

	    return *this;
    }

    void ImGuiLoopHandler::UpdateNC(const unsigned selectedIndex, NamedCircle &circle, const sf::Vector2u& screenSize) const
    {
	    if (currentIndex == selectedIndex) {
		    std::cout << "Updating circle with selectedIndex " << selectedIndex << std::endl;
		    circle.setRadius(radius, screenSize);
		    if (circle.getPointCount() != pointCount) circle.setPointCount(pointCount);
		    if (circle.getVelocity() != velocity) circle.setVelocity(velocity);
		    if (circle.getName() != name) circle.setName(name);
		    if (circle.getImGuiFillColor() != ImGuiCircleFillColor) circle.setCircleFillColor(ImGuiCircleFillColor);
		    circle.isCircleDrawn = isCircleDrawn;
		    circle.isTextDrawn = isNameDrawn;
	    }
    }

    void ImGuiLoopHandler::UpdateNC(const unsigned selectedIndex, std::list<NamedCircle> &lsCircles,
        const sf::Vector2u& screenSize) const {
	    UpdateNC(selectedIndex, getElementRef(selectedIndex, lsCircles), screenSize);
    }
}

